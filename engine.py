import ctypes
from enum import Enum
class Error(Enum):
    SUCCESS=0
    VERT_FAIL=1
    FRAG_FAIL=2
    GLFW_INIT_FAIL=3
    GLFW_WIN_FAIL=4
lib=ctypes.CDLL('c/engine.so')
def init(wl,name):
    global lib
    lib.init.argtypes=(ctypes.c_int,ctypes.c_char_p)
    lib.init.restype=ctypes.c_int
    if isinstance(name,str):
        name=bytes(name,'utf-8')
    match lib.init(wl,name):
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
