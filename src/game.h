#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game {
public:
    Game();
    ~Game();
    bool gameOver;
    int score;
    void draw();
    void handleInput();
    void moveBlockDown();
    Music music;


private:
    Grid grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Block getRandomBlock();
    std::vector<Block> getAllBlocks();
    bool isBlockOutside();
    bool blockFits();
    void moveBlockLeft();
    void moveBlockRight();
    void rotateBlock();
    void lockBlock();
    void reset();
    void updateScore(int numLinesCleared, int moveDownPoints);
    Sound rotateSound;
    Sound clearSound;

};