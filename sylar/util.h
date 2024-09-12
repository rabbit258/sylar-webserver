#pragma once
#include <thread>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
namespace sylar{
    pid_t GetThreadId();
    uint32_t GetFiberId();
}