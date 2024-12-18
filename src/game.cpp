#include "game.h"
#include <random>

Game::Game() {
    grid = Grid();
    gameOver = false;
    blocks = getAllBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("resources/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("resources/rotate.mp3");
    clearSound = LoadSound("resources/clear.mp3");
}

Game::~Game() {
    UnloadMusicStream(music);
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    CloseAudioDevice();
}

void Game::draw() {
    grid.draw();
    currentBlock.draw(11, 11);

    if (nextBlock.id == 3) {
        nextBlock.draw(255, 290);
    } else if (nextBlock.id == 4) {
        nextBlock.draw(255, 280);
    } else {
        nextBlock.draw(270, 270);
    }
   
}

void Game::handleInput() {
    int keyPressed = GetKeyPressed();

    if (gameOver && keyPressed) {
        gameOver = false;
        reset();
    }

    if (keyPressed == KEY_LEFT) {
        moveBlockLeft();
    }
    else if (keyPressed == KEY_RIGHT) {
        moveBlockRight();
    }
    else if (keyPressed == KEY_DOWN) {
        updateScore(0, 1);
        moveBlockDown();
    }
    else if (keyPressed == KEY_UP) {
        rotateBlock();
    }
}

void Game::moveBlockLeft() {
    if (gameOver) { return; }
    currentBlock.move(0, -1);
    if (isBlockOutside() || !blockFits()) {
        currentBlock.move(0, 1);
    }
    
}

void Game::moveBlockRight() {
    if (gameOver) { return; }
    currentBlock.move(0, 1);
    if (isBlockOutside() || !blockFits()) {
        currentBlock.move(0, -1);
    }
}

void Game::moveBlockDown() {
    if (gameOver) { return; }
    currentBlock.move(1, 0);
    if (isBlockOutside() || !blockFits()) {
        currentBlock.move(-1, 0);
        lockBlock();
    }
}

Block Game::getRandomBlock() {
    if (blocks.empty()) {
        blocks = getAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block randomBlock = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return randomBlock;
}

std::vector<Block> Game::getAllBlocks() {
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

bool Game::isBlockOutside() {
    std::vector<Position> tiles = currentBlock.getCellPositions();

    for (Position tile : tiles) {
        if (grid.isCellOutside(tile.row, tile.column)) {
            return true;
        }
    }
    return false;
}

bool Game::blockFits() {
    std::vector<Position> tiles = currentBlock.getCellPositions();

    for (Position tile : tiles) {
        if (!grid.isCellEmpty(tile.row, tile.column)) {
            return false;
        }
    } 
    return true;
}

void Game::rotateBlock() {
    currentBlock.rotate();
    if (isBlockOutside() || !blockFits()) {
        currentBlock.undoRotation();
    } else {
        PlaySound(rotateSound);
    }
}

void Game::lockBlock() {
    std::vector<Position> tiles = currentBlock.getCellPositions();

    for (Position tile : tiles) {
        grid.grid[tile.row][tile.column] = currentBlock.id;
    }

    currentBlock = nextBlock;
    if (!blockFits()) {
        gameOver = true;
    }
    nextBlock = getRandomBlock();

    int rowsCleared = grid.clearFullRows();

    if (rowsCleared > 0) {
        PlaySound(clearSound);
        updateScore(rowsCleared, 0);
    }
}

void Game::reset() {
    grid.init();
    blocks = getAllBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    score = 0;
}

void Game::updateScore(int numLinesCleared, int moveDownPoints) {
    if (numLinesCleared == 1) {
        score += 100;
    } else if (numLinesCleared == 2) {
        score += 300;
    } else if (numLinesCleared == 3) {
        score += 500;
    }

    score += moveDownPoints;
}
