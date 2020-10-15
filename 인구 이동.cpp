#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct POS {
  int y, x;
};

const int dy[] = {0,0,-1,1};
const int dx[] = {-1,1,0,0};

int n, l, r;
int map[50][50];

void createArea(int sy, int sx, int status[][50], int idx, int& cnt, int& sum) {
  int visited[50][50] = {0,};

  queue<POS> q;
  POS head;
  head.y = sy, head.x = sx;
  visited[sy][sx] = 1;
  q.push(head);

  while (!q.empty()) {
    POS cur = q.front(); q.pop();

    status[cur.y][cur.x] = idx;
    ++cnt;
    sum += map[cur.y][cur.x];

    for (int dir = 0; dir < 4; ++dir) {
      POS next;
      next.y = cur.y + dy[dir];
      next.x = cur.x + dx[dir];

      if (next.y < 0 || next.y >= n || next.x < 0 || next.x >= n)
        continue;

      int delta = abs(map[cur.y][cur.x] - map[next.y][next.x]);
      if (visited[next.y][next.x] == 0 && l <= delta && delta <= r) {
        visited[next.y][next.x] = 1;
        q.push(next);
      }
    }
  }
}

int main() {
  cin >> n >> l >> r;
  for (int y = 0; y < n; ++y)
    for (int x = 0; x < n; ++x)
      cin >> map[y][x];

  int ret = 0;
  bool updated = true;
  while (updated) {
    updated = false;

    int status[50][50] = {0,};
    int areaIdx = 0;
    int cnt[2501] = {0,};
    int sum[2501] = {0,};
    for (int y = 0; y < n; ++y) {
      for (int x = 0; x < n; ++x) {
        if (status[y][x] == 0) {
          ++areaIdx;
          createArea(y, x, status, areaIdx, cnt[areaIdx], sum[areaIdx]);
        }
      }
    }

    for (int y = 0; y < n; ++y) {
      for (int x = 0; x < n; ++x) {
        int idx = status[y][x];
        int avg = sum[idx] / cnt[idx];
        if (map[y][x] != avg) {
          map[y][x] = avg;
          updated = true;
        }
      }
    }

    if (updated)
      ++ret;
  }

  cout << ret << endl;

  return 0;
}
