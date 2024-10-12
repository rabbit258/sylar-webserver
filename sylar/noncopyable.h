#pragma once

namespace sylar{
class Noncopyable {
public:
    Noncopyable() = default;
    ~Noncopyable() = default;
    //删掉拷贝构造函数和拷贝赋值函数
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable & operator=(const Noncopyable &) = delete;
};
}