#pragma once

namespace sylar {

template<class T,class X=void ,int N =0>
class Singleton{
public:
    static T * GetInstance(){
        //c++11保证线程安全
        static T v;
        return &v;
    }
};

template<class T,class X = void, int N = 0>
class SingletonPtr{
public:
    static std::shared_ptr<T> GetInstance(){
        static std::shared_ptr<T> v(new T);
        return *v;
    }
};
}