#! /usr/bin/python3

import tkinter as tk
import grid
import player

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

    def __init__(self, width, height):
        Window.__init__(self)
        self.width = width
        self.height = height
        self.title('Gomomoku V1')

        self.canvasGrid = tk.Canvas(self)
        self.canvasGrid.pack()
        
        # initialize grid

        self._grid = grid.GridManager(self.width, self.height)
        self._gridGui = grid.GridGui(self._grid, self.canvasGrid)
        
        # initialize players

        self._players = {-1 : player.Player(self._gridGui), 1 : player.Player(self._gridGui)}

        # create window with tk

        self.canvas_controls = tk.Canvas(self)
        self.canvas_controls.pack(side='bottom')
        self.new_game_button = tk.Button(self.canvas_controls, text='New game', command=self.newGame)
        self.new_game_button.grid(column=0, row=0)
        self.options_button = tk.Button(self.canvas_controls, text='Options', command=self.optionsGui)
        self.options_button.grid(column=1, row=0)
        self.exit_button = tk.Button(self.canvas_controls, text='Exit', command=self.closeGui)
        self.exit_button.grid(column=2, row=0)

        self.beginGame = False
        
    def closeGui(self):
        self.canvasGrid.destroy()
        self.canvas_controls.destroy()
        self.destroy()

    def optionsGui(self):
        print("menu options")

    def newGame(self):
        self._grid.reset()
        self._gridGui.reset()
        self.beginGame = True
        
    def loop(self):

        while True:
            while not self.beginGame:
                if not self.update():
                    return
            self.beginGame = False
            winner = self.lauchGame()
            self.gameOver(winner)
            
    def lauchGame(self):

        """
        algo :

        while true:
          joueur % 2 joue
          recalcul board / update gui
          if find winner:
            break
          if error:
            throw
        """

        print("game launched")
        while True:
            self._players[self._grid._turn].play()
            winner = self._grid.findWinner()
            if winner:
                return winner
            
            self._gridGui.update()
