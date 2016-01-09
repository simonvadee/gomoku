class Player(object):

    def __init__(self, gridGui, img=None):
        self._gridGui = gridGui
        self._img = img

    def play(self):
        self._gridGui._playing = True
        while self._gridGui._playing is True:
            self._gridGui.update()
