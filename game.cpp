#include "game.h"
#include "console/console.h"
#include "tetromino.h"
#include <cstdlib>

using namespace console;

void Game::update() {
    
}

void Game::draw() {
    NULL;
}

bool Game::shouldExit() {
    return false;
}

Tetromino Game::randomTetromino() {
    int r = rand() % 7;
    switch (r) {
        case 0:
            return Tetromino::I;
        case 1:
            return Tetromino::O;
        case 2:
            return Tetromino::T;
        case 3:
            return Tetromino::S;
        case 4:
            return Tetromino::Z;
        case 5:
            return Tetromino::J;
        case 6:
            return Tetromino::L;
    }
}

// Game 생성자
Game::Game() {
    for(int x = 0; x < BOARD_WIDTH; x++)
        for(int y = 0; y < BOARD_HEIGHT; y++)
            board_[x][y] = false;

    current_ = randomTetromino();
    next_ = randomTetromino();
}
