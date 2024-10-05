#include "sylar/uri.h"
#include <iostream>

int main(int argc,char ** argv){
    sylar::Uri::ptr uri = sylar::Uri::Create("https://www.baidu.com/test/uri?id=100&name=sylar#frg");
    std::cout << uri->toString();
    auto addr = uri->createAddress();
    std::cout << *addr <<std::endl;
    return 0;
}