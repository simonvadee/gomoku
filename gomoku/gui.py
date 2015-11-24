#! /usr/bin/python3

import tkinter as tk

class Window(tk.Tk):


    def update(self, *args, **kwargs):
        """
        Extend the base method ``update``.
        Return ``True`` if the window is still open, return ``False``
        if the window has been destroyed.
        """
        try:
            tk.Tk.update(self, *args, **kwargs)
            return True
        except tk.TclError as err:
            if 'has been destroyed' in err.args[0]:
                return False
            else:
                raise err


class GomokuWindow(Window):

    def __init__(self, grid, width, height):
        Window.__init__(self)
        self._width = width
        self._height = height
        self.title('Gomomoku V1')

        self._canvasGrid = tk.Canvas(self)
        self._canvasGrid.pack()

        self._grid = grid
        self._beginGame = False
        
        # create window with tk

        self._canvas_controls = tk.Canvas(self)
        self._canvas_controls.pack(side='bottom')
        self._new_game_button = tk.Button(self._canvas_controls, text='New game', command=self.newGame)
        self._new_game_button.grid(column=0, row=0)
        self._options_button = tk.Button(self._canvas_controls, text='Options', command=self.optionsGui)
        self._options_button.grid(column=1, row=0)
        self._exit_button = tk.Button(self._canvas_controls, text='Exit', command=self.closeGui)
        self._exit_button.grid(column=2, row=0)
        
    def closeGui(self):
        self._canvasGrid.destroy()
        self._canvas_controls.destroy()
        self.destroy()

    def optionsGui(self):
        print("menu options")

    def newGame(self):
        self._grid.reset()
        self._grid._gridGui.reset()
        self._beginGame = True
