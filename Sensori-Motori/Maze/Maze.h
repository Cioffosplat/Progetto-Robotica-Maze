#ifndef MAZE_H
#define MAZE_H

#include "Arduino.h"

#include "../Cell/Cell.h"

const int MAZE_SIZE = 100;

class Maze
{
private:
    const Cell *maze[MAZE_SIZE][MAZE_SIZE];

public:
    Maze();
    void addNewCell(int x, int y, Cell *cell);
    bool alreadyExist(int x, int y);
};
#endif