from enum import Enum
import numpy
import gui
import player
import gridGui

empty = 0
playerOne = 1
playerTwo = -1

class GridManager(object):
    def __init__(self, height, width):
        self._playersEatenCount = {-1: 0, 1: 0}
        self._height = int(height)
        self._width = int(width)
        self._grid = numpy.zeros((self._height, self._width), dtype='int8')
        self._lastMove = None
        self._window = gui.GomokuWindow(self, self._height, self._width)
        self._gridGui = gridGui.GridGui(self, self._window._canvasGrid)
        self._players = {-1 : player.Player(self._gridGui), 1 : player.Player(self._gridGui)}
        self._toUpdate = []
        self._dir = [
            (1, 1),
            (1, -1),
            (0, 1),
            (1, 0)
        ]
        self.reset()

    def reset(self):
        self._grid[:] = empty
        self._freeSpace = self._height * self._width
        self._turn = playerOne
        self._gridGui.reset()

    def __getitem__(self, key):
        return self._grid[key]

    def __setitem__(self, key, value):
        prevValue = self._grid[key]
        self._grid[key] = value
        if (self.doubleThreeRule(key,value) == False):
            self._grid[key] = prevValue
            raise
        self._grid[key] = prevValue

        if value == self._turn and self[key] == empty:
            self._turn = -self._turn
            if self._freeSpace == 0:
                # Nobody wins
                raise
            self._freeSpace -= 1
            self._lastMove = (key, value)
            self._grid[key] = value
        else:
            print("error case")
            raise

    def checkDoubleThree(self, concatGrid, value):
        for line in concatGrid:
            if ((value == 1 and (line.find("01110") != -1 or line.find("10110") != -1 or line.find("01101") != -1))
                or (value == -1 and (line.find("0-1-1-10") != -1 or line.find("-10-1-10") != -1 or line.find("0-1-10-1") != -1))):
                return False

        return True

    def doubleThreeRule(self, key, value):
        """
        check if the rule of three is possible for thr current player in each direction
        """
        concatGrid = ["","","",""]
        for x in range(key[1] - 5, key[1] + 5):
            if (x < 0 or x >= self._width):
                continue
            concatGrid[0] += str(self._grid[key[0], x])

        for x in range(key[0] - 5, key[0] + 5):
            if (x < 0 or x >= self._height):
                continue
            concatGrid[1] += str(self._grid[x, key[1]])

        for x in range(key[1] - 5, key[1] + 5):
            y = key[0] + key[1] - x
            if (x < 0 or x >= self._width or y < 0 or  y >= self._height):
                continue
            concatGrid[2] += str(self._grid[y, x])

        for x in range(key[0] - 5, key[0] + 5):
            y = key[1] + x - key[0]
            if (x < 0 or x >= self._width or y < 0 or  y >= self._height):
                continue
            concatGrid[3] += str(self._grid[x, y])

        if self.checkDoubleThree(concatGrid, value) == False:
            return False
        return True;

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
            self.checkEatenPieces()
            winner = self.findWinner()
            if winner:
                return winner

            self._gridGui.update()

    # Check for eat pieces

    def checkEatenPieces(self) :
        self.checkAround(self._lastMove[0], -self._lastMove[1])

    def checkAround(self, coord, enemy) :
        """
        checking around looking for pieces to eat
        """
        for y in range(coord[0] - 1, coord[0] + 2) :
            for x in range(coord[1] - 1, coord[1] + 2) :
                if y in range(0, self._height) and x in range(0, self._width) and self._grid[(y, x)] == enemy :
                    enemyWay = (x - coord[1], y - coord[0])
                    if self.tryEat(enemyWay, coord, enemy) != False:
                        self._playersEatenCount[self._turn] += 2;
                        print(self._playersEatenCount[self._turn])
        return False

    def tryEat(self, enemyWay, coord, enemy, cnt = 0) :
        """
        checking recursively the number of pieces aligned to eat
        """

        x = coord[1] + enemyWay[0]
        y = coord[0] + enemyWay[1]
        if y in range(0, self._height) and x in range(0, self._width) :
            if self._grid[(y, x)] == -enemy :
                return cnt
            elif self._grid[(y, x)] == 0 :
                return False
            else :
                res = self.tryEat(enemyWay, (y, x), enemy, cnt + 1)
                if res and res % 2 == 0 :
                    self._grid[(y, x)] = 0
                    self._toUpdate.append((y, x))
                    return res
                return False

    # Check End and Breakable

    def isBreakable(self, enemyWay, coord, enemy, friendWay) :
        """
        checking recursively the number of pieces aligned to win
        """
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

    def isPair(self, way, coord, team, cnt = 0) :
        x = coord[1] + way[0]
        y = coord[0] + way[1]
        if y in range(0, self._height) and x in range(0, self._width) :
            if self._grid[(y, x)] == team :
                return self.isPair(way, (y, x), team, cnt + 1) + 1
            elif self._grid[(y, x)] == 0 :
                return 1
            elif self._grid[(y, x)] == -team :
                return -cnt
        return 0

    def checkAroundBreakable(self, coord, valid, enemy, friendWay) :
        """
        checking around if enemy pieces can break the alignement
        """
        for y in range(coord[0] - 1, coord[0] + 2) :
            for x in range(coord[1] - 1, coord[1] + 2) :
                if y in range(0, self._height) and x in range(0, self._width) and self._grid[(y, x)] == enemy :
                    enemyWay = (coord[1] - x, coord[0] - y)
                    resPair = self.isPair(enemyWay, coord, -enemy)
                    if resPair and resPair % 2 == 0 :
                        isBreakable = self.isBreakable(enemyWay,
                                                       (coord[0] + resPair + 1, coord[1] + resPair + 1),
                                                       enemy,
                                                       friendWay)
                        if isBreakable :
                            return isBreakable
        return False

    def recursDir(self, way, lastMove, valid) :
        """
        checking recursively the number of pieces aligned
        """
        ret = self.checkAroundBreakable(lastMove[0], valid, -lastMove[1], way)
        if ret :
            return -ret
        valid.append(lastMove)
        x = lastMove[0][1] + way[0]
        y = lastMove[0][0] + way[1]
        if y in range(0, self._height) and x in range(0, self._width) and self._grid[(y, x)] == lastMove[1] :
            valid.append((y, x));
            return (self.recursDir(way, ((y, x), lastMove[1]), valid) + 1)
        return 0

    def findWinner(self):

        """
        for each case of the grid, check horizontal vertical (2)diagonal if 5 rocks aligned or id ten pawn from a team as already been eaten
        """
        if (self._playersEatenCount[playerOne] >= 10 or self._playersEatenCount[playerTwo] >= 10):
            return (playerOne if self._playersEatenCount[playerOne] >= 10 else playerTwo)
        valid = []
        for elem in self._dir :
            res = 1 + self.recursDir(elem, self._lastMove, valid) + self.recursDir(tuple(scalar * (-1) for scalar in elem), self._lastMove, valid)
            if res >= 5 :
                return -self._turn
        return False


    def gameOver(self, winner):
        self._window.winGui(winner)
