#ifndef __CUTILS_H__
#define __CUTILS_H__

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;

#if !defined (__ARGS) && !defined (__ARGC_N) && !defined (__ARGC) && !defined (ARGC) 
    #define __ARGS(X) (X)
    #define __ARGC_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, N, ...)    N == 1 ? (#_0)[0] != 0 : N
    #define __ARGC(...) __ARGS(__ARGC_N(__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))
    #define ARGC(...) __ARGC(__VA_ARGS__)
#else
    #warning "information: duplicate define macro '__ARGS or __ARGC_N or __ARGC or ARGC'
#endif

#if !defined (DEFAULTARGC)
    #define DEFAULTARGC(a, value) ((#a[0]) ? (a + 0) : value)
#else
    #warning "information: duplicate define macro 'DEFAULTARGC'
#endif

// 针对动态链接库,用它定义的符号将被导出，动态库中的函数默认是可见的。
#define public __attribute__((visibility("default")))
// 针对动态链接库,用它定义的符号将不被导出，并且不能从其它对象进行使用，动态库中的函数是被隐藏的。
#define private __attribute__((visibility("hidden")))

// #if !defined (__$NAMESPACE$__) && !defined (__NAMESPACE__)
//     #define __$NAMESPACE$__(s, Module, File, Name) Module##s##File##s##Name
//     #define __NAMESPACE__(s, Module, File, Name) __$NAMESPACE$__(s, Module, File, Name)
// #else
//     #warning "information: duplicate define macro '__$NAMESPACE$__', '__NAMESPACE__'!"
// #endif
    
// #if !defined(func)
//     // Module: 模块名称
//     // File: 文件名称不带后缀
//     // Name: 函数名
//     // s:分割符号 C语言允许的函数名分隔符只有两种(_和$)其他的不允许使用
//     #define func(s, Module, File, Name) __NAMESPACE__(s, Module, File, Name)
// #else
//     #warning "information: duplicate define macro 'func'!"
// #endif


#if !defined (init) && !defined (deinit)
    #define init(type, n) ((type *)malloc((n) * sizeof(type)))
    #define deinit(var) (free(var); var = NULL);
#else
    #warning "information: duplicate define macro 'init', 'deinit'!"
#endif

#if !defined (Stringfy)
    #define Stringfy(x) #x
#else
    #warning "information: duplicate define macro 'Stringfy'!"
#endif

#if !defined(weak) && !defined (strong)
    #define weak __attribute__((weak))
    #define strong
#else
    #warning "information: duplicate define macro 'weak', 'strong'!"
#endif


#if !defined(MINIMUM) && !defined (MAXIMUM)
    #define MINIMUM(type, x, y) ({ type __min1 = (x); type __min2 = (y); __min1 < __min2 ? __min1 : __min2; })
    #define MAXIMUM(type, x, y) ({ type __max1 = (x); type __max2 = (y); __max1 > __max2 ? __max1 : __max2; })
#else
    #warning "information: duplicate define macro 'MINIMUM', 'MAXIMUM'!"
#endif

#if !defined(_LABEL_) && !defined(__LABEL__) && !defined(___LABEL___)
    #define _LABEL_(x) _LABEL_##x
    #define __LABEL__(x) _LABEL_(x)
    #define ___LABEL___ __LABEL__(__LINE__)
#else
    #warning "information: duplicate define macro '_LABEL_', '__LABEL__', '___LABEL___'!"
#endif

#if !defined(DeferBegin) && !defined(defer) && !defined(DeferEnd)
    #define DeferBegin(number)\
        void * _defers_[number];\
        void * _run_;\
        int _index_ = 0;\
        int _number_ = number;\

    #define defer(code) \
        if (_index_ > _number_ - 1) {\
            printf("number too smaller!");\
            abort();\
        };\
        _defers_[_index_ ++] = && ___LABEL___;\
        if (0) {\
            ___LABEL___:code;\
            if (_index_ --) goto *_defers_[_index_];\
            else goto *_run_;\
        }

    #define DeferEnd()\
        _run_ = && ___LABEL___;\
        if (_index_--)\
            goto *_defers_[_index_];\
        ___LABEL___:
#else
    #warning "information: duplicate define macro 'DeferBegin', 'defer', 'DeferEnd'!"
#endif

#if !defined(BIT_GET) && !defined(BIT_NOT) && !defined(BIT_SET0) && !defined(BIT_SET1)
    #define BIT_GET(n, p)  ((n) >> (p)&1)
    #define BIT_NOT(n, p)  ((n) ^= 1<<(p))
    #define BIT_SET0(n, p) ((n) &= ~(1<<(p)))
    #define BIT_SET1(n, p) ((n)|= 1<<(p))
#else
    #warning "information: duplicate define macro 'BIT_GET', 'BIT_NOT', 'BIT_SET0', 'BIT_SET1'!"
#endif

#if !defined(BIT_DISPLAY)
	#define BIT_DISPLAY(type, value) do {\
        type x = value;\
        uint64_t * temp = ((uint64_t *) &x);\
        for (int i = 0; i < 8 * sizeof(type); i ++) {\
		    printf("%llu", BIT_GET(*temp, i));\
	    }\
	} while(0)
#else
    #warning "information: duplicate define macro 'BIT_DISPLAY'!"
#endif

#if !defined(EXCHANGE)
    #define EXCHANGE(n1, n2) do { n1 = n1 ^ n2; n2 = n1 ^ n2; n1 = n1 ^ n2; } while(0)
#else
    #warning "information: duplicate define macro 'EXCHANGE'!"
#endif

#define  MEMORY_BIT1(x)   (*((bit*)(x)))
#define  MEMORY_BIT8(x)   (*((byte*)(x)))
#define  MEMORY_BIT16(x)  (*((word*)(x)))
#define  MEMORY_BIT32(x)  (*((dword*)(x)))
#define  MEMORY_BIT64(x)  (*((qword*)(x)))

#define  WORD_LOW(xxx)    ((byte) ((word)(var) & 255))
#define  WORD_HIGH(xxx)   ((byte) ((word)(var) >> 8))

#define FPOS( type, field ) ((dword)&((type *)0)->field)
#define FSIZ( type, field ) sizeof(((type *) 0)->field)

#define ffor(var, start, end, ...) for(int var = start; var <= end; __VA_ARGS__)

// 删除
typedef enum rm {
    rmsin,  // 单个元素
    rmdup,  // 数组元素
    rmidx,  // 位置索引
} rm_t;

// 搜索
typedef enum sc {
    scsin,  // 单个元素
    scdup,  // 数组元素
} sc_t;

// 嵌入
typedef enum is {
    issin,  // 单个元素
    isdup,  // 数组元素
} is_t;

#endif