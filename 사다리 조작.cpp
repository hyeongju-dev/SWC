#include <iostream>
using namespace std;

int n, m, h, ret;
int map[31][11];

bool check() {
  bool ret = true;

  for (int i = 1; i <= n; ++i) {
    int pos = i;

    for (int j = 0; j <= h; ++j)
      if (map[j][pos] == 1)
        ++pos;
      else if (map[j][pos-1] == 1)
        --pos;

    if (pos != i)
      return ret = false;
  }

  return ret;
}

void dfs(int cnt, int y, int x) {
  if (cnt >= ret)
    return;
  if (check()) {
    ret = cnt;
    return;
  }
  if (cnt == 3)
    return;

  for (int i = y; i <= h; ++i) {
    for (int j = x; j < n; ++j) {
      if (map[i][j] == 0 && map[i][j-1] == 0 && map[i][j+1] == 0) {
        map[i][j] = 1;
        dfs(cnt+1, i, j);
        map[i][j] = 0;
      }
    }
    x = 1;
  }
}

int main() {
  cin >> n >> m >> h;
  int a, b;
  for (int i = 0; i < m; ++i) {
    cin >> a >> b;
    map[a][b] = 1;
  }

  ret = 4;
  dfs(0, 1, 1);
  if (ret == 4)
    ret = -1;
  cout << ret << endl;

  return 0;
}
