
#ifndef GAME_H
#define GAME_H

#include "tetromino.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define LINES 40

#define DROP_DELAY 60

class Game {
private:
  // 게임 판을 나타내는 배열
  // board[x][y]가 true 인 경우 x, y 위치에 고정된 블록이 존재하는 것을 의미한다
  bool board_[BOARD_WIDTH][BOARD_HEIGHT];
  // 현재 내려오는 테트로미노
  Tetromino current_ = Tetromino("", 0, "");
  // 현재 내려오는 테트로미노의 위치
  int current_x; int current_y;
  // 홀드한 테트로미노
  Tetromino hold_ = Tetromino("", 0, "");
  // 다음에 내려올 테트로미노
  Tetromino next_ = Tetromino("", 0, "");
  // 섀도우 테트로미노
  Tetromino shadow_ = Tetromino("", 0, "");

  // 랜덤하게 테트로미노를 하나 뽑는다.
  Tetromino randomTetromino();
  // 테트로미노를 배열에 추가한다.
  void addTetromino(Tetromino t, int x, int y);
  // 테트로미노를 배열에서 제거한다.
  void removeTetromino(Tetromino t, int x, int y);


public:
  // 게임의 한 프레임을 처리한다.
  void update();

  // 게임 화면을 그린다.
  void draw();

  // 게임 루프가 종료되어야 하는지 여부를 반환한다.
  bool shouldExit();

  Game();
};
#endif