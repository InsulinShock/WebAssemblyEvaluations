:: Get Emscripten
call %~dp0..\emsdk\emsdk.bat activate latest
call emcc %~dp0main.cpp --js-library %~dp0camera.js -s DEMANGLE_SUPPORT=1 -std=c++11 --bind -s WASM=1 --shell-file %~dp0main.html -o %~dp0index.html