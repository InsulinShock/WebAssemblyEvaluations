#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#endif
#include <vector>
#include <iostream>
#include <string>


std::vector<std::string> *vectorFromIntPointer(uintptr_t vec)
{
    return reinterpret_cast<std::vector<std::string> *>(vec);
};

EMSCRIPTEN_BINDINGS(Wrappers)
{
    emscripten::register_vector<std::string>("VectorString").constructor(&vectorFromIntPointer, emscripten::allow_raw_pointers());
};


int main()
{

    std::vector<std::string> myVector;
    myVector.push_back("First item");
    myVector.push_back("Second item");

    EM_ASM_ARGS({
        var myVector = new Module.VectorString($0);
        // Prints "Second item"
        console.log(myVector.get(1));
    }, &myVector);

    return 0;
}