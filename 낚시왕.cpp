#include <iostream>
using namespace std;

struct CELL {
  int s, d, z;
};

int r, c, m;
CELL map[2][100][100];
int fishing(int cur, int pos) {
  int size = 0;
  for (int y = 0; y < r; ++y) {
    if (map[cur][y][pos].z != 0) {
      size = map[cur][y][pos].z;
      map[cur][y][pos].s = 0;
      map[cur][y][pos].d = 0;
      map[cur][y][pos].z = 0;
      break;
    }
  }
  return size;
}

// 1 -> up
// 2 -> down
// 3 -> right
// 4 -> down
void move(int cur) {
  int next = (cur + 1) % 2;
  for (int y = 0; y < r; ++y) {
    for (int x = 0; x < c; ++x) {
      map[next][y][x].s = 0;
      map[next][y][x].d = 0;
      map[next][y][x].z = 0;
    }
  }

  for (int y = 0; y < r; ++y) {
    for (int x = 0; x < c; ++x) {
      if (map[cur][y][x].z != 0) {
        // y 감소
        if (map[cur][y][x].d == 1) {
          int ny = (((r - 1) * 2) - y) + map[cur][y][x].s;
          ny = (ny % ((r - 1) * 2));
          int nd = 2;
          if (ny >= (r - 1)) {
            ny = ((r - 1) * 2) - ny;
            nd = 1;
          }
          if (map[next][ny][x].z < map[cur][y][x].z) {
            map[next][ny][x].s = map[cur][y][x].s;
            map[next][ny][x].d = nd;
            map[next][ny][x].z = map[cur][y][x].z;
          }
        }
        // y 증가
        else if (map[cur][y][x].d == 2) {
          int ny = y + map[cur][y][x].s;
          ny = (ny % ((r - 1) * 2));
          int nd = 2;
          if (ny >= (r - 1)) {
            ny = ((r - 1) * 2) - ny; nd = 1;
          }
          if (map[next][ny][x].z < map[cur][y][x].z) {
            map[next][ny][x].s = map[cur][y][x].s;
            map[next][ny][x].d = nd;
            map[next][ny][x].z = map[cur][y][x].z;
          }
        }
        // x 증가
        else if (map[cur][y][x].d == 3) {
          int nx = x + map[cur][y][x].s;
          nx = (nx % ((c - 1) * 2));
          int nd = 3;
          if (nx >= (c - 1)) {
            nx = ((c - 1) * 2) - nx; nd = 4;
          }
          if (map[next][y][nx].z < map[cur][y][x].z) {
            map[next][y][nx].s = map[cur][y][x].s;
            map[next][y][nx].d = nd;
            map[next][y][nx].z = map[cur][y][x].z;
          }
        }
        // x 감소
        else if (map[cur][y][x].d == 4) {
          int nx = (((c - 1) * 2) - x) + map[cur][y][x].s;
          nx = (nx % ((c - 1) * 2));
          int nd = 3;
          if (nx >= (c - 1)) {
            nx = ((c - 1) * 2) - nx; nd = 4;
          }
          if (map[next][y][nx].z < map[cur][y][x].z) {
            map[next][y][nx].s = map[cur][y][x].s;
            map[next][y][nx].d = nd;
            map[next][y][nx].z = map[cur][y][x].z;
          }
        }
      }
    }
  }
}

int main() {
  cin >> r >> c >> m;
  int y, x, cur = 0;
  for (int i = 0; i < m; ++i) {
    cin >> y >> x;
    --y, --x;
    cin >> map[cur][y][x].s >> map[cur][y][x].d >> map[cur][y][x].z;
  }

  int ret = 0;
  for (int pos = 0; pos < c; ++pos) {
    ret += fishing(cur, pos);
    move(cur);
    cur = (cur + 1) % 2;
  }

  cout << ret << endl;

  return 0;
}
