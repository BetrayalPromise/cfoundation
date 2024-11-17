#define __CAT__(x, y) x ## y
#define CAT(x, y) __CAT__(x, y)

// 最多支持10个不定参数
#define SELECT(c) CAT(SELECT_, c)
#define SELECT_0(p0, ...) p0
#define SELECT_1(p0, p1, ...) p1
#define SELECT_2(p0, p1, p2, ...) p2
#define SELECT_3(p0, p1, p2, p3, ...) p3
#define SELECT_4(p0, p1, p2, p3, p4, ...) p4
#define SELECT_5(p0, p1, p2, p3, p4, p5, ...) p5
#define SELECT_6(p0, p1, p2, p3, p4, p5, p6, ...) p6
#define SELECT_7(p0, p1, p2, p3, p4, p5, p6, p7, ...) p7
#define SELECT_8(p0, p1, p2, p3, p4, p5, p6, p7, p8, ...) p8
#define SELECT_9(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, ...) p9

// 最多支持10个不定参数
#define UNSELECT(c) CAT(UNSELECT_, c)
#define UNSELECT_0(p0, ...) __VA_ARGS__
#define UNSELECT_1(p0, p1, ...) p0; __VA_ARGS__
#define UNSELECT_2(p0, p1, p2, ...) p0; p1; __VA_ARGS__
#define UNSELECT_3(p0, p1, p2, p3, ...) p0; p1; p2; __VA_ARGS__
#define UNSELECT_4(p0, p1, p2, p3, p4, ...) p0; p1; p2; p3; __VA_ARGS__
#define UNSELECT_5(p0, p1, p2, p3, p4, p5, ...) p0; p1; p2; p3; p4; __VA_ARGS__
#define UNSELECT_6(p0, p1, p2, p3, p4, p5, p6, ...) p0; p1; p2; p3; p4; p5; __VA_ARGS__
#define UNSELECT_7(p0, p1, p2, p3, p4, p5, p6, p7, ...) p0; p1; p2; p3; p4; p5; p6; __VA_ARGS__
#define UNSELECT_8(p0, p1, p2, p3, p4, p5, p6, p7, p8, ...) p0; p1; p2; p3; p4; p5; p6; p7; __VA_ARGS__
#define UNSELECT_9(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, ...) p0; p1; p2; p3; p4; p5; p6; p7; p8; __VA_ARGS__

#define IIF(c) CAT(IIF_, c)
#define IIF_1(t, ...) __VA_ARGS__
#define IIF_0(t, ...) t

#define COMPL(b) CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define GET_SEC(x, n, ...) n
#define CHECK(...) GET_SEC(__VA_ARGS__, 0)
#define PROBE(x) x, 1

#define IS_EMPTY(x) CHECK(CAT(__CAT__(IS_EMPTY_, x), 0))
#define IS_EMPTY_0 PROBE()

#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE()

#define NOT(x) CHECK(__CAT__(NOT_, x))
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

#define EMPTY()
#define DEFER(id) id EMPTY()
#define EXPAND(...) __VA_ARGS__

#define FOR_EACH(macro, x, ...) CAT(FOR_EACH_, IS_EMPTY(__VA_ARGS__)) (macro, x, __VA_ARGS__)
#define FOR_EACH_0(macro, x, ...) macro(x) DEFER(FOR_EACH_I)() (macro, __VA_ARGS__)
#define FOR_EACH_1(...) macro(x)
#define FOR_EACH_I() FOR_EACH
