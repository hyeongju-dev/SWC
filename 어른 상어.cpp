#include <iostream>
using namespace std;

const int dy[4] = {-1,1,0,0};
const int dx[4] = {0,0,-1,1};

struct SHARK {
  int y, x, d;
  int priority[4][4];
};

int N, M, K, ret;
int board[20][20][3];
SHARK shark[400];

void solve() {
  int time = 0;
  int kill_shark = 0;
  while (time <= 1000) {
    ++time;

    int new_board[20][20][3] = {0,};
    for (int y = 0; y < N; ++y) {
      for (int x = 0; x < N; ++x) {
        new_board[y][x][0] = board[y][x][0];
        new_board[y][x][2] = board[y][x][2];
        if (new_board[y][x][2] > 0) {
          --new_board[y][x][2];
        }
        if (new_board[y][x][2] > 0) {
          new_board[y][x][1] = board[y][x][1];
        }
      }
    }

    for (int i = 0; i < M; ++i) {
      int cy = shark[i].y;
      int cx = shark[i].x;
      int cd = shark[i].d;
      if (cy == -1) {
        continue;
      }
      bool is_move = false;
      for(int d = 0; d < 4; ++d) {
        int nd = shark[i].priority[cd][d];
        int ny = cy + dy[nd];
        int nx = cx + dx[nd];
        if (ny < 0 || ny >= N || nx < 0 || nx >= N || board[ny][nx][2] != 0) {
          continue;
        }
        is_move = true;
        new_board[cy][cx][0] = 0;
        if (new_board[ny][nx][0] == 0) {
          new_board[ny][nx][0] = i + 1;
          new_board[ny][nx][1] = i + 1;
          new_board[ny][nx][2] = K;
          shark[i].y = ny;
          shark[i].x = nx;
          shark[i].d = nd;
        } else {
          ++kill_shark;
          shark[i].y = -1;
        }
        break;
      }
      if (is_move == false) {
        for (int d = 0; d < 4; ++d) {
          int nd = shark[i].priority[cd][d];
          int ny = cy + dy[nd];
          int nx = cx + dx[nd];
          if (ny < 0 || ny >= N || nx < 0 || nx >= N) {
            continue;
          }
          if (board[ny][nx][2] != 0 && board[ny][nx][1] != i + 1) {
            continue;
          }
          new_board[cy][cx][0] = 0;
          if (new_board[ny][nx][0] == 0) {
            new_board[ny][nx][0] = i + 1;
            new_board[ny][nx][1] = i + 1;
            new_board[ny][nx][2] = K;
            shark[i].y = ny;
            shark[i].x = nx;
            shark[i].d = nd;
          } else {
            ++kill_shark; shark[i].y = -1;
          }
          break;
        }
      }
    }
    if (kill_shark == M - 1) {
      break;
    }
    for (int y = 0; y < N; ++y) {
      for (int x = 0; x < N; ++x) {
        board[y][x][0] = new_board[y][x][0];
        board[y][x][1] = new_board[y][x][1];
        board[y][x][2] = new_board[y][x][2];
      }
    }
  }
  if (time <= 1000) {
    ret = time;
  }
}

int main() {
  cin >> N >> M >> K;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cin >> board[y][x][0];
      if (board[y][x][0] != 0) {
        int shark_number = board[y][x][0] - 1;
        shark[shark_number].y = y;
        shark[shark_number].x = x;
        board[y][x][1] = board[y][x][0];
        board[y][x][2] = K;
      }
    }
  }
  for (int i = 0; i < M; ++i) {
    cin >> shark[i].d;
    --shark[i].d;
  }
  for (int i = 0; i < M; ++i) {
    for (int d = 0; d < 4; ++d) {
      cin >> shark[i].priority[d][0] >> shark[i].priority[d][1] >> shark[i].priority[d][2] >> shark[i].priority[d][3];
      --shark[i].priority[d][0], --shark[i].priority[d][1], --shark[i].priority[d][2], --shark[i].priority[d][3];
    }
  }
  ret = -1;
  solve();
  cout << ret << endl;
  return 0;
}
