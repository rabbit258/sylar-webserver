#pragma once
#include <thread>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <string>

namespace sylar{
pid_t GetThreadId();
uint32_t GetFiberId();

void Backtrace(std::vector<std::string> & bt,int size,int skip);
std::string BacktracetoString(int size,int skip = 2,const std::string& prefix ="");
}