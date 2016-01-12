from player import Player
from IA import IA
from cython.view cimport array as cvarray
from cython.parallel import parallel, prange
import numpy as np
from gui import GomokuWindow
from gridGui import GridGui

empty = 0
playerOne = 1
playerTwo = 2

class GridManager(object):
    def __init__(self, height, width):
        self._playersEatenCount = {1: 0, 2: 0}
        self._height = int(height)
        self._width = int(width)
        self._grid = cvarray(shape=(19,19), itemsize=sizeof(int), format="i")
        self._grid[:] = 0
        self._lastMove = None
        self._window = GomokuWindow(self, self._height, self._width)
        self._gridGui = GridGui(self, self._window._canvasGrid)
        self._players = {1 : Player(self._gridGui), 2 : IA(self, self._gridGui)}
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

    # def __setitem__(self, key, value):
    #     # prevValue = self._grid[key]
    #     # self._grid[key] = value
    #     # if (self.doubleThreeRule(key,value) == False):
    #     #     self._grid[key] = prevValue
    #     #     print("error case")
    #     #     raise
    #     if value == self._turn and self[key] == empty:
    #         self._turn = 3 - self._turn
    #         if self._freeSpace == 0:
    #             # Nobody wins
    #             raise
    #         self._freeSpace -= 1
    #         self._lastMove = (key, value)
    #         self._grid[key] = value
    #     else:
    #         print("error case")
    #         raise


    def __setitem__(self, key, value):
        prevValue = self._grid[key]

        if value == self._turn and self[key] == empty:
            if self._freeSpace == 0:
                #Nobody wins
                raise
            self._grid[key] = value
            if (self.doubleThreeRule(key, value, -1) == False):
                print("error rule")
                self._grid[key] = prevValue
                raise
            self._turn = 3 - self._turn
            self._grid[key] = prevValue

            self._freeSpace -= 1
            self._lastMove = (key, value)
            self._grid[key] = value
        else:
            print("error case")
            raise


    def checkNeighbours(self, line, index, player, key, size):
        if (self.doubleThreeRule(key, player, index) == False):
            return False
        pos = 0
        if (index == 0):
            for x in range(key[1] - size[0], key[1] + size[1]):
                if (line[pos] == player):
                    if (x != key[1] and self.doubleThreeRule((key[0], x), player, index) == False):
                        return False
            pos += 1;
        elif (index == 1):
            for x in range(key[0] - size[0], key[0] + size[1]):
                if (int(line[pos]) == player):
                    if (x != key[0] and self.doubleThreeRule((x, key[1]), player, index) == False):
                        return False
                pos += 1;
        elif (index == 2):
            for x in range(key[1] - size[0], key[1] + size[1]):
                y = key[0] + key[1] - x
                if (int(line[pos]) == player):
                    if (x != key[1] and self.doubleThreeRule((y, x), player, index) == False):
                        return False
                pos += 1;
        elif (index == 3):
            for x in range(key[0] - size[0], key[0] + size[1]):
                y = key[1] + x - key[0]
                if (int(line[pos]) == player):
                    if (x != key[0] and self.doubleThreeRule((x, y), player, index) == False):
                        return False
                pos += 1;
        return True

    def checkDoubleThree(self, concatGrid, player, key, lineChecked):
        pool = ["01110", "010110", "011010","02220", "020220", "022020"]
        for index, line in enumerate(concatGrid):
            for elem in pool:
                pos = line.find(elem)
                if (pos != -1):
                    if (lineChecked != -1):
                        return False
                    else:
                        pos = (4 - pos, 5 - (4 - pos + 1))
                        if (self.checkNeighbours(elem, index, player, key, pos) == False):
                            return False
        return True

    def doubleThreeRule(self, key, player, lineChecked):
        """
        check if the rule of three is possible for thr current player in each direction
        """
        concatGrid = ["","","",""]
        if lineChecked != 0:
            for x in range(key[1] - 4, key[1] + 5):
                if (x < 0 or x >= self._width):
                    concatGrid[0] += "3"
                elif str(self._grid[key[0], x]).find("-1") != -1:
                    concatGrid[0] += "2"
                else:
                    concatGrid[0] += str(self._grid[key[0], x])
        if lineChecked != 1:
            for x in range(key[0] - 4, key[0] + 5):
                if (x < 0 or x >= self._height):
                    concatGrid[1] += "2"
                elif str(self._grid[x, key[1]]).find("-1") != -1:
                    concatGrid[1] += "2"
                else:
                    concatGrid[1] += str(self._grid[x, key[1]])
        if lineChecked != 2:
            for x in range(key[1] - 4, key[1] + 5):
                y = key[0] + key[1] - x
                if (x < 0 or x >= self._width or y < 0 or  y >= self._height):
                    concatGrid[2] += "3"
                elif  str(self._grid[y, x]).find("-1") != -1:
                    concatGrid[2] += "2"
                else:
                    concatGrid[2] += str(self._grid[y, x])

        if lineChecked != 3:
            for x in range(key[0] - 4, key[0] + 5):
                y = key[1] + x - key[0]
                if (x < 0 or x >= self._width or y < 0 or  y >= self._height):
                    concatGrid[3] += "3"
                elif str(self._grid[x, y]).find("-1") != -1:
                    concatGrid[3] += "2"
                else:
                    concatGrid[3] += str(self._grid[x, y])
        if (self.checkDoubleThree(concatGrid, player, key, lineChecked) == False):
            return False
        return True

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
        self.checkAround(self._lastMove[0], 3 - self._lastMove[1])

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
            if self._grid[(y, x)] == 3 - enemy :
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

    def checkAroundBreakable(self, coord, enemy, friendWay) :
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

    def recursDir(self, way, lastMove) :
        """
        checking recursively the number of pieces aligned
        """
        ret = self.checkAroundBreakable(lastMove[0], -lastMove[1], way)
        if ret :
            return 0
        x = lastMove[0][1] + way[0]
        y = lastMove[0][0] + way[1]
        if y in range(0, self._height) and x in range(0, self._width) and self._grid[(y, x)] == lastMove[1] :
            return (self.recursDir(way, ((y, x), lastMove[1])) + 1)
        return 0

    def findWinner(self, move = None):
        """
        for each case of the grid, check horizontal vertical (2)diagonal if 5 rocks aligned or if ten rocks from a team have already been eaten
        """

        if not move:
            move = self._lastMove
        if (self._playersEatenCount[playerOne] >= 10 or self._playersEatenCount[playerTwo] >= 10):
            return (playerOne if self._playersEatenCount[playerOne] >= 10 else playerTwo)
        for elem in self._dir:
            res = 1 + self.recursDir(elem, move) + self.recursDir(tuple(scalar * (-1) for scalar in elem), move)
            if res >= 5 :
                return 3 - self._turn
        return False


    def gameOver(self, winner):
        self._window.winGui(winner)
