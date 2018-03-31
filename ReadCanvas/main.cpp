#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#endif
#include <vector>
#include <iostream>
#include <string>



template <typename T>
void copyToVector(const emscripten::val &typedArray, std::vector<T> &vec)
{
    unsigned int length = typedArray["length"].as<unsigned int>();
    emscripten::val memory = emscripten::val::module_property("buffer");

    vec.resize(length);

    emscripten::val memoryView = typedArray["constructor"].new_(memory, reinterpret_cast<uintptr_t>(vec.data()), length);

    memoryView.call<void>("set", typedArray);
}


int main() {

    emscripten::val document = emscripten::val::global("document");
    emscripten::val canvas = document.call<emscripten::val>("getElementById", emscripten::val("canvas"));
    emscripten::val context = canvas.call<emscripten::val>("getContext", emscripten::val("2d"));

    emscripten::val imageData = context.call<emscripten::val>(
        "getImageData", emscripten::val(0), emscripten::val(0), canvas["width"], canvas["height"]
        );

    std::vector<uint8_t> v;

    copyToVector(imageData["data"], v);

    std::cout << "Length = " << std::to_string(v.size()) << std::endl;

    return 0;
}