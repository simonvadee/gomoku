import numpy
import tkinter as tk

empty = 0
playerOne = 1
playerTwo = -1

class GridManager(object):
    def __init__(self, height, width):
        self._height = int(height)
        self._width = int(width)
        self._grid = numpy.zeros((self._height, self._width), dtype='int8')
        self._lastMove = None
        self.reset()
        self._dir = [
            (1, 1),
            (1, -1),
            (0, 1),
            (1, 0)
        ]


    def reset(self):
        self._grid[:] = empty
        self._freeSpace = self._height * self._width
        self._turn = playerOne


    def __getitem__(self, key):
        return self._grid[key]

    def __setitem__(self, key, value):
        if value == self._turn and self[key] == empty:
            self._turn = - self._turn
            if self._freeSpace == 0:
                # Nobody wins
                raise
            self._freeSpace -= 1
            self._lastMove = (key, value)
            self._grid[key] = value
        else:
            print("error case")
            raise

    # TODO :
    # implement functions check row, column, diagonal

    def recursDir(self, way, lastMove, valid) :
        x = lastMove[0][1] + way[0]
        y = lastMove[0][0] + way[1]
        if y in range(0, self._height) and x in range(0, self._width) and self._grid[(y, x)] == lastMove[1] :
            valid.append((y, x));
            return (self.recursDir(way, ((y, x), lastMove[1]), valid) + 1)
        return 0

    def findWinner(self):
        valid = [self._lastMove[0]]
        for elem in self._dir :
            res = 1 + self.recursDir(elem, self._lastMove, valid) + self.recursDir(tuple(scalar * (-1) for scalar in elem), self._lastMove, valid)
            if res >= 5 :
                return True
        return False
       
        """
        for each case of the grid, check horizontal vertical (2)diagonal if 5 rocks aligned
        """
        return None

class GridGui(object):
    
    def __init__(self, grid, canvas):
        
        def button_command(x,y):
            if self._playing is True:
                try:
                    self._grid[x, y] = self._grid._turn
                except Exception as e:
                    return
                self._playing = False
                background = ("black" if self._grid._turn == 1 else "red")
                self._cases[x, y].config(background=background, activebackground=background)
            
        self._playing = False
        self._grid = grid
        self._canvas = canvas
        self._cases = numpy.empty_like(grid._grid, dtype='object')
        for i in range(self._grid._height):
            for j in range(self._grid._width):
                setCase = self._cases[i,j] = tk.Button(canvas, command=lambda x=i, y=j: button_command(x,y), background="white", activebackground="white")
                setCase.grid(row=i, column=j)

    def reset(self):
        for i in range(self._grid._height):
            for j in range(self._grid._width):
                self._cases[j, i].config(background="white")

    
    def update(self, *args, **kwargs):
        try:
            tk.Canvas.update(self._canvas, *args, **kwargs)
        except tk.TclError as err:
            if 'has been destroyed' in err.args[0]:
                exit(0)
            else:
                raise err
