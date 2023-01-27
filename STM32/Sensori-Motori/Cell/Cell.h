#ifndef CELL_H
#define CELL_H
enum CellType
{
  Basic,
  Color
};

class Cell
{
private:
  CellType type;

  int x, y;

public:
    Cell(int x, int y, CellType type);
    
    int getx();
    int gety();
    
    CellType gettype();
};

#endif
