#include "Maze.h"

Maze::Maze() { }

void Maze::addNewCell(int x, int y,  Cell *cell)
{
    maze[x][y] = cell;
}

bool Maze::alreadyExist(int x, int y)
{
    return maze[x][y] != NULL;
}
