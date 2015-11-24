import numpy
import tkinter as tk

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
