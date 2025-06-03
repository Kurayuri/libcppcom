#pragma once
#include "PU.hpp"
#include <Highs.h>
#include <vector>

namespace HighsUtils {
using namespace PU;
using HighsValue_t = double;
using HighsSize_t = HighsInt;

struct AMatrix_t {
    MatrixFormat format_;
    std::vector<HighsSize_t> start_;
    std::vector<HighsSize_t> index_;
    std::vector<HighsValue_t> value_;
};

struct AllResult_t {
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

    AMatrix_t a_matrix_;
};

AllResult_t inline buildAll(const PUModel &pu_model) {
    AllResult_t result;
    result.num_col_ = pu_model.vars.size();
    result.num_row_ = pu_model.constrs.size();
    result.sense_ = pu_model.sense == PU_MINIMIZE ? ObjSense::kMinimize : ObjSense::kMaximize;
    result.offset_ = pu_model.objective.offset;

    result.col_cost_.resize(result.num_col_);
    result.col_lower_.resize(result.num_col_);
    result.col_upper_.resize(result.num_col_);
    result.integrality_.resize(result.num_col_);

    for (const auto &var : pu_model.vars) {
        result.col_cost_[var.id] = var.coef;
        result.col_lower_[var.id] = var.lb;
        result.col_upper_[var.id] = var.ub;
        result.integrality_[var.id] = static_cast<HighsVarType>(var.type);
    }

    result.row_lower_.resize(result.num_row_);
    result.row_upper_.resize(result.num_row_);
    result.a_matrix_.format_ = MatrixFormat::kRowwise;

    size_t idx = 0;
    for (HighsSize_t i = 0; i < pu_model.constrs.size(); ++i) {
        const auto &constr = pu_model.constrs[i];
        result.row_lower_[i] = constr.lb;
        result.row_upper_[i] = constr.ub;
        result.a_matrix_.start_.push_back(idx);
        HighsValue_t offset = 0;
        for (const auto &[var_id, item] : constr.expr.items) {
            result.a_matrix_.index_.push_back(var_id);
            result.a_matrix_.value_.push_back(item.coef);
            offset += item.offset;
            idx++;
        }
    }
    result.a_matrix_.start_.push_back(idx);
    return result;
}

HighsModel inline buildModel(const PUModel &pu_model) {
    HighsModel model;
    auto all_result = buildAll(pu_model);

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

} // namespace HighsUtils