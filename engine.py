import ctypes
from platform import system
from enum import Enum
class Error(Enum):
    SUCCESS=0
    VERT_FAIL=-1
    FRAG_FAIL=-2
    GLFW_INIT_FAIL=-3
    GLFW_WIN_FAIL=-4
    VERT_NOT_FOUND=-6
    FRAG_NOT_FOUND=-7
    FILE_NOT_FOUND=-9
    COMPILE_FAIL=-10
class Sprite:
    x=0.0
    y=0.0
    z=0.0
    w=0.0
    h=0.0
    t=0
    def __init__(self,x,y,z,w,h,t):
        self.x=x
        self.y=y
        self.z=z
        self.w=w
        self.h=h
        self.t=t
class SpriteC(ctypes.Structure):
    _fields_=[
            ('x',ctypes.c_double),
            ('y',ctypes.c_double),
            ('z',ctypes.c_double),
            ('w',ctypes.c_double),
            ('h',ctypes.c_double),
            ('t',ctypes.c_int)
            ]
lib=0
def init(wl,name):
    global lib
    match system():
        case'Linux':
            lib=ctypes.CDLL('c/engine.so')
        case'Darwin':
            lib=ctypes.CDLL('c/engine.dylib')
    lib.init.argtypes=(ctypes.c_int,ctypes.c_char_p)
    lib.init.restype=ctypes.c_int
    lib.loadtex.argtypes=[ctypes.c_char_p]
    lib.loadtex.restype=ctypes.c_int
    lib.draw.argtypes=(ctypes.POINTER(SpriteC),ctypes.c_int)
    if isinstance(name,str):
        n=bytes(name,'utf-8')
    else:
        n=name
    match lib.init(wl,n):
        case Error.VERT_FAIL.value:
            raise Exception('failed to compile vertex shader')
        case Error.FRAG_FAIL.value:
            raise Exception('failed to compile fragment shader')
        case Error.GLFW_INIT_FAIL.value:
            raise Exception('failed to initialize glfw')
        case Error.GLFW_WIN_FAIL.value:
            raise Exception('failed to create window')
        case Error.VERT_NOT_FOUND.value:
            raise Exception('shaders/vert.glsl not found')
        case Error.FRAG_NOT_FOUND.value:
            raise Exception('shaders/frag.glsl not found')
def load_texture(file):
    global lib
    if isinstance(file,str):
        f=bytes(file,'utf-8')
    else:
        f=file
    tex=lib.loadtex(f)
    if tex==Error.FILE_NOT_FOUND.value:
        raise Exception(file+' not found')
    return tex
def draw(s):
    global lib
    ns=len(s)
    sprites=(SpriteC*ns)()
    for i,sprt in enumerate(s):
        sprites[i]=SpriteC(x=sprt.x,y=sprt.y,z=sprt.z,w=sprt.w,h=sprt.h,t=sprt.t)
    lib.draw(sprites,ns)
