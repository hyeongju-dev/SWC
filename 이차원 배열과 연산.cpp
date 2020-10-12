#include <iostream>
using namespace std;

int r, c, k;
int ret;
int map[101][101];
int pre_row_size, cur_row_size;
int pre_col_size, cur_col_size;

void update_row(int sy) {
  int bucket[101] = {0,};
  for (int x = 1; x <= pre_col_size; ++x)
    ++bucket[map[sy][x]];

  int size = 0;
  for (int i = 1; i <= 100 && size < 100; ++i) {
    for (int j = 1; j <= 100 && size < 100; ++j) {
      if (bucket[j] == i) {
        map[sy][++size] = j;
        map[sy][++size] = i;
      }
    }
  }

  for (int i = size+1; i <= pre_col_size; ++i)
    map[sy][i] = 0;

  if (cur_col_size < size)
    cur_col_size = size;
}

void update_col(int sx) {
  int bucket[101] = {0,};
  for (int y = 1; y <= pre_row_size; ++y)
    ++bucket[map[y][sx]];

  int size = 0;
  for (int i = 1; i <= 100 && size < 100; ++i) {
    for (int j = 1; j <= 100 && size < 100; ++j) {
      if (bucket[j] == i) {
        map[++size][sx] = j;
        map[++size][sx] = i;
      }
    }
  }

  for (int i = size+1; i <= pre_row_size; ++i)
    map[i][sx] = 0;

  if (cur_row_size < size)
    cur_row_size = size;
}

void solve() {
  while (map[r][c] != k) {
    if (cur_row_size >= cur_col_size) {
      pre_col_size = cur_col_size;
      cur_col_size = 0;
      for (int y = 1; y <= cur_row_size; ++y)
        update_row(y);
    } else {
      pre_row_size = cur_row_size;
      cur_row_size = 0;
      for (int x = 1; x <= cur_col_size; ++x)
        update_col(x);
    }

    ++ret;
    if (ret > 100)
      break;
  }
}

int main() {
  pre_row_size = 3, cur_row_size = 3;
  pre_col_size = 3, cur_col_size = 3;
  cin >> r >> c >> k;

  for (int y = 1; y <= 3; ++y)
    for (int x = 1; x <= 3; ++x)
      cin >> map[y][x];

  ret = 0;
  solve();
  if (ret > 100)
    cout << -1 << endl;
  else
    cout << ret << endl;

  return 0;
}
