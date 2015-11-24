#! /usr/bin/python3

import grid

if __name__ == '__main__':
    main_window = grid.GridManager(19,19)
    # with ErrorHandler():
    main_window.loop()
