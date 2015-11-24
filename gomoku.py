#! /usr/bin/python3

import gui

if __name__ == '__main__':
    main_window = gui.GomokuWindow(19,19)
    # with ErrorHandler():
    main_window.loop()
