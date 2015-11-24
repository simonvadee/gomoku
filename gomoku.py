#! /usr/bin/python3

import grid

if __name__ == '__main__':
    gameEngine = grid.GridManager(19,19)
    gameEngine.loop()
