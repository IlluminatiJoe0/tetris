#pragma once

#include "position.h"
#include <vector>
#include <map>
#include "colors.h"

class Block {
public:
    Block();
    void draw(int offsetX, int offsetY);
    void move(int row, int column);
    void rotate();
    void undoRotation();
    std::vector<Position> getCellPositions();
    int id;
    std::map<int, std::vector<Position>> cells;

private:
    int rowOffset;
    int columnOffset;
    int cellSize;
    int rotationState;
    std::vector<Color> colors;

};