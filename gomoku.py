#! /usr/bin/python3

import libgomoku

if __name__ == '__main__':
    gameEngine = libgomoku.GridManager(19,19)
    gameEngine.loop()
