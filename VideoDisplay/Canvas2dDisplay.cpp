#include "Canvas2dDisplay.hpp"

using namespace emscripten;

Canvas2dDisplay::Canvas2dDisplay(
    std::string htmlId, 
    const unsigned int width, 
    const unsigned int height, 
    const unsigned int depth) : 
    htmlId_(htmlId), width_(width), height_(height), depth_(depth),
    imageData_(val::global("ImageData").new_(val(width),val(height))),
    canvasElement_(val::global("document").call<val>("getElementById",val(htmlId))),
    typedArray_(val::global("Uint8ClampedArray").new_(val(0)))
{    
    interleavedImageVector_ = std::vector<uint8_t>(width_ * height_ * 4 * sizeof(uint8_t));

    uintptr_t ptr = reinterpret_cast<uintptr_t>(this->interleavedImageVector_.data());

    this->typedArray_ = val::global("HEAPU8").call<emscripten::val>(
        "subarray",
         emscripten::val(ptr), 
         emscripten::val(ptr + this->width_ * this->height_ * 4)
         );
    
};


void Canvas2dDisplay::putImageRowMajor(uint8_t planarImageVector[])
{

    const unsigned int redOffset = 0;
    const unsigned int greenOffset = 1;
    const unsigned int blueOffset = 2;
    const unsigned int opacityOffset = 3;

    switch (this->depth_)
    {
    case 1:
        for (int column = 0; column < this->width_; column++)
            for (int row = 0; row < this->height_; row++)
            {
                int index = column + row * this->width_;

                this->interleavedImageVector_.at(4 * index + redOffset) = planarImageVector[index];   // red
                this->interleavedImageVector_.at(4 * index + greenOffset) = planarImageVector[index]; // green
                this->interleavedImageVector_.at(4 * index + blueOffset) = planarImageVector[index];  // blue
                this->interleavedImageVector_.at(4 * index + opacityOffset) = 255;                    // opacity
            }
        break;

    case 3:
        break;

    case 4:
        break;
    }

    this->writeImageToCanvas();
};

void Canvas2dDisplay::putImageColumnMajor(uint8_t planarImageVector[])
{

    const unsigned int redOffset = 0;
    const unsigned int greenOffset = 1;
    const unsigned int blueOffset = 2;
    const unsigned int opacityOffset = 3;

    switch (this->depth_)
    {
    case 1:
        for (int column = 0; column < this->width_; column++)
            for (int row = 0; row < this->height_; row++)
            {
                int rowMajorIndex = column + row * this->width_;
                int columnMajorIndex = column * this->height_ + row;

                this->interleavedImageVector_.at(4 * rowMajorIndex + redOffset) = planarImageVector[columnMajorIndex];   // red
                this->interleavedImageVector_.at(4 * rowMajorIndex + greenOffset) = planarImageVector[columnMajorIndex]; // green
                this->interleavedImageVector_.at(4 * rowMajorIndex + blueOffset) = planarImageVector[columnMajorIndex];  // blue
                this->interleavedImageVector_.at(4 * rowMajorIndex + opacityOffset) = 255;                               // opacity
            }
        break;

    case 3:
        break;

    case 4:
        break;
    }

    this->writeImageToCanvas();
}

void Canvas2dDisplay::writeImageToCanvas(void)
{

    emscripten::val context = this->canvasElement_.call<emscripten::val>(
        "getContext", 
        emscripten::val("2d")
        );

    this->imageData_["data"].call<void>(
        "set", 
        this->typedArray_
        );

    context.call<void>(
        "putImageData", 
        this->imageData_, 
        emscripten::val(0), 
        emscripten::val(0));
}

