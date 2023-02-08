import pickle
from abc import ABC

import numpy as np

from core.comunication.directions import Direction
from core.errors.errors import NoCellsMatch
from core.navigation.Coordinates import Coord
from core.navigation.Coordinates import direction_to_coord
from matrix.cell import AbstractCell
from matrix.cell import AnonymousCell


class AbstractMap(ABC):

    def __init__(self, settings):
        self.dims = settings.dims
        self.backup_dir = settings.backup_dir
        self.matrix = settings.matrix(settings)
        self.route = [Coord(self.dims[1] // 2, self.dims[2] // 2)]

    def update(self, cell: AbstractCell):
        self.current_cell = cell
        self.current_cell.set_coord(self.current_pos)

    def goto(self, direction: Direction):
        self.route.append(self.current_pos + direction_to_coord[direction.value])

    def rollback(self):
        self.route.pop()

    def bfs(self, check):
        queue = [[self.current_pos]]
        history = np.full(shape=self.dims[1:], fill_value=False, dtype=bool)
        while queue:
            element = queue.pop(0)
            if check(self.get(element[-1])):
                return element
            if history[element[-1].y][element[-1].x]:
                continue
            history[element[-1].y][element[-1].x] = True
            for neighbour in self.get(element[-1]).get_neighbours(self.matrix):
                queue.append(element + [neighbour])
        raise NoCellsMatch()

    def go_home(self):
        return self.bfs(lambda c: c.coord == self.route[0])

    def get(self, *args):
        return self.matrix.get(*args)

    def teleport(self, coord):
        self.route.append(coord)

    @property
    def current_cell(self) -> AbstractCell:
        return self.get(self.current_pos)

    @property
    def last_checkpoint(self) -> AbstractCell:
        coord = list(filter(lambda c: hasattr(c, 'checkpoint') and c.checkpoint, map(self.get, self.route)))
        if len(coord) > 0:
            print(f'from last checkpoint')
            return coord[-1]
        start = self.get(self.route[0])
        print(f'from start')
        return start

    @current_cell.setter
    def current_cell(self, value):
        self.matrix.set(self.current_pos, value)

    @property
    def current_pos(self) -> Coord:
        return self.route[-1]

    def save(self):
        with open(f'{self.backup_dir}/backup.bk', 'w+') as f:
            pickle.dump(self, f)

    @staticmethod
    def load(settings):
        with open(f'{settings.backup_dir}/backup.bk', 'w+') as f:
            return pickle.load(f)

    def print(self):
        size = self.matrix.shape
        for y in range(size[2] - 1, -1, -1):
            for x in range(size[1]):
                c = self.get(x, y)
                if isinstance(c, AnonymousCell):
                    print('   ', end='')
                else:
                    print(' ' + ('─' if c.walls[1] else '│') + ' ', end='')
            print()
            for x in range(size[1]):
                c = self.get(x, y)
                if isinstance(c, AnonymousCell):
                    print('   ', end='')
                    continue
                print('│' if c.walls[2] else '─', end='')
                if c.black:
                    print('B', end='')
                elif c.coord == self.current_pos:
                    print('P', end='')
                elif c.checkpoint:
                    print('C', end=' ')
                else:
                    print(' ', end='')
                print('│' if c.walls[0] else '─', end='')
            print()
            for x in range(size[1]):
                c = self.get(x, y)
                if isinstance(c, AnonymousCell):
                    print('   ', end='')
                else:
                    print(' ' + ('─' if c.walls[3] else '│') + ' ', end='')
            print()
        print()