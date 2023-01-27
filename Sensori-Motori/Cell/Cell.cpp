#include "Cell.h"
Cell::Cell(int x, int y, CellType type)
{
    this->x=x;
    this->y=y;
    this->type=type;
}

int Cell::getx(){
    return x;
}

int Cell::gety(){
    return y;
}

CellType Cell::gettype()
{
  return type;
}
