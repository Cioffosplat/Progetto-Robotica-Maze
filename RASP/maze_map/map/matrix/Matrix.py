from abc import ABC

import numpy as np

from core.navigation.Coordinates import Coord
from maze_map.map.map import AnonymousCell


class AbstractMatrix(ABC):

    def __init__(self, settings):
        self._dims = settings.dims
        self._cell = settings.cell
        self.level = 0
        self._matrix = np.ndarray(shape=self._dims, dtype=settings.cell)
        for h in range(self._dims[0]):
            for x in range(self._dims[1]):
                for y in range(self._dims[2]):
                    self._matrix[h][y][x] = AnonymousCell()

    def climb(self, p: int):
        self.level += p

    def get(self, *args):
        if len(args) == 1 and type(args[0]) == Coord:
            return self._matrix[self.level][args[0].y][args[0].x]
        else:
            return self._matrix[self.level][args[1]][args[0]]

    def set(self, *args):
        if len(args) == 2 and type(args[0]) == Coord:
            self._matrix[self.level][args[0].y][args[0].x] = args[1]
        else:
            self._matrix[self.level][args[1]][args[0]] = args[2]

    @property
    def shape(self):
        return self._matrix.shape