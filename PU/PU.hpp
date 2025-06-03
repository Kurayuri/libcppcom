#pragma once
#include <unordered_map>
#include <vector>

namespace PU {
using PUSize_t = std::size_t;
using PUValue_t = double;
using PUType_t = int;
inline constexpr PUValue_t PU_VALUE_INF = 1.0e30;
inline constexpr PUValue_t PU_VALUE_P_INF = 1.0e30;
inline constexpr PUValue_t PU_VALUE_N_INF = -1.0e30;

inline constexpr PUType_t PU_CONTINUOUS = 0;
inline constexpr PUType_t PU_BINARY = 1;
inline constexpr PUType_t PU_MINIMIZE = 0;
inline constexpr PUType_t PU_MAXIMIZE = 1;

struct PUVar {
    PUValue_t lb;
    PUValue_t ub;
    PUValue_t coef;

    PUType_t type;
    PUSize_t id;
};

struct PULinItem {
    PUValue_t coef;
    PUValue_t offset;

    // PUVar *var;
    PULinItem() = default;
    PULinItem(PUValue_t coef, PUValue_t offset = 0) : coef(coef), offset(offset) {}
    PULinItem(const PUVar &var) : coef(1), offset(0) {} // Assuming offset is zero for vars

    PULinItem &operator+=(const PULinItem &item) {
        coef += item.coef;
        offset += item.offset;
        return *this;
    }
    PULinItem &operator+=(PUValue_t scalar) {
        offset += scalar;
        return *this;
    }
    PULinItem &operator+=(const PUVar &var) {
        coef += 1; // TODO
        return *this;
    }
    PULinItem &operator/=(PUValue_t scalar) {
        coef /= scalar;
        offset /= scalar;
        return *this;
    }
    PULinItem &operator*=(PUValue_t scalar) {
        coef *= scalar;
        offset *= scalar;
        return *this;
    }
};

struct PULinExpr {
    std::unordered_map<PUSize_t, PULinItem> items;
    PUValue_t offset;
    PUValue_t coef;

    PULinExpr() = default;
    PULinExpr(PUValue_t offset, PUValue_t coef = 0) : offset(offset), coef(coef) {}

    PULinExpr &operator+=(const PULinExpr &expr) {
        for (const auto &[var_id, item] : expr.items) {
            items[var_id].coef += item.coef;
            items[var_id].offset += item.offset;
        }
        offset += expr.offset;
        coef += expr.coef;
        return *this;
    }
    PULinExpr &operator+=(PUValue_t scalar) {
        offset += scalar;
        return *this;
    }
    PULinExpr &operator+=(const PUVar &var) {
        items[var.id] += var;
        return *this;
    }
};

struct PUConstr {
    PULinExpr expr;
    PUValue_t lb;
    PUValue_t ub;
};

class PUModel {
  public:
    std::vector<PUConstr> constrs;
    std::vector<PUVar> vars;
    PULinExpr objective;
    PUType_t sense;

    PUSize_t var_id = 0;

    PUVar addVar(PUValue_t lb, PUValue_t ub, PUValue_t coef, PUType_t type) {
        vars.push_back({lb, ub, coef, type, var_id++});
        return vars.back();
    }

    PUConstr addConstr(PULinExpr expr, PUValue_t lb, PUValue_t ub) {
        constrs.push_back({expr, lb, ub});
        return constrs.back();
    }

    void setObjective(PULinExpr expr, PUType_t sense) {
        objective = expr;
        this->sense = sense;
    }

    void optimize() {
        // Optimization logic goes here
        // This is a placeholder for the actual optimization algorithm
        std::cout << "Optimizing model with " << vars.size() << " variables and " << constrs.size()
                  << " constraints." << std::endl;
    }
};

inline PULinExpr operator/=(PULinExpr expr, PUValue_t scalar) {
    for (auto &[var_id, item] : expr.items) {
        item /= scalar;
    }
    expr.offset /= scalar;
    expr.coef /= scalar;
    return expr;
}

inline PULinExpr operator*(const PULinExpr &expr, PUValue_t scalar) {
    PULinExpr result = expr;
    for (auto &[var_id, item] : result.items) {
        item *= scalar;
    }
    result.offset *= scalar;
    result.coef *= scalar;
    return result;
}
inline PULinExpr operator*(PUValue_t scalar, const PULinExpr &expr) { return expr * scalar; }

inline PULinExpr operator*(const PUVar &var, PUValue_t scalar) {
    PULinExpr expr;
    expr.items[var.id] = PULinItem(scalar, 0);
    return expr;
}
inline PULinExpr operator*(PUValue_t scalar, const PUVar &var) { return var * scalar; }

inline PULinExpr &operator*=(PULinExpr &expr, PUValue_t scalar) {
    for (auto &[var_id, item] : expr.items) {
        item *= scalar;
    }
    expr.offset *= scalar;
    // expr.coef *= scalar;
    return expr;
}

inline PULinExpr operator-(const PUVar &var, PUValue_t scalar) {
    PULinExpr expr;
    expr.items[var.id] = PULinItem(-1, scalar);
    return expr;
}
inline PULinExpr operator+(const PULinExpr &lhs, const PULinExpr &rhs) {
    PULinExpr result = lhs;
    for (const auto &[var_id, item] : rhs.items) {
        result.items[var_id] += item;
    }
    result.offset += rhs.offset;
    result.coef += rhs.coef;
    return result;
}

inline PULinExpr operator-(const PUVar &lhs, const PUVar &rhs) {
    PULinExpr expr;
    expr.items[lhs.id] = PULinItem(1, 0);
    expr.items[rhs.id] = PULinItem(-1, 0);
    return expr;
}

inline PULinExpr operator-(const PULinExpr &expr, const PUVar &var) {
    PULinExpr result = expr;
    result.items[var.id] += PULinItem(-1, 0);
    return result;
}

// inline PULinExpr operator+=();
} // namespace PU