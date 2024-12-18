#pragma once
#include <vector>
#include "raylib.h"

class Grid {
public:
    Grid();
    int grid[20][10];
    void init();
    void print();
    void draw();
    bool isCellEmpty(int row, int column);
    bool isCellOutside(int row, int column);
    int clearFullRows();

private:
    int numRows;
    int numColumns;
    int cellSize;
    std::vector<Color> colors;
    bool isRowFull(int row);
    void clearRow(int row);
    void moveRowDown(int row, int numRows);
};