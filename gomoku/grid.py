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
        self._lastMove = None
        # initialize window
        self._window = gui.GomokuWindow(self, self._height, self._width)
        # initialize grid gui
        self._gridGui = gridGui.GridGui(self, self._window._canvasGrid)
        # initialize players
        self._players = {-1 : player.Player(self._gridGui), 1 : player.Player(self._gridGui)}
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

    def isBreakable(self, enemyWay, coord, enemy, friendWay) :
        x = coord[1] + enemyWay[0]
        y = coord[0] + enemyWay[1]
        isBreakable = True
        count = 1
        while isBreakable :
            isBreakable = False
            if y in range(0, self._height) and x in range(0, self._width) :
                if self._grid[(y, x)] == 0 :
                    break
                elif self._grid[(y, x)] == enemy :
                    return 0
                elif self._grid[(y, x)] == -enemy :
                    if enemyWay == tuple(scalar * (-1) for scalar in friendWay) :
                        count += 1
                    isBreakable = True
            x += enemyWay[0]
            y += enemyWay[1]
        return count
    
    def checkAround(self, coord, valid, enemy, friendWay) :
        for y in range(coord[0] - 1, coord[0] + 2) :
            for x in range(coord[1] - 1, coord[1] + 2) :
                if y in range(0, self._height) and x in range(0, self._width) and self._grid[(y, x)] == enemy :
                    enemyWay = (coord[1] - x, coord[0] - y)
                    return self.isBreakable(enemyWay, coord, enemy, friendWay)
        return False

    def recursDir(self, way, lastMove, valid) :
        ret = self.checkAround(lastMove[0], valid, -lastMove[1], way)
        if ret :
            return -ret
        valid.append(lastMove)
        # check Breakable+
            # determiner way pour checker les breaks
        x = lastMove[0][1] + way[0]
        y = lastMove[0][0] + way[1]
        if y in range(0, self._height) and x in range(0, self._width) and self._grid[(y, x)] == lastMove[1] :
            valid.append((y, x));
            return (self.recursDir(way, ((y, x), lastMove[1]), valid) + 1)
        return 0

    def findWinner(self):
        valid = []
        for elem in self._dir :
            res = 1 + self.recursDir(elem, self._lastMove, valid) + self.recursDir(tuple(scalar * (-1) for scalar in elem), self._lastMove, valid)
            if res >= 5 :
                return True
        return False
       
        """
        for each case of the grid, check horizontal vertical (2)diagonal if 5 rocks aligned
        """
        return None
