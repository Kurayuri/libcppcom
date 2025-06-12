#pragma once
#include "LCCS.hpp"
#include <Highs.h>
#include <vector>

namespace HighsUtils {
using namespace LCCS;
using HighsValue_t = double;
using HighsSize_t = HighsInt;

struct AMatrix_t_ {
    MatrixFormat format_;
    std::vector<HighsSize_t> start_;
    std::vector<HighsSize_t> index_;
    std::vector<HighsValue_t> value_;
};

struct LP_ {
    HighsSize_t num_col_;
    HighsSize_t num_row_;
    ObjSense sense_;
    HighsValue_t offset_;
    std::vector<HighsValue_t> col_cost_;
    std::vector<HighsValue_t> col_lower_;
    std::vector<HighsValue_t> col_upper_;
    std::vector<HighsValue_t> row_lower_;
    std::vector<HighsValue_t> row_upper_;
    std::vector<HighsVarType> integrality_;

    AMatrix_t_ a_matrix_;
};
HighsVarType inline toHighsVarType(LCCSType_t type) {
    switch (type) {
    case LCCS_CONTINUOUS:
        return HighsVarType::kContinuous;
    case LCCS_BINARY:
        return HighsVarType::kInteger;
    case LCCS_INTEGER:
        return HighsVarType::kInteger;
    case LCCS_SEMICONT:
        return HighsVarType::kSemiContinuous;
    case LCCS_SEMIINT:
        return HighsVarType::kSemiInteger;
    default:
        throw std::invalid_argument("Unknown variable type");
    }
}
LCCSType_t inline toLCCSType(HighsVarType type) {
    switch (type) {
    case HighsVarType::kContinuous:
        return LCCS_CONTINUOUS;
    case HighsVarType::kInteger:
        return LCCS_INTEGER;
    case HighsVarType::kSemiContinuous:
        return LCCS_SEMICONT;
    case HighsVarType::kSemiInteger:
        return LCCS_SEMIINT;
    default:
        throw std::invalid_argument("Unknown variable type");
    }
}

LP_ inline to_LP_(const LCCSModel &lccs_model) {
    LP_ result;
    result.num_col_ = lccs_model.vars.size();
    result.num_row_ = lccs_model.constrs.size();
    result.sense_ = lccs_model.sense == LCCS_MINIMIZE ? ObjSense::kMinimize : ObjSense::kMaximize;
    result.offset_ = lccs_model.objective.total_offset();

    result.col_cost_.resize(result.num_col_);
    result.col_lower_.resize(result.num_col_);
    result.col_upper_.resize(result.num_col_);
    result.integrality_.resize(result.num_col_);

    for (const auto &var : lccs_model.vars) {
        auto var_it = lccs_model.objective.items.find(var.id);
        HighsValue_t coef = var_it != lccs_model.objective.items.end() ? var_it->second.coef : 0.0;
        result.col_cost_[var.id] = coef;
        result.col_lower_[var.id] = var.lb;
        result.col_upper_[var.id] = var.ub;
        result.integrality_[var.id] = toHighsVarType(var.type);
    }

    result.row_lower_.resize(result.num_row_);
    result.row_upper_.resize(result.num_row_);
    result.a_matrix_.format_ = MatrixFormat::kRowwise;

    size_t idx = 0;
    for (size_t i = 0; i < lccs_model.constrs.size(); ++i) {
        const auto &constr = lccs_model.constrs[i];

        result.a_matrix_.start_.push_back(idx);
        HighsValue_t offset = constr.expr.offset; // Initialize offset with the constraint's offset
        for (const auto &[var_id, item] : constr.expr.items) {
            result.a_matrix_.index_.push_back(var_id);
            result.a_matrix_.value_.push_back(item.coef);
            offset += item.offset;
            idx++;
        }
        result.row_lower_[i] = constr.lb - offset;
        result.row_upper_[i] = constr.ub - offset;
    }
    result.a_matrix_.start_.push_back(idx);
    return result;
}

HighsModel inline to_HIghsModel(const LCCSModel &lccs_model) {
    HighsModel model;
    auto all_result = to_LP_(lccs_model);

    model.lp_.num_col_ = all_result.num_col_;
    model.lp_.num_row_ = all_result.num_row_;
    model.lp_.sense_ = all_result.sense_;
    model.lp_.offset_ = all_result.offset_;
    model.lp_.col_cost_ = std::move(all_result.col_cost_);
    model.lp_.col_lower_ = std::move(all_result.col_lower_);
    model.lp_.col_upper_ = std::move(all_result.col_upper_);
    model.lp_.row_lower_ = std::move(all_result.row_lower_);
    model.lp_.row_upper_ = std::move(all_result.row_upper_);
    model.lp_.integrality_ = std::move(all_result.integrality_);
    model.lp_.a_matrix_.format_ = all_result.a_matrix_.format_;
    model.lp_.a_matrix_.start_ = std::move(all_result.a_matrix_.start_);
    model.lp_.a_matrix_.index_ = std::move(all_result.a_matrix_.index_);
    model.lp_.a_matrix_.value_ = std::move(all_result.a_matrix_.value_);

    return model;
}
LCCSModel inline to_LCCSModel(const HighsModel &model) {
    LCCSModel lccs_model;
    lccs_model.sense = model.lp_.sense_ == ObjSense::kMinimize ? LCCS_MINIMIZE : LCCS_MAXIMIZE;
    lccs_model.objective.offset = model.lp_.offset_;

    for (HighsSize_t i = 0; i < model.lp_.num_col_; ++i) {
        lccs_model.addVar(model.lp_.col_lower_[i], model.lp_.col_upper_[i], model.lp_.col_cost_[i],
                          toLCCSType(model.lp_.integrality_[i]));
    }

    for (HighsSize_t i = 0; i < model.lp_.num_row_; ++i) {
        LCCSLinExpr expr;
        for (HighsSize_t j = model.lp_.a_matrix_.start_[i]; j < model.lp_.a_matrix_.start_[i + 1];
             ++j) {
            expr.items[model.lp_.a_matrix_.index_[j]] = LCCSLinItem(model.lp_.a_matrix_.value_[j]);
        }
        lccs_model.addConstr(model.lp_.row_lower_[i] + expr.offset, expr,
                             model.lp_.row_upper_[i] + expr.offset);
    }

    lccs_model.setObjective(lccs_model.objective, lccs_model.sense);
    return lccs_model;
}

void inline dumpConstr(const Highs &highs,  const HighsModel &model,
                       const LCCSModel &lccs_model, const HighsSolution &solution) {
    const auto &lp = model.lp_;
    const auto &basis = highs.getBasis();
    std::ofstream ofs("highs_rows.txt");
    for (int row = 0; row < lp.num_row_; row++) {
        if (!lccs_model.constrs[row].name.empty()) {
            ofs << "Row    " << row;
            ofs << "; value = " << solution.row_value[row]
                << "; status: " << highs.basisStatusToString(basis.row_status[row]) << "  "
                << lccs_model.constrs[row].name;
            ofs << std::endl;
        }
    }
    ofs.close();
}

std::string inline printModel(const HighsModel &model) {
    std::ostringstream oss;
    oss << "HighsModel:\n";
    oss << "  num_col: " << model.lp_.num_col_ << "\n";
    oss << "  num_row: " << model.lp_.num_row_ << "\n";
    oss << "  sense: " << (model.lp_.sense_ == ObjSense::kMinimize ? "Minimize" : "Maximize")
        << "\n";
    oss << "  offset: " << model.lp_.offset_ << "\n";
    oss << "  col_cost: ";
    for (const auto &cost : model.lp_.col_cost_) {
        oss << cost << " ";
    }
    oss << "\n  col_lower: ";
    for (const auto &lower : model.lp_.col_lower_) {
        oss << lower << " ";
    }
    oss << "\n  col_upper: ";
    for (const auto &upper : model.lp_.col_upper_) {
        oss << upper << " ";
    }
    oss << "\n  row_lower: ";
    for (const auto &lower : model.lp_.row_lower_) {
        oss << lower << " ";
    }
    oss << "\n  row_upper: ";
    for (const auto &upper : model.lp_.row_upper_) {
        oss << upper << " ";
    }
    oss << "\n  integrality: ";
    for (const auto &type : model.lp_.integrality_) {
        oss << static_cast<int>(type) << " ";
    }
    oss << "\n  a_matrix format: " << static_cast<int>(model.lp_.a_matrix_.format_) << "\n";
    oss << "  a_matrix start: ";
    for (const auto &start : model.lp_.a_matrix_.start_) {
        oss << start << " ";
    }
    oss << "\n  a_matrix index: ";
    for (const auto &index : model.lp_.a_matrix_.index_) {
        oss << index << " ";
    }
    oss << "\n  a_matrix value: ";
    for (const auto &value : model.lp_.a_matrix_.value_) {
        oss << value << " ";
    }
    oss << "\n";
    // Add more details as needed
    return oss.str();
}
} // namespace HighsUtils