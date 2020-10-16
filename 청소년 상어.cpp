#include <iostream>
using namespace std;

struct FISH {
  int y, x, dir;
};

const int dy[8] = {-1,-1,0,1,1,1,0,-1};
const int dx[8] = {0,-1,-1,-1,0,1,1,1};
int ret;

void solve(int board[4][4], FISH fish[], int sharkY, int sharkX, int sum) {
  int candBoard[4][4];
  FISH candFish[16];
  for (int y = 0; y < 4; ++y)
    for (int x = 0; x < 4; ++x)
      candBoard[y][x] = board[y][x];

  for (int i = 0; i < 16; ++i)
    candFish[i] = fish[i];

  //eat
  int numFish = candBoard[sharkY][sharkX];
  int dirShark = candFish[numFish].dir;
  candFish[numFish].y = -1;
  candFish[numFish].x = -1;
  candFish[numFish].dir = -1;
  candBoard[sharkY][sharkX] = -1;

  sum += (numFish + 1);
  if (ret < sum)
    ret = sum;

  //fish move
  for (int f = 0; f < 16; ++f) {
    if (candFish[f].y == -1)
      continue;
    int cy = candFish[f].y;
    int cx = candFish[f].x;
    int cd = candFish[f].dir;

    int ny = cy + dy[cd];
    int nx = cx + dx[cd];
    int nd = cd;
    while (ny < 0 || ny >= 4 || nx < 0 || nx >= 4 || (ny == sharkY && nx == sharkX)) {
      nd = (nd + 1) % 8;
      ny = cy + dy[nd];
      nx = cx + dx[nd];
    }
    if (candBoard[ny][nx] != -1) {
      int target = candBoard[ny][nx];
      candFish[target].y = cy;
      candFish[target].x = cx;
      candFish[f].y = ny;
      candFish[f].x = nx;
      candFish[f].dir = nd;
      candBoard[ny][nx] = f;
      candBoard[cy][cx] = target;
    } else {
      candFish[f].y = ny;
      candFish[f].x = nx;
      candFish[f].dir = nd;
      candBoard[ny][nx] = f;
      candBoard[cy][cx] = -1;
    }
  }

  //shark move
  for (int step = 1; step < 4; ++step) {
    int ny = sharkY + dy[dirShark] * step;
    int nx = sharkX + dx[dirShark] * step;
    if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4)
      break;
    if (candBoard[ny][nx] != -1)
      solve(candBoard, candFish, ny, nx, sum);
  }
}

int main() {
  FISH fish[16];
  int board[4][4];
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 4; ++x) {
      int a, b;
      cin >> a >> b;
      --a, --b;
      fish[a].y = y;
      fish[a].x = x;
      fish[a].dir = b;
      board[y][x] = a;
    }
  }
  ret = 0;
  solve(board, fish, 0, 0, 0);
  cout << ret << endl;
  return 0;
}
