#define PRIMITIVE_CAT(x, y) x ## y
#define CAT(x, y) PRIMITIVE_CAT(x, y)

// 最多支持10个不定参数
#define SELECT(c) CAT(SELECT_, c)
#define SELECT_0(t0, ...) t0
#define SELECT_1(t0, t1, ...) t1
#define SELECT_2(t0, t1, t2, ...) t2
#define SELECT_3(t0, t1, t2, t3, ...) t3
#define SELECT_4(t0, t1, t2, t3, t4, ...) t4
#define SELECT_5(t0, t1, t2, t3, t4, t5, ...) t5
#define SELECT_6(t0, t1, t2, t3, t4, t5, t6, ...) t6
#define SELECT_7(t0, t1, t2, t3, t4, t5, t6, t7, ...) t7
#define SELECT_8(t0, t1, t2, t3, t4, t5, t6, t7, t8, ...) t8
#define SELECT_9(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, ...) t9

// 最多支持10个不定参数
#define UNSELECT(c) CAT(UNSELECT_, c)
#define UNSELECT_0(t0, ...) __VA_ARGS__
#define UNSELECT_1(t0, t1, ...) t0; __VA_ARGS__
#define UNSELECT_2(t0, t1, t2, ...) t0; t1; __VA_ARGS__
#define UNSELECT_3(t0, t1, t2, t3, ...) t0; t1; t2; __VA_ARGS__
#define UNSELECT_4(t0, t1, t2, t3, t4, ...) t0; t1; t2; t3; __VA_ARGS__
#define UNSELECT_5(t0, t1, t2, t3, t4, t5, ...) t0; t1; t2; t3; t4; __VA_ARGS__
#define UNSELECT_6(t0, t1, t2, t3, t4, t5, t6, ...) t0; t1; t2; t3; t4; t5; __VA_ARGS__
#define UNSELECT_7(t0, t1, t2, t3, t4, t5, t6, t7, ...) t0; t1; t2; t3; t4; t5; t6; __VA_ARGS__
#define UNSELECT_8(t0, t1, t2, t3, t4, t5, t6, t7, t8, ...) t0; t1; t2; t3; t4; t5; t6; t7; __VA_ARGS__
#define UNSELECT_9(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, ...) t0; t1; t2; t3; t4; t5; t6; t7; t8; __VA_ARGS__

#define IIF(c) CAT(IIF_, c)
#define IIF_1(t, ...) __VA_ARGS__
#define IIF_0(t, ...) t

#define COMPL(b) CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define GET_SEC(x, n, ...) n
#define CHECK(...) GET_SEC(__VA_ARGS__, 0)
#define PROBE(x) x, 1

#define IS_EMPTY(x) CHECK(CAT(PRIMITIVE_CAT(IS_EMPTY_, x), 0))
#define IS_EMPTY_0 PROBE()

#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE()

#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
#define NOT_0 PROBE()

#define BOOL(x) COMPL(NOT(x))
#define IF(c) IIF(BOOL(c))

#define BOOL(x) COMPL(NOT(x))
#define IF(c) IIF(BOOL(c))

#define IF_ELSE(condition) CAT(_IF_,  BOOL(condition))
#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE

#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__