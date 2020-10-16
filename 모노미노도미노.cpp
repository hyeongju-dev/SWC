#include <iostream>
using namespace std;

const int BLUE = 0;
const int GREEN = 1;

int N, score, cnt;
int board[2][10][4];

void movePoint(int y, int x, int color) {
  int label = board[color][y][x];
  board[color][y][x] = 0;
  while (y < 10) {
    if (board[color][y][x] != 0) {
      break;
    }
    ++y;
  }
  --y;
  board[color][y][x] = label;
}

void moveHBlock(int y, int x, int color) {
  int label = board[color][y][x];
  board[color][y][x] = 0;
  board[color][y - 1][x] = 0;
  while (y < 10) {
    if (board[color][y][x] != 0) {
      break;
    }
    ++y;
  }
  --y;
  board[color][y][x] = label;
  board[color][y - 1][x] = label;
}

void moveWBlock(int y, int x, int color) {
  int label = board[color][y][x];
  board[color][y][x] = 0;
  board[color][y][x + 1] = 0;
  while (y < 10) {
    if (board[color][y][x] != 0 || board[color][y][x + 1] != 0) {
      break;
    }
    ++y;
  }
  --y;
  board[color][y][x] = label;
  board[color][y][x + 1] = label;
}

void remove(int y, int color) {
  for (int x = 0; x < 4; ++x) {
    board[color][y][x] = 0;
  }
}

void move(int sy, int color) {
  const int dy[2] = { -1, 0 };
  const int dx[2] = { 0, +1 };
  for (int y = sy; y >= 4; --y) {
    for (int x = 0; x < 4; ++x) {
      if (board[color][y][x] == 0) {
        continue;
      }
      //type 1 one block
      //type 2 h block
      //tyep 3 w block
      int type = 1;
      for (int d = 0; d < 2; ++d) {
        int ny = y + dy[d];
        int nx = x + dx[d];
        if (ny < 4 || nx >= 4) {
          continue;
        }
        if (board[color][y][x] == board[color][ny][nx]) {
          if (d == 0) {
            type = 2;
          } else {
            type = 3;
          }
        }
      }
      if (type == 1) {
        movePoint(y, x, color);
      } else if (type == 2) {
        moveHBlock(y, x, color);
      } else if (type == 3) {
        moveWBlock(y, x, color);
      }
    }
  }
}

void deleteFilledBlock(int color) {
  bool removed = false;

  for (int y = 6; y < 10; ++y) {
    int cnt = 0;

    for (int x = 0; x < 4; ++x)
      if (board[color][y][x] != 0)
        ++cnt;

    if (cnt == 4) {
      removed = true;
      ++score;
      remove(y, color);
      move(y - 1, color);
    }
  }
  if (removed)
    deleteFilledBlock(color);
}

void deleteOverflowBlock(int color) {
  int removeCnt = 0;
  for (int y = 4; y <= 5; ++y) {
    bool hasBlock = false;
    for (int x = 0; x < 4; ++x) {
      if (board[color][y][x] != 0) {
        hasBlock = true;
        break;
      }
    }
    if (hasBlock)
      ++removeCnt;
  }

  if (removeCnt > 0) {
    for (int y = 9; y >= 6; --y)
      for (int x = 0; x < 4; ++x)
        board[color][y][x] = board[color][y - removeCnt][x];

    for (int y = 4; y <= 5; ++y)
      for (int x = 0; x < 4; ++x)
        board[color][y][x] = 0;
  }
}

void put(int type, int target, int color, int label) {
  if (type == 1) {
    board[color][0][target] = label;
    movePoint(0, target, color);
  } else if ((type == 2 && color == BLUE) || (type == 3 && color == GREEN)) {
    board[color][0][target] = label;
    board[color][1][target] = label;
    moveHBlock(1, target, color);
  } else if ((type == 3 && color == BLUE) || (type == 2 && color == GREEN)) {
    board[color][0][target] = label;
    board[color][0][target + 1] = label;
    moveWBlock(0, target, color);
  }
  deleteFilledBlock(color);
  deleteOverflowBlock(color);
}

int main() {
  score = 0, cnt = 0;
  cin >> N;

  for (int i = 0; i < N; ++i) {
    int t, x, y;
    cin >> t >> y >> x;
    put(t, y, BLUE, i + 1);
    put(t, x, GREEN, i + 1);
  }

  for (int color = 0; color < 2; ++color)
    for (int y = 4; y < 10; ++y)
      for (int x = 0; x < 4; ++x)
        if (board[color][y][x] != 0)
          ++cnt;
  cout << score << '\n' << cnt << '\n';

  return 0;
}
