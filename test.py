#!/usr/bin/python
import engine
engine.init(512,'B3GE')
engine.load_texture('test.png')
sprites=[engine.Sprite(-.25,.25,0,1,1,1),engine.Sprite(.25,-.25,1,1,1,1)]
for i in range(1000000000000):
    engine.draw(sprites)
