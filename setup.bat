:: Get Emscripten
call git clone https://github.com/juj/emsdk.git
call .\emsdk\emsdk.bat install latest
call .\emsdk\emsdk.bat activate latest 
call emcc --version



