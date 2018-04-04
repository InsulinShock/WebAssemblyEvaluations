#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#endif
#include <iostream>
#include <string>

#include <memory>

using namespace emscripten;

int main()
{
    val Promise = val::global("Promise");

    std::cout << "OK" << std::endl;

    val Function = val::global("Function");

    std::cout << "OK" << std::endl;

    val fun = Function.new_(val("resolve"), val("reject"), val("setTimeout(() => resolve(), 10000)"));
    val thenFun = Function.new_(val("console.log('Resolved')"));
    val catchFun = Function.new_(val("console.log('Rejected')"));

    std::cout << "Starting promise..." << std::endl;

    val promise = Promise.new_(fun);
    promise.call<void>("then", thenFun);
    promise.call<void>("catch", catchFun);

    std::cout << "...Completed promise." << std::endl;

    return 0;
}