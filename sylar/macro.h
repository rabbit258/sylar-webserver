#pragma once

#include<string.h>
#include<assert.h>
#include"util.h"

#if defined __GUNC__ || defined __LLVM__
#   define SYLAR_LICKLY(x)          __builtin_expect(!!(x),1)
#   define SYLAR_UNLICKLY(x)        __builtin_expect(!!(x),0)
#else 
#   define SYLAR_LICKLY(x)          (x)
#   define SYLAR_UNLICKLY(x)        (x)
#endif

#define SYLAR_ASSERT(x) \
    if(SYLAR_UNLICKLY(!(x))) { \
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ASSERTION: "#x \
            << "\nbacktrace:\n" \
            << sylar::BacktracetoString(100,2,"\t"); \
        assert(x); \
    } \

#define SYLAR_ASSERT2(x,w) \
    if(SYLAR_UNLICKLY(!(x))) { \
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ASSERTION: "#x \
            <<"\n" << w\
            << "\nbacktrace:\n" \
            << sylar::BacktracetoString(100,2,"\t"); \
        assert(x); \
    } \

