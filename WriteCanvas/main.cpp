#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#endif
#include <vector>
#include <iostream>
#include <string>

#include <memory>

void copyFromVector(const std::vector<uint8_t> &vec, emscripten::val &typedArray) {
    
    uintptr_t ptr = reinterpret_cast<uintptr_t>(vec.data());
    unsigned int length = (unsigned int)vec.size();

    std::cout << "Ptr = {" << std::to_string(ptr) << "," << std::to_string(length) << "}" << std::endl;

    emscripten::val Module = emscripten::val::global("Module");
    emscripten::val HEAPU8 = Module["HEAPU8"];
    emscripten::val subarray = HEAPU8.call<emscripten::val>("subarray", emscripten::val(ptr),emscripten::val(ptr+length));

    typedArray.call<void>("set", subarray);
}



int main()
{
    emscripten::val document = emscripten::val::global("document");
    emscripten::val canvas = document.call<emscripten::val>("getElementById", emscripten::val("canvas"));
    emscripten::val context = canvas.call<emscripten::val>("getContext", emscripten::val("2d"));

    emscripten::val image = context.call<emscripten::val>(
        "getImageData", emscripten::val(0), emscripten::val(0), emscripten::val(2), emscripten::val(2));

    emscripten::val data = image["data"];
    
    int length = 2 * 2 * 4;


    std::vector<uint8_t> myvector = {255,0,0,255,0,255,0,255,0,0,255,255,255,0,255,255};

    
    std::cout << "myvector = {" << std::to_string(myvector[0]) << ", " << std::to_string(myvector[1]) << ", " << std::to_string(myvector[2]) << ", " << std::to_string(myvector[3]) << "...}" << std::endl;

    std::cout << "Ptr = " << std::to_string(reinterpret_cast<uintptr_t>(myvector.data())) << std::endl;

    copyFromVector( myvector, data);


    image["data"].call<void>("set", data);

    context.call<void>("putImageData", image, emscripten::val(0), emscripten::val(0));

    return 0;
}