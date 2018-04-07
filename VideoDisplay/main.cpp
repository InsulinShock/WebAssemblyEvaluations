#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#endif
#include <vector>
#include <iostream>
#include <string>

#include <memory>

#include "Canvas2dDisplay.hpp"

using namespace emscripten;


/*
void one_iter(void* canvas) 
{
    uint8_t img[9] = {255,0,0,0,0,0,0,0,0};

    ((Canvas2dDisplay*)canvas).putImageRowMajor(img);
};
*/


int main()
{

    uint8_t img[9] = {255,0,0,0,0,0,0,0,0};

    Canvas2dDisplay canvas = Canvas2dDisplay(3, 3);


    //canvas.putImageRowMajor(img);

    //Canvas2dDisplay *pCanvas = NULL;
    //pCanvas = &canvas;   
    
    //emscripten_set_main_loop_arg(one_iter, pCanvas, 2, 1);

    return 0;
}