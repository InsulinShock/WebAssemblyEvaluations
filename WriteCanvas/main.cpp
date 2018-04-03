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













//template <typename T>
//void copyFromVector(const uintptr_t &vecPtr, int length, emscripten::val &typedArray)
//{
    // unsigned int length = typedArray["length"].as<unsigned int>();
    // emscripten::val memory = emscripten::val::module_property("buffer");

    // vec.resize(length);

 //   emscripten::val subarray = typedArray.call<emscripten::val>("subarray", emscripten::val(vecPtr),emscripten::val(vecPtr+length));
 //   typedArray.call<void>("set", subarray);

    //emscripten::val memoryView = typedArray["constructor"].new_(memory, reinterpret_cast<uintptr_t>(vec.data()), length);

    //memoryView.call<void>("set", typedArray);
//}



int main()
{
    emscripten::val document = emscripten::val::global("document");
    emscripten::val canvas = document.call<emscripten::val>("getElementById", emscripten::val("canvas"));
    emscripten::val context = canvas.call<emscripten::val>("getContext", emscripten::val("2d"));

    emscripten::val image = context.call<emscripten::val>(
        "getImageData", emscripten::val(0), emscripten::val(0), emscripten::val(2), emscripten::val(2));

    emscripten::val data = image["data"];

    //uint8_t nativeData[16] = {255,0,0,255,0,255,0,255,0,0,255,255,255,0,255,255};
    //uintptr_t ptr = reinterpret_cast<uintptr_t>(nativeData);
    int length = 2 * 2 * 4;

    //std::cout << ptr << std::endl;


    std::vector<uint8_t> myvector = {255,0,0,255,0,255,0,255,0,0,255,255,255,0,255,255};

    
    std::cout << "myvector = {" << std::to_string(myvector[0]) << ", " << std::to_string(myvector[1]) << ", " << std::to_string(myvector[2]) << ", " << std::to_string(myvector[3]) << "...}" << std::endl;
    //std::cout << "Ptr = " << ptr << std::endl;
    std::cout << "Ptr = " << std::to_string(reinterpret_cast<uintptr_t>(myvector.data())) << std::endl;


    /*
    emscripten::val Module = emscripten::val::global("Module");
    emscripten::val HEAPU8 = Module["HEAPU8"];
    emscripten::val subarray = HEAPU8.call<emscripten::val>("subarray", emscripten::val(ptr),emscripten::val(ptr+length));
    data.call<void>("set", subarray);
    context.call<void>("putImageData",image, emscripten::val(0), emscripten::val(0));
    */
    
    
    copyFromVector( myvector, data);


    image["data"].call<void>("set", data);

    context.call<void>("putImageData", image, emscripten::val(0), emscripten::val(0));
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