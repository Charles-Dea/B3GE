## Current State
As of right now, the project can only draw a red triangle on a black background. This was done to verify that the necessary OpenGL boilerplate was properly written. The window does not close until the program terminates. The window cannot be resized. The code has been test in both X11 and Wayland on Linux, and been verified to work. Windows and MacOS support are planned for the near future, as soon as basic functionality is achieved and I obtain access to machines for compiling and testing.

## Dependencies
OpenGL

GLEW

GLFW

## Compiling
Linux:

`clang -fPIC -shared -o engine.so -lGL -lGLEW -lglfw engine.c`

## Usage
To use the library, simply import wrapper and call init(). You can then call draw() to re-draw the frame. See function docs for details. Refer to test.py for example code.

## Function Docs
`engine = init()`

opens a window and returns an engine


`engine.draw()`

draws a frame
