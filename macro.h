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

#define DONE() printf("a")

// #define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
// #define COMPL_0 1
// #define COMPL_1 0

// #define GET_SEC(x, n, ...) n
// #define CHECK(...) GET_SEC(__VA_ARGS__, 0)
// #define PROBE(x) x, 1


