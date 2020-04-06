A very work in progress N64 emulator.

# Building on Windows

As usual, Windows makes building with third party libraries a giant pain. The following is an example of how to get things to work:

```
cmake -G "NMake Makefiles" -DGLEW_INCLUDE_DIR:STRING="C:\glew-2.1.0\include" -DGLEW_LIBRARY:STRING="C:\glew-2.1.0\lib\Release\x64\glew32.lib" -DGLFW_INCLUDE_DIR:STRING="C:\glfw\include" -DGLFW_LIBRARY:STRING="C:\glfw\lib-vc2017\glfw3.lib" .. 

 nmake
 ```

 ## Dependencies

 * GLEW
 * GLFW
 * Nuklear