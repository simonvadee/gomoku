import numpy
import tkinter as tk

empty = 0
playerOne = 1
playerTwo = -1

class Grid(object):
    def __init__(self, height, width):
        self._height = int(height)
        self._width = int(width)
        self._grid = numpy.zeros((self._height, self._width), dtype='int8')
        self.reset()


    def reset(self):
        self._grid[:] = empty
        self._freeSpace = self._height * self._width
        self._turn = playerOne


    def __getitem__(self, key):
        return self._grid[key]

    def __setitem__(self, key, value):
        if value == self._turn and self[key] == empty:
            self.in_turn = - self.in_turn
            if self._freeSpace == 0:
                raise
            self._freeSpace -= 1
            self._grid[key] = value

        else:
            print("error case")


    # TODO :
    # implement functions check row, column, diagonal

    
    def findWinner(self):
        """
        for each case of the grid, check horizontal vertical (2)diagonal if 5 rocks aligned
        """
        pass


class GridGui(object):
    def __init__(self, grid, canvas):
        self._grid = grid
        self._canvas = canvas
        self._cases = numpy.empty_like(grid._grid, dtype='object')
        for i in range(self._grid._height):
            for j in range(self._grid._width):
                setCase = self._cases[i,j] = tk.Button(canvas)
                setCase.grid(row=i, column=j)



        def update(self, *args, **kwargs):
            try:
                tk.Canvas.update(self.window, *args, **kwargs)
            except tk.TclError as err:
                if 'has been destroyed' in err.args[0]:
                    exit(0)
                else:
                    raise err
