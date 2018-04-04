#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#endif
#include <vector>
#include <iostream>
#include <string>

#include <memory>

using namespace emscripten;





void copyFromVector(const std::vector<uint8_t> &vec, val &typedArray) {
    
    uintptr_t ptr = reinterpret_cast<uintptr_t>(vec.data());
    unsigned int length = (unsigned int)vec.size();

    std::cout << "Ptr = {" << std::to_string(ptr) << "," << std::to_string(length) << "}" << std::endl;

    emscripten::val Module = val::global("Module");
    emscripten::val HEAPU8 = Module["HEAPU8"];
    emscripten::val subarray = HEAPU8.call<emscripten::val>("subarray", val(ptr), val(ptr+length));

    typedArray.call<void>("set", subarray);
};

template <typename T>
void copyToVector(const val &typedArray, std::vector<T> &vec) {
    unsigned int length = typedArray["length"].as<unsigned int>();
    val memory = val::module_property("buffer");

    vec.resize(length);

    val memoryView = typedArray["constructor"].new_(memory, reinterpret_cast<uintptr_t>(vec.data()), length);

    memoryView.call<void>("set", typedArray);
};

extern "C" {
    extern void createCamera(int *status, int width, int height);    

    extern void getCameraImage(const val &typedArray, int width, int height);
};



void one_iter(void* cameraStatus) {
    std::cout << "Checking camera status" << std::endl;
    if (*(int*)cameraStatus == 1){
        std::cout << "Camera Ready" << std::endl;
    }
}


struct camera {
    int status;
    val imageData;
};



int main()
{
    
    int cameraStatus = 0;
    int *pCameraStatus = NULL;
    pCameraStatus = &cameraStatus;   
    

    createCamera(pCameraStatus, 640, 480);  

    std::cout << "Completed camera setup" << std::endl;

    emscripten_set_main_loop_arg(one_iter, pCameraStatus, 60, 1);
    

    return 0;
}