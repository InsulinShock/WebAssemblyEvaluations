#ifndef WEBASSEMBLY_BROWSER_CANVAS2DDISPLAY_H_
#define WEBASSEMBLY_BROWSER_CANVAS2DDISPLAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <vector>
#include <iostream>
//#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#endif

class Canvas2dDisplay
{

private:
  std::vector<uint8_t> interleavedImageVector;
  emscripten::val typedArray;
  emscripten::val imageData;
  emscripten::val canvasElement;
  unsigned int depth;

  void writeImageToCanvas(void);

public:
  Canvas2dDisplay(unsigned int width, unsigned int height);

  void putImageRowMajor(uint8_t planarImageVector[]);

  void putImageColumnMajor(uint8_t planarImageVector[]);
};


#ifdef __cplusplus
}
#endif

#endif // WEBASSEMBLY_BROWSER_CANVAS2DDISPLAY_H_