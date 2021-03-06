# programming-kata
Miscellaneous repo to practise or implement CS stuff.

## Compilation
- Install conan.io
- `pip install -r requirements.txt`
- `mkdir build && cd build`
- `conan install ..`

### Windows
- `cmake .. -G "Visual Studio 16"`
- `cmake --build . --config Release` 

### Unix-like
- `cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release`
- `cmake --build .`
