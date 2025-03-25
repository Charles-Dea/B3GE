#!/bin/python3
import engine
import math
engine.init(1024,'B3GE')
tex=engine.load_texture('test.png')
sprites=[engine.Sprite(-.25,.25,0,1,1,tex,math.pi/4),engine.Sprite(.25,-.25,1,1,1,tex,0)]
for i in range(100):
    engine.draw(sprites)
