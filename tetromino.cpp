#include "tetromino.h"
using namespace std;

// Tetromino 생성자
Tetromino::Tetromino(string name, int size, std::string shape) {
    NULL;
}

// 시계 방향으로 회전한 모습의 테트로미노 객체를 반환한다.
Tetromino Tetromino::rotatedCW() {
    NULL;
}

// 반시계 방향으로 회전한 모습의 테트로미노 객체를 반환한다.
Tetromino rotatedCCW() {
    NULL;
}

// 화면의 x, y 위치에 s 문자열로  테트로미노를 그린다
void Tetromino::drawAt(std::string s, int x, int y) {
    NULL;
}

// 테트로미노 선언
Tetromino Tetromino::I("I", 4, "XXXXOOOOXXXXXXXX");
Tetromino Tetromino::O("O", 2, "OOOO");
Tetromino Tetromino::T("T", 3, "XOXOOOXXX");
Tetromino Tetromino::S("S", 3, "XOOOOXXXX");
Tetromino Tetromino::Z("Z", 3, "OOXXOOXXX");
Tetromino Tetromino::J("J", 3, "OXXOOOXXX");
Tetromino Tetromino::L("L", 3, "XXOOOOXXX");