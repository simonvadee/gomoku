import numpy as np
import random
import time
from node import Node

class GomokuState:

    def __init__(self, board, size = 19, rootNb = 30):
        self.playerJustMoved = 2
        self.board = np.copy(board)
        self.size = size
        self.lastMove = None
        self.rootNb = rootNb
        
    def Clone(self):
        """ Create a deep clone of this game state.
        """
        st = GomokuState(np.copy(self.board))
        st.playerJustMoved = self.playerJustMoved
        st.lastMove = self.lastMove
        st.size = self.size
        return st

    def isWinningCase(self, case):
        # if can eat or can align 5
        return False

    def isLosingCase(self, case):
        # if enemy can eat, if enemy can align 5
        return False

    def isPlayableCase(self, case):
        # if case on board, if case empty, if not double three

        if (case[0] > 0) and (case[0] < len(self.board)) and (case[1] > 0) and(case[1] < len(self.board[0])) and (self.board[case] != 0x1) and (self.board[case] != 0x2):
            return True
        return False

    def calculateCaseScore(self, case):
        # can eat, can align...
        pass
    
    def evaluate(self, move):
        # check around move and modify the weight ===> to optimize
        if self.lastMove:
            print("evaluating last own move ", self.lastMove[0])
            p = self.lastMove[0]
            for case in [(p[0] - 1, p[1] - 1), (p[0] - 1, p[1]), (p[0] - 1, p[1] + 1), (p[0], p[1] - 1), (p[0], p[1] + 1), (p[0] + 1, p[1] - 1), (p[0] + 1, p[1]), (p[0] + 1, p[1] + 1)]:
                if self.isWinningCase(case):
                    pass # add winning in bitfield
                elif self.isLosingCase(case):
                    pass # add losing in bitfield
                elif self.isPlayableCase(case):
                    self.calculateCaseScore(case)
                    self.board[case] = 0xb
        print("evaluating enemy move ", move)
    
    def DoMove(self, move):
        """ Update a state by carrying out the given move.
            Must update playerJustMoved.
        """
        
        self.playerJustMoved = 3 - self.playerJustMoved
        self.board[move] = 0x1 if self.playerJustMoved == 1 else 0x2
        self.lastMove = (move, self.playerJustMoved)
        
    def GetMoves(self):
        """ Get all possible moves from this state.
        """
        # TODO : SELECT THE X BEST NODES BASED ON THE RULES AND THE PATTERN WE IDENTIFY
        moves = [(x,y) for x in range(self.size) for y in range(self.size) if self.board[x][y] == 0xb]
        if moves == []:
            moves = [(x,y) for x in range(self.size) for y in range(self.size) if self.board[x][y] == 0x0]
        return moves
        # return random.sample(moves, self.rootNb)
        
    def GetRandomMoves(self):
        """ Get all possible moves from this state.
        """
        possibleMoves = [(x,y) for x in range(self.size) for y in range(self.size) if self.board[x][y] == 0]
        if possibleMoves == []:
            return possibleMoves
        else:
            # utiliser le random de numpy si possible -> travailler avec une array simple, pas de tuple
            return random.sample(possibleMoves, len(possibleMoves))

    def GetResult(self, playerjm):
        """ Get the game result from the viewpoint of playerjm. 
        """
        return 1
  
    def __repr__(self):
        """ Don't need this - but good style.
        """
        ret = str()
        for x in range(self.size):
            for y in range(self.size):
                if self.board[(x,y)] & 0x2:
                    ret += 'X '
                elif self.board[(x,y)] & 0x1:
                    ret += '0 '
                else:
                    ret += '. '
            ret += '\n'
        return ret
    
class IA:

    def __init__(self, board, gui):
        self.board = board
        self.gui = gui
        self.state = GomokuState(self.board._grid, 19)
        

    def play(self):
        print "IA playing"
        begin = time.clock()
        print self.state.playerJustMoved
        self.state.evaluate(self.board._lastMove[0])
        m = self.UCT(itermax = 30)
        try :
            self.board[m[0], m[1]] = self.board._turn
        except:
            pass
        self.state.DoMove(m)
        self.lastMove = m
        background = ("black" if self.board._turn == 1 else "red")
        self.gui._cases[m[0], m[1]].config(background=background, activebackground=background)
        print "moving in {} [{:.3f} seconds]".format(m, time.clock() - begin)

    def UCT(self, itermax):
        """ Conduct a UCT search for itermax iterations starting from rootstate.
        Return the best move from the rootstate.
        Assumes 2 alternating players (player 1 starts), with game results in the range [0.0, 1.0]."""
    
        rootnode = Node(state = self.state)
        
        for i in range(itermax):
            node = rootnode
            state = self.state.Clone()
            
            # Select
            while node.untriedMoves == [] and node.childNodes != []: # node is fully expanded and non-terminal
                node = node.UCTSelectChild()
                state.DoMove(node.move)
                
            # Expand
            if node.untriedMoves != []: # if we can expand (i.e. state/node is non-terminal)
                m = random.choice(node.untriedMoves) 
                state.DoMove(m)
                node = node.AddChild(m,state) # add child and descend tree

            # Rollout
            moves = state.GetRandomMoves()
            for elem in moves:
                state.DoMove(elem)
                if self.board.findWinner(state.lastMove):
                    break

            # Backpropagate
            while node != None: # backpropagate from the expanded node and work back to the root node
                node.Update(state.GetResult(node.playerJustMoved)) # state is terminal. Update node with result from POV of node.playerJustMoved
                node = node.parentNode

        return sorted(rootnode.childNodes, key = lambda c: c.visits)[-1].move # return the move that was most visited
