#include <iostream>
#include <queue>
using namespace std;

struct CUSTOMER {
  int start, end;
};

struct TAXI {
  int pos, distance;
};

const int WALL = -1;
const int EMPTY = -2;
const int dy[4] = {-1,0,1,0};
const int dx[4] = {0,-1,0,1};

int N, M, fuel;
int taxiY, taxiX;
int board[20][20];
CUSTOMER customer[400];

int findCustomer() {
  queue<TAXI> q;
  bool visited[20][20] = {false,};
  TAXI cur = {taxiY * 100 + taxiX, 0};
  visited[taxiY][taxiX] = true;
  q.push(cur);

  int candSize = 0;
  int cand[400] = {0,};
  int candDistance = -1;

  while (!q.empty()) {
    cur = q.front();
    q.pop();

    if (candDistance != -1 && cur.distance > candDistance)
      break;

    int y = cur.pos / 100;
    int x = cur.pos % 100;
    if (board[y][x] >= 0) {
      cand[candSize++] = board[y][x];
      candDistance = cur.distance;
    }

    for (int d = 0; d < 4; ++d) {
      int ny = y + dy[d];
      int nx = x + dx[d];

      if (ny < 0 || ny >= N || nx < 0 || nx >= N || board[ny][nx] == WALL || visited[ny][nx] == true)
        continue;

      visited[ny][nx] = true;
      TAXI next = {ny * 100 + nx, cur.distance + 1};
      q.push(next);
    }
  }
  if (candDistance > fuel)
    return -1;

  int ret = -1;
  int candVal = 10000;
  for (int i = 0; i < candSize; ++i) {
    if (candVal > customer[cand[i]].start) {
      candVal = customer[cand[i]].start;
      ret = cand[i];
    }
  }

  taxiY = customer[ret].start / 100;
  taxiX = customer[ret].start % 100;
  board[taxiY][taxiX] = EMPTY;
  fuel -= candDistance;
  return ret;
}

bool moveCustomer(int target) {
  queue<TAXI> q;
  bool visited[20][20] = {false,};
  TAXI cur = {taxiY * 100 + taxiX, 0};
  visited[taxiY][taxiX] = true;
  q.push(cur);

  while (!q.empty()) {
    cur = q.front(); q.pop();

    if (cur.distance > fuel)
      return false;

    if (cur.pos == customer[target].end) {
      taxiY = customer[target].end / 100;
      taxiX = customer[target].end % 100;
      fuel += cur.distance;
      return true;
    }

    int y = cur.pos / 100;
    int x = cur.pos % 100;
    for (int d = 0; d < 4; ++d) {
      int ny = y + dy[d];
      int nx = x + dx[d];
      if (ny < 0 || ny >= N || nx < 0 || nx >= N || board[ny][nx] == WALL || visited[ny][nx] == true)
        continue;
      TAXI next = {ny * 100 + nx, cur.distance + 1};
      q.push(next);
      visited[ny][nx] = true;
    }
  }
  return false;
}

int solve() {
  int ret = -1;
  for (int i = 0; i < M; ++i) {
    int target = findCustomer();
    if (target == -1)
      return ret;
    bool success = moveCustomer(target);
    if (success == false)
      return ret;
  }
  ret = fuel;
  return ret;
}

int main() {
  cin >> N >> M >> fuel;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < N; ++x) {
      cin >> board[y][x];
      board[y][x] -= 2;
    }
  }
  cin >> taxiY >> taxiX;
  --taxiY, --taxiX;
  for (int i = 0; i < M; ++i) {
    int sy, sx, ey, ex;
    cin >> sy >> sx >> ey >> ex;
    --sy, --sx, --ey, --ex;
    customer[i].start = (sy * 100 + sx);
    customer[i].end = (ey * 100 + ex);
    board[sy][sx] = i;
  }
  int ret = solve();
  cout << ret << endl;
  return 0;
}
