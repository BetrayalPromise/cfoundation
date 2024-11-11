#ifndef __CUTILS_H__
#define __CUTILS_H__

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

#if !defined (__$NAMESPACE$__) && !defined (__NAMESPACE__)
    #define __$NAMESPACE$__(s, Module, File, Name) Module##s##File##s##Name
    #define __NAMESPACE__(s, Module, File, Name) __$NAMESPACE$__(s, Module, File, Name)
#else
    #warning "information: duplicate define macro '__$NAMESPACE$__', '__NAMESPACE__'!"
#endif
    
#if !defined(func)
    // Module: 模块名称
    // File: 文件名称不带后缀
    // Name: 函数名
    // s:分割符号 C语言允许的函数名分隔符只有两种(_和$)其他的不允许使用
    #define func(s, Module, File, Name) __NAMESPACE__(s, Module, File, Name)
#else
    #warning "information: duplicate define macro 'func'!"
#endif

#if !defined ($$) && !defined (__)
    #define $$(Module, File, Name) func($, Module, File, Name)
    #define __(Module, File, Name) func(_, Module, File, Name)
#else
    #warning "information: duplicate define macro '$$', '__'!"
#endif


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

#if !defined(FlexFor)
    #define FlexFor(var, start, end, ...) for(int var = start; var <= end; __VA_ARGS__)
#else
    #warning "information: duplicate define macro 'EasyFor'!"
#endif

#if !defined(Minimum) && !defined (Maximum)
    #define Minimum(type, x, y) ({ type __min1 = (x); type __min2 = (y); __min1 < __min2 ? __min1 : __min2; })
    #define Maximum(type, x, y) ({ type __max1 = (x); type __max2 = (y); __max1 > __max2 ? __max1 : __max2; })
#else
    #warning "information: duplicate define macro 'Minimum', 'Maximum'!"
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

#if !defined(BitGet) && !defined(BitNOT) && !defined(BitSET1) && !defined(BitSET0)
    #define BitGet(n, p)  ((n) >> (p)&1)
    #define BitNOT(n, p)  ((n) ^= 1<<(p))
    #define BitSET1(n, p) ((n)|= 1<<(p))
    #define BitSET0(n, p) ((n) &= ~(1<<(p)))
#else
    #warning "information: duplicate define macro 'BitGet', 'BitNOT', 'BitSET0', 'BitSET1'!"
#endif


#if !defined(EXCHANGE)
    #define EXCHANGE(n1, n2) do { n1 = n1 ^ n2; n2 = n1 ^ n2; n1 = n1 ^ n2; } while(0)
#else
    #warning "information: duplicate define macro 'EXCHANGE'!"
#endif

// static inline void handler(void (^ * expr)(void)) { (* expr)(); }
// #define DEFER_1(x, y) x##y
// #define DEFER_2(x, y) DEFER_1(x, y)
// #define DEFER_0(x)    DEFER_2(x, __COUNTER__)
// #define defer __attribute__((cleanup(handler))) void (^ DEFER_0(option))(void) = ^

#endif