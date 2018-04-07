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

#include "Canvas2dDisplay.hpp"

using namespace emscripten;




unsigned int ii = 0;


void one_iter(void* Canvas) 
{
    emscripten::val console = emscripten::val::global("console");

    uint8_t img[10000] = {};

    int jj = ii % 10000;
    img[jj] = 255;
    ii++;   

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    ((Canvas2dDisplay*)Canvas)->putImageColumnMajor(img);

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span1 = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    std::cout << "It took me" << time_span1.count() << std::endl;
};

int main()
{

    Canvas2dDisplay Canvas("canvas", 100, 100, 1);


    //canvas.putImageRowMajor(img);


    Canvas2dDisplay *pCanvas = NULL;
    pCanvas = &Canvas;   
    
    emscripten_set_main_loop_arg(one_iter, pCanvas, 30, 1);

    return 0;
}