import numpy
import gui
import player
import gridGui

empty = 0
playerOne = 1
playerTwo = -1

class GridManager(object):
    def __init__(self, height, width):
        self._height = int(height)
        self._width = int(width)
        self._grid = numpy.zeros((self._height, self._width), dtype='int8')
        # initialize window
        self._window = gui.GomokuWindow(self, self._height, self._width)
        # initialize grid gui
        self._gridGui = gridGui.GridGui(self, self._window._canvasGrid)
        # initialize players
        self._players = {-1 : player.Player(self._gridGui), 1 : player.Player(self._gridGui)}
        self.reset()


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
                raise
            self._freeSpace -= 1
            print(key)
            self._grid[key] = value

        else:
            print("error case")
            raise

    def loop(self):

        while True:
            while not self._window._beginGame:
                self._gridGui.update()
            self._window._beginGame = False
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
            self._players[self._turn].play()
            winner = self.findWinner()
            if winner:
                return winner
            
            self._gridGui.update()
   # TODO :
    # implement functions check row, column, diagonal

    
    def findWinner(self):
        """
        for each case of the grid, check horizontal vertical (2)diagonal if 5 rocks aligned
        """
        return None
