#!/usr/bin/python
import engine
engine.init(1024,'B3GE')
engine.load_texture(20)
sprites=[engine.Sprite(-.25,.25,0,1,1,1),engine.Sprite(.25,-.25,0,1,1,1)]
for i in range(100):
    engine.draw(sprites)
