#include "Canvas2dDisplay.hpp"

Canvas2dDisplay::Canvas2dDisplay(
    unsigned int width,
    unsigned int height);
{
    this->canvasElement = emscripten::val::global("document").call<emscripten::val>("getElementById", emscripten::val("canvas"));

    this->interleavedImageVector = std::vector(width * height * sizeof(uint8_t));

    uintptr_t ptr = reinterpret_cast<uintptr_t>(this->interleavedImageVector.data());

    this->typedArray = val::global("HEAPU8").call<val>("subarray", val(ptr), val(ptr + width * height * 4));

    this->imageData = val::global("ImageData").new_(val(width), val(height));
};

void Canvas2dDisplay::putImageRowMajor(uint8_t planarImageVector[]);
{

    const unsigned int width = this->imageData["width"].at<unsigned int>();
    const unsigned int height = this->imageData["height"].at<unsigned int>();
    const unsigned int redOffset = 0;
    const unsigned int greenOffset = 1;
    const unsigned int blueOffset = 2;
    const unsigned int opacityOffset = 3;
    const unsigned int depth = 1;

    switch (depth)
    {
    case 1:
        for (int column = 0; column < width; column++)
            for (int row = 0; row < height; row++)
            {
                int index = column + row * width;

                this->interleavedImageVector.at(4 * index + redOffset) = planarImageVector[index];   // red
                this->interleavedImageVector.at(4 * index + greenOffset) = planarImageVector[index]; // green
                this->interleavedImageVector.at(4 * index + blueOffset) = planarImageVector[index];  // blue
                this->interleavedImageVector.at(4 * index + opacityOffset) = 255;                    // opacity
            }
        break;

    case 3:
        break;

    case 4:
        break;
    }

    this->writeImageToCanvas();
};

void Canvas2dDisplay::putImageColumnMajor(uint8_t planarImageVector[]);
{

    const unsigned int width = this->imageData["width"].at<unsigned int>();
    const unsigned int height = this->imageData["height"].at<unsigned int>();
    const unsigned int redOffset = 0;
    const unsigned int greenOffset = 1;
    const unsigned int blueOffset = 2;
    const unsigned int opacityOffset = 3;
    const unsigned int depth = 1;

    switch (depth)
    {
    case 1:
        for (int column = 0; column < width; column++)
            for (int row = 0; row < height; row++)
            {
                int rowMajorIndex = column + row * width;
                int columnMajorIndex = column * height + row;

                this->interleavedImageVector.at(4 * rowMajorIndex + redOffset) = planarImageVector[columnMajorIndex];   // red
                this->interleavedImageVector.at(4 * rowMajorIndex + greenOffset) = planarImageVector[columnMajorIndex]; // green
                this->interleavedImageVector.at(4 * rowMajorIndex + blueOffset) = planarImageVector[columnMajorIndex];  // blue
                this->interleavedImageVector.at(4 * rowMajorIndex + opacityOffset) = 255;                               // opacity
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

    emscripten::val context = this->canvasElement.call<emscripten::val>("getContext", emscripten::val("2d"));

    this->imageData["data"].call<void>("set", this->typedArray);

    context.call<void>("putImageData", this->imageData, emscripten::val(0), emscripten::val(0));
}
