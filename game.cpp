#include "game.h"
#include "console/console.h"
#include "tetromino.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace console;

void Game::update() {
    // 만약 게임이 흘러갈 수록 내려오는 속도를 빠르게 하고싶으면,  
    // 이 변수의 값에 따라 DROP_DELAY를 상수가 아닌 변수로 하여 낮추면 될 거같음
    static clock_t start = clock();  // static으로 선언하면 다음 함수 호출 시에도 값이 유지된다 !!
    clock_t end = clock();
    Key input = getInput();
    processInput(input);

    end = clock();

    // 더 이상 아래로 내려갈 수 없다면, 도착한 것으로 간주
    // 이동하던 테트로미노를 보드에 고정
    // 다 채운 줄은 지우고, 새로운 테트로미노 생성
    if(end - start > DROP_DELAY*1000/60) {  // 1초가 지났다면 테트로미노를 내려보내자.
        // 더 이상 내려갈 수 없으면, 도착 후처리(고정, 완성라인 삭제, 새로 생성)
        if(!canMove(current_, current_x, current_y+1)) {
            afterArrival();
        }
        // 아래로 내려갈 수 있다면 내려감
        else {
            processInput(K_DOWN);
        }
        start = end;
    }
}

void Game::draw() {
    drawBox(0, 0, BOARD_WIDTH+1, BOARD_HEIGHT+1);
    drawBox(BOARD_WIDTH+1+2, 0, BOARD_WIDTH+1+2+5, 5);
    drawBox(BOARD_WIDTH+1+2+5+1, 0, BOARD_WIDTH+1+2+5+1+5, 5);
    console::draw(BOARD_WIDTH+3+1, 0, "Next");
    console::draw(BOARD_WIDTH+3+5+1+1, 0, "Hold");

    shadow_.drawAt(SHADOW_STRING, shadow_x, shadow_y);
    current_.drawAt(BLOCK_STRING, current_x, current_y);
    for(int x = 0; x < BOARD_WIDTH; x++)
        for(int y = 0; y < BOARD_HEIGHT; y++)
            if(board_[x][y])
                console::draw(x+1, y+1, BLOCK_STRING);

    next_.drawAt(BLOCK_STRING, BOARD_WIDTH+1+2+(3 - next_.size() / 2) - 1, (3 - next_.size() / 2) - 1);
    hold_.drawAt(BLOCK_STRING, BOARD_WIDTH+1+2+5+1+(3 - hold_.size() / 2) - 1, (3 - hold_.size() / 2) - 1);
    console::draw(0, BOARD_HEIGHT+2, std::to_string(linesToClear-lines) + " lines left");
}

bool Game::shouldExit() {
    if(lines >= linesToClear)
        return true;
    if(current_y == 1 && !canMove(current_, current_x, current_y + 1))
        return true;
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

bool Game::canMove(Tetromino t, int x, int y) {
    for(int row = 0; row < t.size(); row++)
        for(int col = 0; col < t.size(); col++) {
            if(t.check(row, col) && (x + col < 0 || x + col >= BOARD_WIDTH || y + row >= BOARD_HEIGHT))
                return false;
            if(t.check(row, col) && board_[x + col][y + row])
                return false;
        }
    return true;
}

void Game::afterArrival() {
    addTetromino();

    current_ = next_;
    next_ = randomTetromino();
    current_x = BOARD_WIDTH / 2 - current_.size() / 2;
    current_y = 1;
    makeShadow();

    clearLines();
    holdChance = true;
}

void Game::addTetromino() {
    for(int row = 0; row < current_.size(); row++)
        for(int col = 0; col < current_.size(); col++)
            if(current_.check(row, col))
                board_[current_x + col][current_y + row] = true;
}

void Game::clearLines() {
    bool lineIsFull = true;
    int fullLineIndex;
    while(lineIsFull) {
        for(int y = 0 ; y < BOARD_HEIGHT ; y++) {
            fullLineIndex = -1;
            lineIsFull = true;
            for(int x = 0 ; x < BOARD_WIDTH ; x++)
                if(board_[x][y] == false) {
                    lineIsFull = false;
                    break;
                }
            if(lineIsFull) {
                fullLineIndex = y;
                break;
            }
        }
        // fullLineIndex가 -1이 아니라면, 한 줄이 꽉 찬거임. 한 줄을 당기도록 한다.
        if(fullLineIndex != -1) {
            for(int y = fullLineIndex; y > 0; y--)
                for(int x = 0; x < BOARD_WIDTH; x++)
                    board_[x][y] = board_[x][y-1];
            for(int x = 0; x < BOARD_WIDTH; x++)
                board_[x][0] = false;
            lines++;
        }
    }
}

void Game::swapHold() {
    Tetromino temp = hold_;
    hold_ = current_;
    // hold 되어 있던 테트로미노가 없다면(처음 홀드하는 경우)
    // 홀드에 집어넣고, 다음 테트로미노를 꺼내며 새로 진행
    if(temp.name() == "") {
        current_ = next_;
        next_ = randomTetromino();
        current_x = BOARD_WIDTH / 2 - current_.size() / 2;
        current_y = 1;
    }
    else {
        current_ = temp;
    }

    // 해당 블럭에 홀드를 사용했으므로 찬스 소모
    holdChance = false;
}

void Game::makeShadow() {
    int x = current_x;
    int y = current_y;
    while(canMove(current_, x, y+1))
        y++;
    std::string shape = "";
    for(int row = 0; row < current_.size(); row++)
        for(int col = 0; col < current_.size(); col++)
            shape += current_.check(row, col) ? "O" : "X";
    shadow_ = Tetromino(current_.name(), current_.size(), shape);
    shadow_x = x;
    shadow_y = y;
}

Key Game::getInput() {
    if(key(K_LEFT)) return K_LEFT;
    if(key(K_RIGHT)) return K_RIGHT;
    if(key(K_UP)) return K_UP;
    if(key(K_DOWN)) return K_DOWN;
    if(key(K_ESC)) return K_ESC;
    if(key(K_SPACE)) return K_SPACE;
    if(key(K_Z)) return K_Z;
    if(key(K_X)) return K_X;
    return K_NONE;
}

void Game::processInput(Key input) {
    switch (input) {
        // 아무것도 인풋이 들어오지 않으면 아무것도 하지 않음
        case K_NONE:
            break;
        // 왼쪽으로 이동이 가능하면 이동
        case K_LEFT:
            if(canMove(current_, current_x - 1, current_y)) {
                current_x--;
                makeShadow();
            }
            break;
        // 오른쪽으로 이동이 가능하면 이동
        case K_RIGHT:
            if(canMove(current_, current_x + 1, current_y)) {
                current_x++;
                makeShadow();
            }
            break;
        // 아래로 이동이 가능하면 이동 (소프트 드롭)
        case K_DOWN:
            if(canMove(current_, current_x, current_y + 1)) {
                current_y++;
            }
            break;
        // 하드 드롭 (자신이 섀도우가 됨)
        // 또한 즉시 보드에 고정
        case K_UP:
            current_ = shadow_;
            current_x = shadow_x;
            current_y = shadow_y;
            afterArrival();
            break;
        // 홀드와 바꿔치기
        case K_SPACE:
            if(holdChance) {
                swapHold();
                makeShadow();
            }
            break;
        // 시계 방향으로 회전이 가능하면 회전
        case K_X:
            if(canMove(current_.rotatedCW(), current_x, current_y)) {
                current_ = current_.rotatedCW();
                makeShadow();
            }
            break;
        // 반시계 방향으로 회전이 가능하면 회전
        case K_Z:
            if(canMove(current_.rotatedCCW(), current_x, current_y)) {
                current_ = current_.rotatedCCW();
                makeShadow();
            }
            break;
        // 게임 즉시 종료
        case K_ESC:
            exit(0);
            break;
    }

}

// Game 생성자
Game::Game() {
    std::cout << "Set lines! > ";
    std::cin >> linesToClear;
    lines = 0;

    for(int x = 0; x < BOARD_WIDTH; x++)
        for(int y = 0; y < BOARD_HEIGHT; y++)
            board_[x][y] = false;

    current_ = randomTetromino();
    next_ = randomTetromino();

    // 첫 테트로미노 생성
    current_x = BOARD_WIDTH / 2 - current_.size() / 2;
    current_y = 1;
    
    makeShadow();

    holdChance = true;
}