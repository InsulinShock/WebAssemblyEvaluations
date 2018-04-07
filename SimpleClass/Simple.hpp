#ifndef WEBASSEMBLY_BROWSER_CANVAS2DDISPLAY_H_
#define WEBASSEMBLY_BROWSER_CANVAS2DDISPLAY_H_


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#endif

class Simple
{

private:  
  emscripten::val a = emscripten::val("document");
public:
  Simple();

};


#endif // WEBASSEMBLY_BROWSER_CANVAS2DDISPLAY_H_