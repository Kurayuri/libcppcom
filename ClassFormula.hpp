#pragma once
#include <map>
#include <string>

#define LIBCPPCOM_CLASSFORMULA_PP_NARG(...)                                                        \
    LIBCPPCOM_CLASSFORMULA_PP_NARG_(__VA_ARGS__, LIBCPPCOM_CLASSFORMULA_PP_RSEQ_N())
#define LIBCPPCOM_CLASSFORMULA_PP_NARG_(...) LIBCPPCOM_CLASSFORMULA_PP_ARG_N(__VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_PP_ARG_N(                                                           \
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,     \
    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
    _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, \
    _59, _60, _61, _62, _63, _64, N, ...)                                                          \
    N
#define LIBCPPCOM_CLASSFORMULA_PP_RSEQ_N()                                                         \
    64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42,    \
        41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20,    \
        19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

// Aux: Concat
#define LIBCPPCOM_CLASSFORMULA_APPLY(macro, n) LIBCPPCOM_CLASSFORMULA_APPLY_(macro, n)
#define LIBCPPCOM_CLASSFORMULA_APPLY_(macro, n) macro##n

// Aux: Map macro to apply a function to each argument
#define LIBCPPCOM_CLASSFORMULA_MAP(macro, ...)                                                     \
    LIBCPPCOM_CLASSFORMULA_APPLY(LIBCPPCOM_CLASSFORMULA_MAP_,                                      \
                                 LIBCPPCOM_CLASSFORMULA_PP_NARG(__VA_ARGS__))(macro, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2(macro, T, ...)                                                 \
    LIBCPPCOM_CLASSFORMULA_APPLY(LIBCPPCOM_CLASSFORMULA_MAP2_,                                     \
                                 LIBCPPCOM_CLASSFORMULA_PP_NARG(__VA_ARGS__))(macro, T,            \
                                                                              __VA_ARGS__)

// Aux: Define MAP_1 to MAP_64 for up to 64 arguments
#define LIBCPPCOM_CLASSFORMULA_MAP_1(m, x) m(x)
#define LIBCPPCOM_CLASSFORMULA_MAP_2(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_1(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_3(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_2(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_4(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_3(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_5(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_4(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_6(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_5(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_7(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_6(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_8(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_7(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_9(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_8(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_10(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_9(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_11(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_10(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_12(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_11(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_13(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_12(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_14(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_13(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_15(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_14(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_16(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_15(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_17(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_16(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_18(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_17(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_19(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_18(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_20(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_19(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_21(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_20(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_22(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_21(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_23(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_22(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_24(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_23(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_25(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_24(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_26(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_25(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_27(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_26(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_28(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_27(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_29(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_28(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_30(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_29(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_31(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_30(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_32(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_31(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_33(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_32(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_34(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_33(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_35(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_34(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_36(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_35(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_37(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_36(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_38(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_37(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_39(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_38(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_40(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_39(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_41(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_40(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_42(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_41(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_43(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_42(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_44(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_43(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_45(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_44(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_46(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_45(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_47(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_46(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_48(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_47(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_49(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_48(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_50(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_49(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_51(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_50(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_52(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_51(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_53(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_52(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_54(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_53(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_55(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_54(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_56(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_55(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_57(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_56(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_58(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_57(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_59(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_58(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_60(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_59(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_61(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_60(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_62(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_61(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_63(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_62(m, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP_64(m, x, ...) m(x), LIBCPPCOM_CLASSFORMULA_MAP_63(m, __VA_ARGS__)

#define LIBCPPCOM_CLASSFORMULA_MAP2_1(m, T, x) m(T, x)
#define LIBCPPCOM_CLASSFORMULA_MAP2_2(m, T, x, ...)                                                \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_1(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_3(m, T, x, ...)                                                \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_2(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_4(m, T, x, ...)                                                \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_3(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_5(m, T, x, ...)                                                \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_4(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_6(m, T, x, ...)                                                \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_5(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_7(m, T, x, ...)                                                \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_6(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_8(m, T, x, ...)                                                \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_7(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_9(m, T, x, ...)                                                \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_8(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_10(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_9(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_11(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_10(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_12(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_11(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_13(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_12(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_14(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_13(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_15(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_14(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_16(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_15(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_17(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_16(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_18(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_17(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_19(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_18(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_20(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_19(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_21(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_20(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_22(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_21(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_23(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_22(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_24(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_23(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_25(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_24(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_26(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_25(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_27(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_26(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_28(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_27(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_29(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_28(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_30(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_29(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_31(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_30(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_32(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_31(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_33(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_32(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_34(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_33(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_35(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_34(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_36(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_35(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_37(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_36(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_38(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_37(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_39(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_38(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_40(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_39(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_41(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_40(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_42(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_41(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_43(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_42(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_44(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_43(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_45(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_44(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_46(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_45(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_47(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_46(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_48(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_47(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_49(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_48(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_50(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_49(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_51(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_50(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_52(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_51(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_53(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_52(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_54(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_53(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_55(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_54(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_56(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_55(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_57(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_56(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_58(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_57(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_59(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_58(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_60(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_59(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_61(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_60(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_62(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_61(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_63(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_62(m, T, __VA_ARGS__)
#define LIBCPPCOM_CLASSFORMULA_MAP2_64(m, T, x, ...)                                               \
    m(T, x), LIBCPPCOM_CLASSFORMULA_MAP2_63(m, T, __VA_ARGS__)

// Aux: Constructors
#define LIBCPPCOM_CLASSFORMULA_ADD_ITEM(T, x) T x
#define LIBCPPCOM_CLASSFORMULA_INIT_ITEM(x) this->x = x
#define LIBCPPCOM_CLASSFORMULA_MAKE_PAIR(x) {#x, x}

// Aux: Operators
#define LIBCPPCOM_CLASSFORMULA_OP_ADD(x) x + other.x
#define LIBCPPCOM_CLASSFORMULA_OP_SUB(x) x - other.x
#define LIBCPPCOM_CLASSFORMULA_OP_ADD_SCALAR(x) x + scalar
#define LIBCPPCOM_CLASSFORMULA_OP_SUB_SCALAR(x) x - scalar
#define LIBCPPCOM_CLASSFORMULA_OP_SCALAR_ADD_OBJ(x) scalar + obj.x
#define LIBCPPCOM_CLASSFORMULA_OP_SCALAR_SUB_OBJ(x) scalar - obj.x

// ClassFormula
#define LIBCPPCOM_CLASSFORMULA_AUTOGEN(CLASS, TYPE, ...)                                           \
  public:                                                                                          \
    CLASS(LIBCPPCOM_CLASSFORMULA_MAP2(LIBCPPCOM_CLASSFORMULA_ADD_ITEM, TYPE, __VA_ARGS__)) {       \
        LIBCPPCOM_CLASSFORMULA_MAP(LIBCPPCOM_CLASSFORMULA_INIT_ITEM, __VA_ARGS__);                 \
    }                                                                                              \
    CLASS() = default;                                                                             \
    std::map<std::string, TYPE> values() const {                                                   \
        return {LIBCPPCOM_CLASSFORMULA_MAP(LIBCPPCOM_CLASSFORMULA_MAKE_PAIR, __VA_ARGS__)};        \
    }                                                                                              \
    CLASS operator+(const CLASS &other) const {                                                    \
        return CLASS(LIBCPPCOM_CLASSFORMULA_MAP(LIBCPPCOM_CLASSFORMULA_OP_ADD, __VA_ARGS__));      \
    }                                                                                              \
    CLASS operator-(const CLASS &other) const {                                                    \
        return CLASS(LIBCPPCOM_CLASSFORMULA_MAP(LIBCPPCOM_CLASSFORMULA_OP_SUB, __VA_ARGS__));      \
    }                                                                                              \
    CLASS &operator+=(const CLASS &other) {                                                        \
        *this = *this + other;                                                                     \
        return *this;                                                                              \
    }                                                                                              \
    CLASS &operator-=(const CLASS &other) {                                                        \
        *this = *this - other;                                                                     \
        return *this;                                                                              \
    }                                                                                              \
    CLASS operator+(TYPE scalar) const {                                                           \
        return CLASS(                                                                              \
            LIBCPPCOM_CLASSFORMULA_MAP(LIBCPPCOM_CLASSFORMULA_OP_ADD_SCALAR, __VA_ARGS__));        \
    }                                                                                              \
    CLASS operator-(TYPE scalar) const {                                                           \
        return CLASS(                                                                              \
            LIBCPPCOM_CLASSFORMULA_MAP(LIBCPPCOM_CLASSFORMULA_OP_SUB_SCALAR, __VA_ARGS__));        \
    }                                                                                              \
    friend CLASS operator+(TYPE scalar, const CLASS &obj) {                                        \
        return CLASS(                                                                              \
            LIBCPPCOM_CLASSFORMULA_MAP(LIBCPPCOM_CLASSFORMULA_OP_SCALAR_ADD_OBJ, __VA_ARGS__));    \
    }                                                                                              \
    friend CLASS operator-(TYPE scalar, const CLASS &obj) {                                        \
        return CLASS(                                                                              \
            LIBCPPCOM_CLASSFORMULA_MAP(LIBCPPCOM_CLASSFORMULA_OP_SCALAR_SUB_OBJ, __VA_ARGS__));    \
    }                                                                                              \
    static CLASS None() {                                                                          \
        CLASS ans;                                                                                 \
        ans.setNone();                                                                             \
        return ans;                                                                                \
    }

// ClassFormula abstract base class
template <typename T> class ClassFormula {
  public:

    virtual ~ClassFormula() = default;

    static ClassFormula sum(const std::vector<ClassFormula> &formulas) {
        ClassFormula ans;
        for (const auto &formula : formulas) {
            ans += formula;
        }
        return ans;
    }
    T val() const { return _func(); }

    void setNone() { _isNone = true; }
    bool isNone() const { return _isNone; }
    void unsetNone() { _isNone = false; }
    double param1 = 0.0;

    LIBCPPCOM_CLASSFORMULA_AUTOGEN(ClassFormula, T, param1)

  protected:
    bool _isNone = false;

    virtual double _func() const { return param1; }
    virtual std::string _code() const { return ""; }
};