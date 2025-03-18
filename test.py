#!/bin/python3
import engine
engine.init(1024,'B3GE')
tex=engine.load_texture('test.png')
sprites=[engine.Sprite(-.25,.25,0,1,1,tex),engine.Sprite(.25,-.25,1,1,1,tex)]
for i in range(100):
    engine.draw(sprites)
