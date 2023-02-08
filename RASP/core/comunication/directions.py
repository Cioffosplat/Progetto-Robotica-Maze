from enum import Enum


class Direction(Enum):
    right = 0
    top = 1
    left = 2
    bottom = 3


int_to_direction = [Direction.right, Direction.top, Direction.left, Direction.bottom]