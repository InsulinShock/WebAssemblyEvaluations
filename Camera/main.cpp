#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#endif
#include <vector>
#include <iostream>
#include <string>

#include <memory>

#include <ctime>
#include <ratio>
#include <chrono>

#include "Camera.hpp"

using namespace emscripten;




unsigned int ii = 0;


void one_iter(void* Canvas) 
{
    
};

int main()
{


    Camera WebCam("video", "canvas", 640, 480, 1);


    Camera *pWebCam = NULL;
    pWebCam = &WebCam;   
    
    emscripten_set_main_loop_arg(one_iter, pWebCam, 30, 1);

    return 0;
}