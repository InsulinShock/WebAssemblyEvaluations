#include "Camera.hpp"

using namespace emscripten;

Camera::Camera(
    std::string htmlVideoId, 
    std::string htmlCanvasId, 
    const unsigned int width, 
    const unsigned int height, 
    const unsigned int depth) : 
    htmlVideoId_(htmlVideoId), htmlCanvasId_(htmlCanvasId), 
    width_(width), height_(height), depth_(depth),
    videoElement_(val::global("document").call<val>("createElement", val("video"))),
    canvasElement_(val::global("document").call<val>("createElement", val("canvas"))),
    imageData_(val::global("ImageData").new_(val(width),val(height)))  
{    
    val console = val::global("console");
    
    this->videoElement_.call<void>("setAttribute", val("autoplay"), val(true));
    this->videoElement_.call<void>("setAttribute", val("id"), val(this->htmlVideoId_));
    this->videoElement_.call<void>("setAttribute", val("height"), val(this->height_));
    this->videoElement_.call<void>("setAttribute", val("width"), val(this->width_));
    this->videoElement_["style"].set("visibility", val("hidden"));

    val::global("document")["body"].call<void>("appendChild", this->videoElement_);

    this->canvasElement_.call<void>("setAttribute", val("height"), val(this->height_));
    this->canvasElement_.call<void>("setAttribute", val("width"), val(this->width_));
  
    wa_initiateCamera(this->htmlVideoId_.c_str(), this->width_, this->height_);
};

void Camera::readImageFromCanvas(void) {

    val context = this->canvasElement_.call<val>("getContext", val("2d"));

    context.call<void>("drawImage", this->videoElement_, val(0), val(0), val(this->width_), val(this->height_)); 

    this->imageData_ = context.call<val>("getImageData", val(0), val(0), val(this->width_), val(this->height_));

    this->copyToVector();
};

void Camera::getImageRowMajor(uint8_t planarImageVector[]) {

    this->readImageFromCanvas();
    
    for(int i=0; i < this->width_ * this->height_; i++) {

        planarImageVector[i] = this->interleavedImageVector_[4*i];      //red
        planarImageVector[i + this->width_ * this->height_] = 
            this->interleavedImageVector_[4*i + 1];                     // green
        planarImageVector[i + 2 * this->width_ * this->height_] = 
            this->interleavedImageVector_[4*i + 2];                     // blue

        }
};


void Camera::copyToVector(void)
{
    unsigned int length = this->imageData_["data"]["length"].as<unsigned int>();
    emscripten::val memory = emscripten::val::module_property("buffer");

    this->interleavedImageVector_.resize(length);

    emscripten::val memoryView = this->imageData_["data"]["constructor"].new_(memory, reinterpret_cast<uintptr_t>(this->interleavedImageVector_.data()), length);

    memoryView.call<void>("set", this->imageData_["data"]);
};