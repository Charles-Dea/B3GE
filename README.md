## Dependencies
OpenGL

GLEW

GLFW

## Compiling
Linux x86_64:

`clang -fPIC -shared -o c/engine.x86_64.so -lGL -lGLEW -lglfw c/engine.c`

macOS x86_64:

`clang -fPIC -shared -o engine.x86_64.dylib -framework OpenGL -lglfw engine.c`

## Usage
To use the library, simply import engine and call init(). Call load_texture() for each .png file you would like to use for drawing. You can then call draw() to re-draw the frame. See function docs for details. Refer to test.py for example code.

## Class Details
Sprite:

Fields:

Name - Type - Description

x - float - X position in NDC.

y - float - Y position in NDC.

z - float - Z position in NDC.

w - float - Width in NDC.

h - float - Height in NDC.

t - int - Id of a previously loaded png file. See load_texture() for details.

Methods:

`__init__(x,y,z,w,h,t)`

Arguments:

Name - Type - Description

x - float - Initial value for x.

y - float - Initial value for y.

z - float - Initial value for z.

w - float - Initial value for w.

h - float - Initial value for h.

t - int - Initial value for t.

## Function Details
`init(window_length, window_name)`

Opens a square-shaped window and runs initialization code.

Arguments:

Name            Type        Description

window_length   int         The length of the window. Also used for the height.

window_name     bytes/str   The name of the window.

Returns:

None

Possible Exceptions:

Class                   Value

Exception               "failed to compile vertex shader"

Exception               "failed to compile fragment shader"

Exception               "failed to initialize glfw"

Exception               "failed to create window"

Exception               "shaders/vert.glsl not found"

Exception               "shaders/frag.glsl not found"

ctypes.ArgumentError    "argument 1: TypeError: 'str' object cannot be interpreted as an integer"

ctypes.ArgumentError    "argument 2: TypeError: wrong type"


`texid = load_texture(path_to_texture)

Loads a png file into memory, assigns it an id, and returns the id.

Argumens:

Name            Type        Description

path_to_texture str/bytes   The path to the png file relative to the current directory.

Returns:

Name    Type    Description

texid   int     An id used to identify the texture.

Possible Exceptions:

Class                   Value

Exception               "<file> not found"

ctypes.ArgumentError    "argument 1: TypeError: wroung type"

`draw(sprites)`

Draws a frame.

Argumenst:

Name    Type            Description

sprites list of Sprites List of sprites to be drawn.

Returns:

None

Possible Exceptions:

None
