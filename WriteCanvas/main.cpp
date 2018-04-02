#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#endif
#include <vector>
#include <iostream>
#include <string>

extern "C" {
    void my_function(uint8_t *buf)
    {
        std::cout << buf << std::endl;
    };
}





int main()
{
    emscripten::val document = emscripten::val::global("document");
    emscripten::val canvas = document.call<emscripten::val>("getElementById", emscripten::val("canvas"));
    emscripten::val context = canvas.call<emscripten::val>("getContext", emscripten::val("2d"));

    emscripten::val image = context.call<emscripten::val>(
        "getImageData", emscripten::val(0), emscripten::val(0), emscripten::val(2), emscripten::val(2));

    emscripten::val data = image["data"];

    uint8_t nativeData[16] = {255,0,0,255,0,255,0,255,0,0,255,255,255,0,255,255};
    uintptr_t ptr = reinterpret_cast<uintptr_t>(nativeData);
    int length = 2 * 2 * 4;

    std::cout << ptr << std::endl;

    emscripten::val Module = emscripten::val::global("Module");
    emscripten::val HEAPU8 = Module["HEAPU8"];
    emscripten::val subarray = HEAPU8.call<emscripten::val>("subarray", emscripten::val(ptr),emscripten::val(ptr+length));
    data.call<void>("set", subarray);
    context.call<void>("putImageData",image, emscripten::val(0), emscripten::val(0));





    //Module.HEAPU8.subarray
/*
    emscripten::val Module = emscripten::val::global("Module");
    emscripten::val dataPtr = Module.call<emscripten::val>("_malloc", emscripten::val(16));

    int ptr = (int *)dataPtr.as<int>();
    int value[] = ptr;
    //uint8_t numberPointer = ptr;

    std::cout << "Ptr: " << value[0] << std::endl;
    /*
    var buf = Module._malloc(myTypedArray.length*myTypedArray.BYTES_PER_ELEMENT);
    Module.HEAPU8.set(myTypedArray, buf);
    Module.ccall('my_function', 'number', ['number'], [buf]);
    Module._free(buf);
    */

  //  Module.call<void>("_free", dataPtr);


    return 0;
}