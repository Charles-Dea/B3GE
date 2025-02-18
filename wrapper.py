from ctypes import CDLL
def init():
    lib=CDLL('./engine.so')
    lib.init()
    return lib
def draw(lib):
    lib.draw()
