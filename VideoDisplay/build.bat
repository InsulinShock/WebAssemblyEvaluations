:: Get Emscripten
call %~dp0..\emsdk\emsdk.bat activate latest
call emcc %~dp0main.cpp %~dp0Canvas2dDisplay.cpp -std=c++11 --bind -s WASM=1 --shell-file %~dp0main.html -o %~dp0index.html