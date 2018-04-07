#ifndef WEBASSEMBLY_BROWSER_CANVAS2DDISPLAY_H_
#define WEBASSEMBLY_BROWSER_CANVAS2DDISPLAY_H_

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

class Canvas2dDisplay
{

private:

  // These work
  std::string htmlId_;
  const unsigned int width_;
  const unsigned int height_;
  const unsigned int depth_;
  std::vector<uint8_t> interleavedImageVector_; 

  // Need to try this
  const emscripten::val imageData_;
  const emscripten::val canvasElement_;
  emscripten::val typedArray_;
  
public:
  Canvas2dDisplay(const std::string htmlId, const unsigned int width, const unsigned int height, const unsigned int depth);


  void putImageRowMajor(uint8_t planarImageVector[]);

  void putImageColumnMajor(uint8_t planarImageVector[]);

  void writeImageToCanvas(void);
  

};


#endif // WEBASSEMBLY_BROWSER_CANVAS2DDISPLAY_H_