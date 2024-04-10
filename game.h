#ifndef GAME_H
#define GAME_H

#include "tetromino.h"
#include "console/console.h"
#include <ctime>
using namespace console;

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define LINES 40

#define DROP_DELAY 60

class Game {
private:
  // 게임 판을 나타내는 배열
  // board[x][y]가 true 인 경우 x, y 위치에 고정된 블록이 존재하는 것을 의미한다
  // 실제로는 (1~BOARD_WIDTH-1, 1~BOARD_HEIGHT-1) 좌표 범위만 사용된다 (벽 제외)
  bool board_[BOARD_WIDTH][BOARD_HEIGHT];
  // 현재 내려오는 테트로미노, 그리고 위치 (x, y)
  Tetromino current_ = Tetromino("", 0, "");
  int current_x; int current_y;
  // 다음에 내려올 테트로미노
  Tetromino next_ = Tetromino("", 0, "");
  // 홀드한 테트로미노
  Tetromino hold_ = Tetromino("", 0, "");
  // 섀도우 테트로미노, 그리고 위치 (x, y)
  Tetromino shadow_ = Tetromino("", 0, "");
  int shadow_x; int shadow_y;
  // 홀드 찬스를 썼는지 여부
  bool holdChance;
  // 지워야 할 라인 개수
  int linesToClear;
  // 지운 라인 개수(점수)
  int lines;
  // 시간 관련 변수들
  clock_t startTime;    // 게임 시작 시간
  clock_t playTime;     // 현재 플레이타임
  clock_t everySecond;  // 매 초를 체크
  char time[8];         // 문자열로 변환한 현재 플레이타임 (mm:ss.ms)

  // 랜덤하게 테트로미노를 하나 뽑는다.
  Tetromino randomTetromino();
  // 테트로미노가 해당 좌표로 움직일 수 있는지 확인한다.
  // 다양한 함수에서 사용할 helper 함수임.
  bool canMove(Tetromino t, int x, int y);
  // 테트로미노가 도착한 후의 처리를 모아놓은 함수
  void afterArrival();
  // 도착한 테트로미노를 보드에 고정시키는 함수
  void addTetromino();
  // 다 채워진 줄들을 지우고, 윗 줄을 당기는 함수
  void clearLines();
  // 홀드 기능을 구현하는 함수
  void swapHold();
  // 현재 테트로미노에 대한 섀도우를 만드는 함수
  void makeShadow();
  // 입력을 받는 함수
  Key getInput();
  // 입력을 적절하게 처리하는 함수
  void processInput(Key input);


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