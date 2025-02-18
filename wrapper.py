import ctypes
from enum import Enum
class Error(Enum):
    SUCCESS=0
    VERT_FAIL=1
    FRAG_FAIL=2
    GLFW_INIT_FAIL=3
    GLFW_WIN_FAIL=4
lib=ctypes.CDLL('./engine.so')
def init():
    global lib
    lib.init.restype=ctypes.c_int
    match lib.init():
        case Error.VERT_FAIL.value:
            raise Exception('failed to compile vertex shader')
        case Error.FRAG_FAIL.value:
            raise Exception('failed to compile fragment shader')
        case Error.GLFW_INIT_FAIL.value:
            raise Exception('failed to initialize glfw')
        case Error.GLFW_WIN_FAIL.value:
            raise Exception('failed to create window')
def draw():
    global lib
    lib.draw()
