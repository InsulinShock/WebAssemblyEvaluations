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
    canvasElement_(val::global("document").call<val>("createElement", val("canvas")))    
{    
    emscripten::val console = emscripten::val::global("console");

    
    this->videoElement_.call<void>("setAttribute", val("autoplay"), val(true));
    this->videoElement_.call<void>("setAttribute", val("id"), val(this->htmlVideoId_));
    this->videoElement_.call<void>("setAttribute", val("height"), val(this->height_));
    this->videoElement_.call<void>("setAttribute", val("width"), val(this->width_));

    val::global("document")["body"].call<void>("appendChild", this->videoElement_);





    console.call<void>("log", this->videoElement_);
/*
    console.call<void>("log", this->videoElement_);

    val constraints = val::global("Object").new_();
    constraints.set("video", val(true));
    constraints.set("audio", val(false));

    
    val navigator = val::global("navigator");
    val userMediaPromise = navigator["mediaDevices"].call<val>("getUserMedia", constraints);
    
    console.call<void>("log", userMediaPromise);


    val Function = val::global("Function");
    val thenFun = Function.new_(val("video"), val(""), val("console.log('Resolved')"));
    val catchFun = Function.new_(val("console.log('Camera access rejected')"));

    val newPromise = userMediaPromise.call<val>("then", thenFun);
    userMediaPromise.call<void>("catch", catchFun);

    console.call<void>("log", newPromise);
*/
    
    wa_initiateCamera(this->htmlVideoId_.c_str(), this->width_, this->height_);

    console.call<void>("log", this->videoElement_);

};


