#include <iostream>
using namespace std;

const int dy[4] = {-1,1,0,0};
const int dx[4] = {0,0,-1,1};

const int DEL = -1;
int N, M, T;
int board[50][50];

void solve(int x, int d, int k) {
  int pick = x - 1;
  if (d == 1)
    k = -k;

  while (pick < N) {
    int temp[50] = {0,};
    for (int i = 0; i < M; ++i)
      temp[(i + k + M) % M] = board[pick][i];
    for (int i = 0; i < M; ++i)
      board[pick][i] = temp[i];
    pick += x;
  }

  bool updated = false;
  bool check[50][50] = {false,};

  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < M; ++x) {
      for (int d = 0; d < 4; ++d) {
        int ny = y + dy[d];
        int nx = (x + dx[d] + M) % M;
        if (ny < 0 || ny >= N)
          continue;
        if (board[y][x] != DEL && board[ny][nx] != DEL && board[y][x] == board[ny][nx]) {
          updated = true;
          check[y][x] = true;
          check[ny][nx] = true;
        }
      }
    }
  }

  if (updated) {
    for (int y = 0; y < N; ++y) {
      for (int x = 0; x < M; ++x) {
        if (check[y][x]) {
          board[y][x] = DEL;
        }
      }
    }
  } else {
    int sum = 0, count = 0;
    for (int y = 0; y < N; ++y) {
      for (int x = 0; x < M; ++x) {
        if (board[y][x] != DEL) {
          sum += board[y][x];
          ++count;
        }
      }
    }
    for (int y = 0; y < N; ++y) {
      for (int x = 0; x < M; ++x) {
        if (board[y][x] != DEL) {
          if (board[y][x] * count > sum) {
            --board[y][x];
          } else if (board[y][x] * count < sum) {
            ++board[y][x];
          }
        }
      }
    }
  }
}

int main() {
  cin >> N >> M >> T;
  for (int y = 0; y < N; ++y)
    for (int x = 0; x < M; ++x)
      cin >> board[y][x];

  for (int i = 0; i < T; ++i) {
    int x, d, k;
    cin >> x >> d >> k;
    solve(x, d, k);
  }
  int ret = 0;
  for (int y = 0; y < N; ++y)
    for (int x = 0; x < M; ++x)
      if (board[y][x] != DEL)
        ret += board[y][x];

  cout << ret << endl;
  return 0;
}
