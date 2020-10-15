#include <iostream>
#include <queue>
using namespace std;

struct SHARK {
  int y, x, time;
};

const int dy[] = {0,0,-1,1};
const int dx[] = {-1,1,0,0};

int n;
int map[20][20];
int sharkSize, sharkEat;
SHARK shark;

int main() {
  cin >> n;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cin >> map[y][x];
      if (map[y][x] == 9) {
        shark.y = y, shark.x = x, shark.time = 0;
        sharkSize = 2, sharkEat = 0;
        map[y][x] = 0;
      }
    }
  }

  bool updated = true;
  while (updated) {
    updated = false;

    bool visited[20][20] = {false,};
    queue<SHARK> q;
    visited[shark.y][shark.x] = true;
    q.push(shark);

    SHARK cand;
    cand.y = 20, cand.time = -1;
    while (!q.empty()) {
      SHARK cur = q.front();  q.pop();

      if (cand.time != -1 && cand.time < cur.time)
        break;

      if (map[cur.y][cur.x] < sharkSize && map[cur.y][cur.x] != 0) {
        updated = true;
        if (cand.y > cur.y || (cand.y == cur.y && cand.x > cur.x))
          cand = cur;
      }

      for (int dir = 0; dir < 4; ++dir) {
        SHARK next;
        next.y = cur.y + dy[dir];
        next.x = cur.x + dx[dir];
        next.time = cur.time + 1;

        if (next.y < 0 || next.y >= n || next.x < 0 || next.x >= n)
          continue;

        if (visited[next.y][next.x] == false && sharkSize >= map[next.y][next.x]) {
          visited[next.y][next.x] = true;
          q.push(next);
        }
      }
    }

    if (updated) {
      shark = cand;
      ++sharkEat;
      if (sharkEat == sharkSize) {
        ++sharkSize;
        sharkEat = 0;
      }
      map[shark.y][shark.x] = 0;
    }
  }

  cout << shark.time << endl;

  return 0;
}
