#ifndef WEBASSEMBLY_BROWSER_CAMERA_H_
#define WEBASSEMBLY_BROWSER_CAMERA_H_


#include <vector>
#include <iostream>
#include <string>

#include <ctime>
#include <ratio>
#include <chrono>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#endif

class Camera
{

private:

  // These work
  std::string htmlVideoId_;
  std::string htmlCanvasId_;
  const unsigned int width_;
  const unsigned int height_;
  const unsigned int depth_;
  std::vector<uint8_t> interleavedImageVector_; 

  // Need to try this
  emscripten::val videoElement_;
  emscripten::val canvasElement_;
  emscripten::val imageData_;
  
public:
  Camera(const std::string htmlVideoId, const std::string htmlCanvasId, const unsigned int width, const unsigned int height, const unsigned int depth);

  void getImageRowMajor(uint8_t planarImageVector[]);

  void getImageColumnMajor(uint8_t planarImageVector[]);

  void readImageFromCanvas(void);
 
  void copyToVector(void);

};

#ifdef __cplusplus
extern "C" {
#endif

extern void wa_initiateCamera(const char *htmlVideoId, int width, int height);

#ifdef __cplusplus
}
#endif


#endif // WEBASSEMBLY_BROWSER_CAMERA_H_