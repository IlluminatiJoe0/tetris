#include "grid.h"
#include <iostream>
#include "colors.h"

Grid::Grid() {
    numRows = 20;
    numColumns = 10;
    cellSize = 30;
    init();
    colors = getCellColors();
}

void Grid::draw() {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numColumns; col++) {
            int cellValue = grid[row][col];
            DrawRectangle(col * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::isCellEmpty(int row, int column) {
    if (grid[row][column] == 0) {
        return true;
    } else {
        return false;
    }
}

bool Grid::isCellOutside(int row, int column) {
    if (row >= 0 && row < numRows && column >= 0 && column < numColumns) {
        return false;
    } else {
        return true;
    }
}

int Grid::clearFullRows() {
    int completed = 0;

    for (int row = numRows - 1; row >= 0; row--) {
        if (isRowFull(row)) {
            clearRow(row);
            completed++;
        } else if (completed > 0) {
            moveRowDown(row, completed);
        }
    }

    return completed;
}

bool Grid::isRowFull(int row) {
    for (int col = 0; col < numColumns; col++) {
        if (grid[row][col] == 0) {
            return false;
        }
    }

    return true;
}

void Grid::clearRow(int row) {
    for (int col = 0; col < numColumns; col++) {
        grid[row][col] = 0;
    }
}

void Grid::moveRowDown(int row, int numRows) {
    for (int col = 0; col < numColumns; col++) {
        grid[row + numRows][col] = grid[row][col];
        grid[row][col] = 0;
    }
}

void Grid::init() {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numColumns; col++) {
            grid[row][col] = 0;
        }
    }
}

void Grid::print() {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numColumns; col++) {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}