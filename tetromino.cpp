#include "tetromino.h"
#include "console/console.h"

using namespace std;
using namespace console;

// Tetromino 생성자
Tetromino::Tetromino(string name, int size, string shape) {
    name_ = name;
    size_ = size;
    for(int row = 0; row < size; row++)
        for(int col = 0; col < size; col++)
            shape_[row][col] = shape[row * size + col] == 'O' ? true : false;
    
    original_ = this;
}

// 시계 방향으로 회전한 모습의 테트로미노 객체를 반환한다.
Tetromino Tetromino::rotatedCW() {
    string newShape = "";
    for(int col = 0; col < size_; col++)
        for(int row = size_-1; row >= 0 ; row--)
            newShape += shape_[row][col] ? 'O' : 'X';
    Tetromino rotated(name_, size_, newShape);
    rotated.original_ = original_;  // 회전 하더라도 원래의 테트로미노를 기억
    return rotated;
}

// 반시계 방향으로 회전한 모습의 테트로미노 객체를 반환한다.
Tetromino Tetromino::rotatedCCW() {
    string newShape = "";
    for(int col = size_-1; col >= 0; col--)
        for(int row = 0; row < size_; row++)
            newShape += shape_[row][col] ? 'O' : 'X';
    Tetromino rotated(name_, size_, newShape);
    rotated.original_ = original_;  // 회전 하더라도 원래의 테트로미노를 기억
    return rotated;
}

// 화면의 x, y 위치에 s 문자열로 테트로미노를 그린다
void Tetromino::drawAt(string s, int x, int y) {
    int index = 0;
    for(int row = 0; row < size_; row++)
        for(int col = 0; col < size_; col++)
            if(check(row, col))
                draw(x + col + 1, y + row + 1, s);
}

// 테트로미노 선언
Tetromino Tetromino::I("I", 4, "XXXXOOOOXXXXXXXX");
Tetromino Tetromino::O("O", 2, "OOOO");
Tetromino Tetromino::T("T", 3, "XOXOOOXXX");
Tetromino Tetromino::S("S", 3, "XOOOOXXXX");
Tetromino Tetromino::Z("Z", 3, "OOXXOOXXX");
Tetromino Tetromino::J("J", 3, "OXXOOOXXX");
Tetromino Tetromino::L("L", 3, "XXOOOOXXX");