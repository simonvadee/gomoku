#! /usr/bin/python3

import libgomoku
# import grid as libgomoku

if __name__ == '__main__':
    gameEngine = libgomoku.GridManager(19,19)
    gameEngine.loop()
