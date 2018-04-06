#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#endif
#include <vector>
#include <iostream>
#include <string>

#include <ctime>
#include <ratio>
#include <chrono>

#include <memory>

using namespace emscripten;

int main()
{

    int width = 1000;
    int height = 1000;

    std::vector<uint8_t> v(height * width * 4);

    for (int ii = 0; ii < v.size(); ii += 4)
    {
        v[ii] = 255;
        v[ii + 1] = 0;
        v[ii + 2] = 255;
        v[ii + 3] = 255;
    }
    std::cout << "start" << std::endl;

    val console = val::global("console");





    uintptr_t ptr = reinterpret_cast<uintptr_t>(v.data());
    unsigned int length = (unsigned int)v.size();

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    val typedArray = val::global("HEAPU8").call<val>("subarray", val(ptr), val(ptr + length));

    console.call<void>("log", typedArray);

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    val imageData = val::global("ImageData").new_(val(width), val(height));

    std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();

    imageData["data"].call<void>("set", typedArray);

    std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();

    console.call<void>("log", imageData);

    for (int ii = 0; ii < v.size(); ii += 4)
    {
        v[ii] = 125;
        v[ii + 1] = 0;
        v[ii + 2] = 222;
        v[ii + 3] = 255;
    }
    std::cout << "end" << std::endl;

    std::chrono::high_resolution_clock::time_point t5 = std::chrono::high_resolution_clock::now();

    imageData["data"].call<void>("set", typedArray);

    std::chrono::high_resolution_clock::time_point t6 = std::chrono::high_resolution_clock::now();

    console.call<void>("log", imageData);




    std::chrono::duration<double> time_span1 = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::chrono::duration<double> time_span2 = std::chrono::duration_cast<std::chrono::duration<double>>(t3 - t2);
    std::chrono::duration<double> time_span3 = std::chrono::duration_cast<std::chrono::duration<double>>(t4 - t3);
    std::chrono::duration<double> time_span4 = std::chrono::duration_cast<std::chrono::duration<double>>(t6 - t5);

    std::cout << "It took me {" << time_span1.count() << ", " << time_span2.count() << ", " << time_span3.count() << ", " << time_span4.count() << "} seconds.";
    std::cout << std::endl;

    return 0;
}