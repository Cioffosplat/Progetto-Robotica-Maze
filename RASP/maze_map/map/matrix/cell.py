from abc import ABC, abstractmethod
from random import sample

from core.navigation.Coordinates import Coord
from core.utils.constants import *

class AbstractCell(ABC):

    @abstractmethod
    def __init__(self, walls, *args, **kwargs):
        self.coord = Coord(0, 0)
        self.walls = walls

    @abstractmethod
    def can_go(self):
        pass

    def is_adjacent(self, cell):
        return (cell.coord.x - self.coord.x, cell.coord.y - self.coord.y) in NEIGHBOURS

    def get_neighbours(self, matrix, random=False):
        neighbours = []
        if self.explored:
            iterator = sample(NEIGHBOURS, len(NEIGHBOURS)) if random else NEIGHBOURS
            for i, d in enumerate(iterator):
                if self.walls[i] == 0:
                    cell = matrix.get(self.coord + d)
                    if cell.can_go():
                        neighbours.append(self.coord + d)
        return neighbours

    def set_coord(self, coord: Coord):
        self.coord = coord

    @property
    @abstractmethod
    def explored(self):
        pass


class AnonymousCell(AbstractCell):

    def __init__(self, *args, **kwargs):
        super().__init__(None, *args, **kwargs)

    def can_go(self):
        return True

    @property
    def explored(self):
        return False