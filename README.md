- 한글 입력 상태에서 몇몇 키를 입력하면 프로그램이 죽어버리는 문제가 있습니다.
  - 영문 입력 상태에서 게임을 진행해주세요.

git clone https://github.com/orbit3230/cpp_week5_tetris tetris  
cd tetris  
mingw32-make  
./main.exe

- 조작키
  - `위 방향키(UP_ARROW)` : 하드 드롭
  - `아래 방향키(DOWN_ARROW)` : 소프트 드롭
  - `오른쪽 방향키(RIGHT_ARRAY)` : 오른쪽 이동
  - `왼쪽 방향키(LEFT_ARRAY)` : 왼쪽 이동
  - `X` : 시계방향 회전
  - `Z` : 반시계방향 회전
  - `SPACE` : 홀드 (블럭 당 1회만 가능)
  - `ESC` : 게임 종료