#include <iostream>
using namespace std;

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

int n, sum;
int map[21][21];

int solve(int x, int y, int d1, int d2) {
  int tmp[21][21] = {0,};
  tmp[x][y] = 5;

  for (int i = 1; i <= d1; ++i) {
    tmp[x+i][y-i] = 5;
    tmp[x+d2+i][y+d2-i] = 5;
  }

  for (int i = 1; i <= d2; ++i) {
    tmp[x+i][y+i] = 5;
    tmp[x+d1+i][y-d1+i] = 5;
  }

  // 1번 선거구
  int aa = 0;
  for (int r = 1; r < x+d1; ++r) {
    for (int c = 1; c <= y; ++c) {
      if (tmp[r][c] == 5)
        break;
      aa += map[r][c];
    }
  }

  // 2번 선거구
  int bb = 0;
  for (int r = 1; r <= x+d2; ++r) {
    for (int c = n; c > y; --c) {
      if (tmp[r][c] == 5)
        break;
      bb += map[r][c];
    }
  }

  // 3번 선거구
  int cc = 0;
  for (int r = x+d1; r <= n; ++r) {
    for (int c = 1; c < y-d1+d2; ++c) {
      if (tmp[r][c] == 5)
        break;
      cc += map[r][c];
    }
  }

  // 4번 선거구
  int dd = 0;
  for (int r = x+d2+1; r <= n; ++r) {
    for (int c = n; c >= y-d1+d2; --c) {
      if (tmp[r][c] == 5)
        break;
      dd += map[r][c];
    }
  }

  int ee = sum-(aa+bb+cc+dd);

  int max_val = max(aa, max(bb, max(cc, max(dd, ee))));
  int min_val = min(aa, min(bb, min(cc, min(dd, ee))));

  return (max_val - min_val);
}

int main() {
  cin >> n;
  for (int x = 1; x <= n; ++x) {
    for (int y = 1; y <= n; ++y) {
      cin >> map[x][y];
      sum += map[x][y];
    }
  }

  int ret = 0x7fffffff;

  for (int x = 1; x <= n; ++x) {
    for (int y = 1; y <= n; ++y) {
      for (int d1 = 1; d1 <= n; ++d1) {
        for (int d2 = 1; d2 <= n; ++d2) {
          if (x+d1+d2 > n)
            continue;
          if (y-d1 < 1)
            continue;
          if (y+d2 > n)
            continue;
          ret = min(ret, solve(x, y, d1, d2));
        }
      }
    }
  }

  cout << ret << endl;

  return 0;
}
