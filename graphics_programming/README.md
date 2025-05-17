### Using openGL in debian-based linux
1. Install `gcc` and `freeglut` using `apt`.
   ```sh
   sudo apt update -y
   sudo apt install gcc freeglut3-dev -y
   ```
2. Use the following linker flags when compiling:
   ```sh
   gcc foo.c -lGL -lGLU -lglut
   ```

### Using openGL in redhat-based linux
1. Install `gcc` and `freeglut` using `dnf`.
   ```sh
   sudo dnf install gcc freeglut-devel
   ```
2. Use the following linker flags when compiling:
   ```sh
   gcc foo.c -lGL -GLU -lglut
   ```

### Using openGL in windows
1. Install `msys2` from [https://www.msys2.org/](https://www.msys2.org/).
2. Open `MSYS2 UCRT` from the start menu.
3. Update repositories:
   ```sh
   pacman -Syu
   ```
5. Install `gcc` and `glut` from msys2 repositories:
   ```sh
   pacman -Sy mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-freeglut
   ```
6. Add `<MSYS installation dir>/ucrt64/bin` to PATH. Ensure that there is no other gcc in PATH. If you chose the default option, it would be:
   ```
   C:\msys64\ucrt64\bin
   ```
7. Use the following linker flags when compiling:
   ```sh
   gcc foo.c -lopengl32 -lglu32 -lfreeglut
   ```
8. VS code configuration (c_cpp_properties.json):
   ```json
   {
      "configurations": [
         {
               "name": "OpenGL",
               "includePath": [
                  "${workspaceFolder}/**"
               ],
               "defines": [
                  "_DEBUG",
                  "UNICODE",
                  "_UNICODE"
               ],
               "compilerPath": "C:/msys64/ucrt64/bin/gcc.exe",
               "cStandard": "c17",
               "cppStandard": "c++17",
               "intelliSenseMode": "${default}",
               "compilerArgs": [
                  "-lm",
                  "-lglu32",
                  "-lopengl32",
                  "-lfreeglut"
               ]
         }
      ],
      "version": 4
   }
   ```
