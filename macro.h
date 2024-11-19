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


/*
#define FOO_  0
#define FOO_1 1

CAT(FOO_, 1)
CAT(0, 1)       参数优先展开
__CAT__(0, 1)
0##1
01

__CAT__(FOO_, 1)
__CAT__(0, 1)   按理讲应该展开为这样,但是__CAT__的参数进行了##运算,因此不再进行参数替换这一步.
__CAT__(FOO_, 1)
FOO_1
1
*/
/*
    总结,宏的参数展开优先于宏其本身
    直接宏, #define __CAT__(x, y) x ## y
    间接宏, #define CAT(x, y) __CAT__(x, y)
    有的时候我们就是希望先展开参数然后再进行拼接,需要借助一个额外的宏间接的来做这件事情.
    直接宏不会对参数x,y进行宏替换;间接宏会对参数x,y进行宏替换
*/

// #define FOO_  0
// #define FOO_1 1
// CAT(FOO_, 1)
// __CAT__(FOO_, 1)

#define IIF(c) CAT(IIF_, c)
#define IIF_0(p0, ...) __VA_ARGS__
#define IIF_1(p0, ...) p0

// 0和1互相取反
#define COMPL(b) CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0
// 检测,找到为
#define GET_SEC(x, n, ...) n
#define CHECK(...) GET_SEC(__VA_ARGS__, 0)
#define PROBE(x) x, 1
// 是否为空,空为1,非空为0.
#define IS_EMPTY(x) CHECK(CAT(CAT(IS_EMPTY_, x), 0))
#define IS_EMPTY_0  PROBE()
// 检测参数是否是括号表达式,是为1,不是为0.
#define IS_PAREN(x)         CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE()

#define NOT(x) CHECK(CAT(NOT_, x))
#define NOT_0  PROBE()

#define BOOL(x) COMPL(NOT(x))
#define IF(c)   IIF(BOOL(c))

#define IF_ELSE(condition) CAT(_IF_,  BOOL(condition))
#define _IF_1(...) __VA_ARGS__ _IF_1_ELSE
#define _IF_0(...)             _IF_0_ELSE

#define _IF_1_ELSE(...)
#define _IF_0_ELSE(...) __VA_ARGS__

// IF_ELSE(1) (x) (y);

// CHECK(PROBE())
// CHECK(knk)
// IS_EMPTY(p)
// IS_PAREN((n))

// #define BAR_I() BAR
// #define BAR() 1 BAR_I()
// BAR() ()

#define FUNCTION(name, ...) void name(__VA_ARGS__);
#define FUNCTION_TABLE(seq) CAT(FUNCTION_TABLE_1 seq, _END)
#define FUNCTION_TABLE_1(x) FUNCTION(x) FUNCTION_TABLE_2
#define FUNCTION_TABLE_2(x) FUNCTION(x) FUNCTION_TABLE_1
#define FUNCTION_TABLE_1_END
#define FUNCTION_TABLE_2_END

// FUNCTION_TABLE((x) (y));

#define EMPTY()
#define DEFER(id) id EMPTY()
#define EXPAND(...) __VA_ARGS__

// FOO()
// EXPAND(DEFER(FOO)())

// #define FOR_EACH(macro, x, ...) macro(x) DEFER(FOR_EACH_I)() (macro, __VA_ARGS__)
// #define FOR_EACH_I() FOR_EACH
// #define FOO(x) void x();
// FOR_EACH(FOO, x, y, z)
// EXPAND(FOR_EACH(FOO, x, y, z))
// EXPAND(EXPAND(FOR_EACH(FOO, x, y, z)))

#define FOR_EACH(macro, x, ...) CAT(FOR_EACH_, IS_EMPTY(__VA_ARGS__)) (macro, x, __VA_ARGS__)
#define FOR_EACH_0(macro, x, ...) macro(x) DEFER(FOR_EACH_I)() (macro, __VA_ARGS__)
#define FOR_EACH_1(...) macro(x)
#define FOR_EACH_I() FOR_EACH

// #define FOO(x) void x();
// EXPAND(EXPAND(EXPAND(FOR_EACH(FOO, x, y, u))))