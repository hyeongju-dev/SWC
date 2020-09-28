#include <iostream>
using namespace std;

const int dy[] = {0,-1,0,1};
const int dx[] = {1,0,-1,0};

int main() {
  int map[101][101] = {0,};

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int curve_size = 0;
    int curve[1024] = {0,};

    int x, y, d, g;
    cin >> x >> y >> d >> g;

    curve[curve_size++] = d;
    map[y][x] = 1;

    for (int j = 0; j < g; ++j)
      for (int k = curve_size-1; k >= 0; --k)
        curve[curve_size++] = (curve[k]+1)%4;

    for (int j = 0; j < curve_size; ++j) {
      y+= dy[curve[j]];
      x+= dx[curve[j]];
      if (y < 0 || y >= 101 || x < 0 || x > 101)
        continue;
      map[y][x] = 1;
    }
  }

  int ret = 0;
  for (int y = 0; y < 100; ++y)
    for (int x = 0; x < 100; ++x)
      if (map[y][x] && map[y][x+1] && map[y+1][x] && map[y+1][x+1])
        ++ret;

  cout << ret << endl;

  return 0;
}
