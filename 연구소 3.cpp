#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct POS {
  int y, x, time;
};

const int dy[] = {1,-1,0,0};
const int dx[] = {0,0,-1,1};

int n, m, ret;
int map[50][50];
int posSize;
POS pos[10];

int bfs(int pick[]) {
  int emptyCnt = 0;
  for (int y = 0; y < n; ++y)
    for (int x = 0; x < n; ++x)
      if (map[y][x] == 0)
        ++emptyCnt;

  queue<POS> q;
  int visited[50][50] = {0,};
  for (int i = 0; i < m; ++i) {
    q.push(pos[pick[i]]);
    visited[pos[pick[i]].y][pos[pick[i]].x] = 1;
  }

  while (!q.empty()) {
    POS cur = q.front(); q.pop();
    if (map[cur.y][cur.x] == 0)
      --emptyCnt;
    if (emptyCnt == 0)
      return cur.time;

    POS next;
    next.time = cur.time + 1;
    for (int d = 0; d < 4; ++d) {
      next.y = cur.y + dy[d];
      next.x = cur.x + dx[d];
      if (next.y < 0 || next.y >= n || next.x < 0 || next.x >= n)
        continue;

      if (visited[next.y][next.x] == 0 && map[next.y][next.x] != 1) {
        q.push(next);
        visited[next.y][next.x] = 1;
      }
    }
  }

  return 0x7fffffff;
}

void dfs(int lastPick, int pickCnt, int pick[]) {
  if (pickCnt == m) {
    int cand = bfs(pick);
    if (ret > cand)
      ret = cand;
    return;
  }

  for (int i = lastPick + 1; i < posSize; ++i) {
    pick[pickCnt] = i;
    dfs(i, pickCnt + 1, pick);
  }
}

int main() {
  cin >> n >> m;
  for (int y = 0; y < n; ++y) {
    for(int x = 0; x < n; ++x) {
      cin >> map[y][x];
      if (map[y][x] == 2) {
        pos[posSize].y = y;
        pos[posSize].x = x;
        pos[posSize].time = 0;
        ++posSize;
      }
    }
  }

  ret = 0x7fffffff;
  int pick[10] = {0,};
  dfs(-1, 0, pick);
  if (ret == 0x7fffffff)
    cout << -1 << endl;
  else
    cout << ret << endl;

  return 0;
}
