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

    uint8_t myVector[] = {255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255};

    EM_ASM_({

        let myTypedArray = new Uint8ClampedArray(16);

        var buf = Module._malloc(myTypedArray.length * myTypedArray.BYTES_PER_ELEMENT);
        Module.HEAPU8.set(myTypedArray, buf);
        //Module.ccall('my_function', 'number', ['number'], [buf]);
        Module._free(buf);

    });

    return 0;
}