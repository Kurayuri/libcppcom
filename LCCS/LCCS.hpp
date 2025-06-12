#pragma once
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
namespace LCCS {
using LCCSSize_t = std::size_t;
using LCCSValue_t = double;
using LCCSType_t = int;
inline constexpr LCCSValue_t LCCS_VALUE_INF = 1.0e30;
inline constexpr LCCSValue_t LCCS_VALUE_P_INF = 1.0e30;
inline constexpr LCCSValue_t LCCS_VALUE_N_INF = -1.0e30;

inline constexpr LCCSType_t LCCS_CONTINUOUS = 0;
inline constexpr LCCSType_t LCCS_BINARY = 1;
inline constexpr LCCSType_t LCCS_INTEGER = 2;
inline constexpr LCCSType_t LCCS_SEMICONT = 3;
inline constexpr LCCSType_t LCCS_SEMIINT = 4;
inline constexpr LCCSType_t LCCS_MINIMIZE = 0;
inline constexpr LCCSType_t LCCS_MAXIMIZE = 1;


struct LCCSVar;     
struct LCCSLinItem; 
struct LCCSLinExpr; 
struct LCCSConstr;  
class LCCSModel;    

using LCCSLinExpr_0D = LCCSLinExpr;
using LCCSLinExpr_1D = std::vector<LCCSLinExpr_0D>;
using LCCSLinExpr_2D = std::vector<LCCSLinExpr_1D>;
using LCCSLinExpr_3D = std::vector<LCCSLinExpr_2D>;

using LCCSVar_0D = LCCSVar;
using LCCSVar_1D = std::vector<LCCSVar_0D>;
using LCCSVar_2D = std::vector<LCCSVar_1D>;
using LCCSVar_3D = std::vector<LCCSVar_2D>;

struct LCCSVar {
    LCCSValue_t lb = 0;
    LCCSValue_t ub = 0;
    LCCSValue_t obj_coef = 0; // Coefficient in the objective function if use the default objective

    LCCSType_t type = LCCS_CONTINUOUS; // Variable type
    LCCSSize_t id;
    std::string name;

    std::string to_string() const {
        std::ostringstream oss;
        oss << "LCCSVar(id=" << id << ", lb=" << lb << ", ub=" << ub << ", coef=" << obj_coef
            << ", type=" << type << ")";
        return oss.str();
    }
};

struct LCCSLinItem {
    LCCSValue_t coef = 0;   // Coefficient for the variable
    LCCSValue_t offset = 0; // Constant offset for the item

    // LCCSVar *var;
    LCCSLinItem() = default;
    LCCSLinItem(LCCSValue_t coef, LCCSValue_t offset = 0) : coef(coef), offset(offset) {}
    LCCSLinItem(const LCCSVar &var) : coef(1), offset(0) {} // Assuming offset is zero for vars

    LCCSLinItem &operator+=(const LCCSLinItem &item) {
        coef += item.coef;
        offset += item.offset;
        return *this;
    }
    LCCSLinItem &operator+=(LCCSValue_t scalar) {
        offset += scalar;
        return *this;
    }
    LCCSLinItem &operator+=(const LCCSVar &var) {
        coef += 1; // TODO
        return *this;
    }
    LCCSLinItem &operator/=(LCCSValue_t scalar) {
        coef /= scalar;
        offset /= scalar;
        return *this;
    }
    LCCSLinItem &operator*=(LCCSValue_t scalar) {
        coef *= scalar;
        offset *= scalar;
        return *this;
    }
};

struct LCCSLinExpr {
    std::unordered_map<LCCSSize_t, LCCSLinItem> items;
    LCCSValue_t offset = 0;
    // LCCSValue_t coef;

    LCCSLinExpr() = default;
    LCCSLinExpr(LCCSValue_t offset, LCCSValue_t coef = 0)
        : offset(offset)
    // , coef(coef)
    {}
    LCCSLinExpr(const LCCSVar &var) {
        items[var.id] = LCCSLinItem(var);
        offset = 0;
    }

    LCCSLinExpr &operator+=(const LCCSLinExpr &expr) {
        for (const auto &[var_id, item] : expr.items) {
            items[var_id] += item;
        }
        offset += expr.offset;
        // coef += expr.coef;
        return *this;
    }
    LCCSLinExpr &operator+=(LCCSValue_t scalar) {
        offset += scalar;
        return *this;
    }
    LCCSLinExpr &operator+=(const LCCSVar &var) {
        items[var.id] += var;
        return *this;
    }

    LCCSValue_t total_offset() const {
        LCCSValue_t total = offset;
        for (const auto &[var_id, item] : items) {
            total += item.offset;
        }
        return total;
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss << "LCCSLinExpr(offset=" << offset << ", items={";
        for (const auto &[var_id, item] : items) {
            oss << item.coef << "*[" << var_id << "]+" << item.offset << "; ";
        }
        oss << "})";
        return oss.str();
    }
};

struct LCCSConstr {
    LCCSLinExpr expr;
    LCCSValue_t lb = 0;
    LCCSValue_t ub = 0;

    LCCSSize_t id; // Unique identifier for the constraint
    std::string name;

    std::string to_string() const {
        std::ostringstream oss;
        oss << "LCCSConstr(" << name << " lb=" << lb << ", ub=" << ub << ", expr={";
        for (const auto &[var_id, item] : expr.items) {
            oss << item.coef << "*[" << var_id << "]+" << item.offset << "; ";
        }
        oss << "+ " << expr.offset << "})";
        return oss.str();
    }
};

class LCCSModel {
  public:
    std::vector<LCCSConstr> constrs;
    std::vector<LCCSVar> vars;
    std::vector<LCCSSize_t> obss;
    LCCSLinExpr objective;
    LCCSType_t sense;

    LCCSSize_t var_id = 0;
    LCCSSize_t constr_id = 0;

    LCCSVar addVar(LCCSValue_t lb, LCCSValue_t ub, LCCSValue_t coef, LCCSType_t type,
                   const std::string &name = "") {
        vars.push_back({lb, ub, coef, type, var_id++, name});
        return vars.back();
    }

    LCCSConstr addConstr(LCCSValue_t lb, LCCSLinExpr expr, LCCSValue_t ub,
                         const std::string &name = "") {
        constrs.push_back({expr, lb, ub, constr_id++, name});
        return constrs.back();
    }

    LCCSConstr addObs(LCCSLinExpr expr, const std::string &name = "") {
        obss.push_back(constr_id);
        constrs.push_back({expr, LCCS_VALUE_N_INF, LCCS_VALUE_P_INF, constr_id++, name});
        return constrs.back();
    }

    void setObjective(LCCSLinExpr expr, LCCSType_t sense = LCCS_MINIMIZE) {
        objective = expr;
        this->sense = sense;
    }

    void setObjective(LCCSType_t sense = LCCS_MINIMIZE) {
        objective = LCCSLinExpr(0); // Reset objective to zero
        for (const auto &var : vars) {
            objective.items[var.id] = LCCSLinItem(var.obj_coef, 0);
        }
        this->sense = sense;
    }

    void optimize() {
        // Optimization logic goes here
        // This is a placeholder for the actual optimization algorithm
        // std::cout << "Optimizing model with " << vars.size() << " variables and " << constrs.size()
        //           << " constraints." << std::endl;
    }
    void write(const std::string &filename) const {
        // Write model to a file (e.g., LP format)
        std::ofstream ofs(filename);
        if (!ofs) {
            throw std::runtime_error("Failed to open file for writing: " + filename);
        }

        ofs << (sense == LCCS_MINIMIZE ? "Minimize" : "Maximize") << "\n";
        ofs << objective.to_string() << "\n";
        ofs << "Subject To\n";
        for (const auto &constr : constrs) {
            ofs << std::setw(8) << std::left << constr.id << " " << constr.to_string() << "\n";
            ;
        }
        ofs << "Bounds\n";
        for (const auto &var : vars) {
            ofs << var.to_string() << "\n";
        }
        ofs << "End\n";
    }
};

// LCCSLinExpr (+-*/) scalar
inline LCCSLinExpr operator+(const LCCSLinExpr &expr, LCCSValue_t scalar) {
    LCCSLinExpr result = expr;
    result.offset += scalar;
    return result;
}
inline LCCSLinExpr operator-(const LCCSLinExpr &expr, LCCSValue_t scalar) {
    return expr + (-scalar);
}

inline LCCSLinExpr operator*(const LCCSLinExpr &expr, LCCSValue_t scalar) {
    LCCSLinExpr result = expr;
    for (auto &[var_id, item] : result.items) {
        item *= scalar;
    }
    result.offset *= scalar;
    // result.coef *= scalar;
    return result;
}

// LCCSLinExpr =(+-*/) scalar
inline LCCSLinExpr &operator/=(LCCSLinExpr &expr, LCCSValue_t scalar) {

    for (auto &[var_id, item] : expr.items) {
        item /= scalar;
    }
    expr.offset /= scalar;
    // expr.coef /= scalar;
    return expr;
}

inline LCCSLinExpr &operator*=(LCCSLinExpr &expr, LCCSValue_t scalar) {
    for (auto &[var_id, item] : expr.items) {
        item *= scalar;
    }
    expr.offset *= scalar;
    // expr.coef *= scalar;
    return expr;
}

// scalar (+-*/) LCCSLinExpr
inline LCCSLinExpr operator*(LCCSValue_t scalar, const LCCSLinExpr &expr) { return expr * scalar; }

// LCCSVar (+-*/) scalar
inline LCCSLinExpr operator*(const LCCSVar &var, LCCSValue_t scalar) {
    LCCSLinExpr expr;
    expr.items[var.id] = LCCSLinItem(scalar, 0);
    return expr;
}

// scalar (+-*/) LCCSVar
inline LCCSLinExpr operator*(LCCSValue_t scalar, const LCCSVar &var) { return var * scalar; }
inline LCCSLinExpr operator-(const LCCSVar &var, LCCSValue_t scalar) {
    LCCSLinExpr expr;
    expr.items[var.id] = LCCSLinItem(1, -scalar);
    return expr;
}
inline LCCSLinExpr operator-(LCCSValue_t scalar, const LCCSVar &var) {
    LCCSLinExpr expr;
    expr.items[var.id] = LCCSLinItem(-1, scalar);
    return expr;
}

// LCCSLinExpr (+-*/) LCCSLinExpr
inline LCCSLinExpr operator+(const LCCSLinExpr &lhs, const LCCSLinExpr &rhs) {
    LCCSLinExpr result = lhs;
    for (const auto &[var_id, item] : rhs.items) {
        result.items[var_id] += item;
    }
    result.offset += rhs.offset;
    // result.coef += rhs.coef;
    return result;
}

inline LCCSLinExpr operator-(const LCCSVar &lhs, const LCCSVar &rhs) {
    LCCSLinExpr expr;
    expr.items[lhs.id] = LCCSLinItem(1, 0);
    expr.items[rhs.id] += LCCSLinItem(-1, 0);
    return expr;
}

inline LCCSLinExpr operator-(const LCCSLinExpr &expr, const LCCSVar &var) {
    LCCSLinExpr result = expr;
    result.items[var.id] += LCCSLinItem(-1, 0);
    return result;
}


} // namespace LCCS