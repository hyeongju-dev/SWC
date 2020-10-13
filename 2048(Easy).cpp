#include <iostream>
using namespace std;

int n, ret;

struct BOARD {
  int map[20][20];

  void rotate() {
    int tmp[20][20];

    for (int y = 0; y < n; ++y)
      for (int x = 0; x < n; ++x)
        tmp[y][x] = map[n-x-1][y];

    for (int y = 0; y < n; ++y)
      for (int x = 0; x < n; ++x)
        map[y][x] = tmp[y][x];
  }

  int getMax() {
    int ret = 0;
    for (int y = 0; y < n; ++y)
      for (int x = 0; x < n; ++x)
        if (ret < map[y][x])
          ret = map[y][x];

    return ret;
  }

  void up() {
    int tmp[20][20];

    for (int x = 0; x < n; ++x) {
      bool updated = false, target = -1;
      for (int y = 0; y < n; ++y) {
        if (map[y][x] == 0)
          continue;
        if (updated == true && map[y][x] == tmp[target][x])
          tmp[target][x] *= 2, updated = false;
        else
          tmp[++target][x] = map[y][x], updated = true;
      }
      for (++target; target < n; ++target)
        tmp[target][x] = 0;
    }
    for (int y = 0; y < n; ++y)
      for (int x = 0; x < n; ++x)
        map[y][x] = tmp[y][x];
  }
};

void dfs(BOARD cur, int cnt) {
  if (cnt == 5) {
    int cand = cur.getMax();
    if (ret < cand)
      ret = cand;
    return;
  }

  for (int dir = 0; dir < 4; ++dir) {
    BOARD next = cur;
    next.up();
    dfs(next, cnt+1);
    cur.rotate();
  }
}

int main() {
  BOARD board;
  cin >> n;
  for (int y = 0; y < n; ++y)
    for (int x = 0; x < n; ++x)
      cin >> board.map[y][x];

  ret = 0;
  dfs(board, 0);
  cout << ret << endl;

  return 0;
}
