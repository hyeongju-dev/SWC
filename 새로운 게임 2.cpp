#include <iostream>
using namespace std;

struct POS {
  int y, x, d;
};

const int dy[] = {0,0,-1,1};
const int dx[] = {1,-1,0,0};

int n, k;
int color[12][12];
int map[12][12][5];
int pos_size;
POS pos[10];

int turn(int index) {
  POS cur = pos[index];
  POS next;
  next.y = cur.y + dy[cur.d];
  next.x = cur.x + dx[cur.d];
  next.d = cur.d;

  if (next.y < 0 || next.y >= n || next.x < 0 || next.x >= n || color[next.y][next.x] == 2) {
    next.d = (cur.d == 0 || cur.d == 2) ? (cur.d + 1) : (cur.d - 1);
    next.y = cur.y + dy[next.d];
    next.x = cur.x + dx[next.d];
    pos[index].d = next.d;
    if (next.y < 0 || next.y >= n || next.x < 0 || next.x >= n || color[next.y][next.x] == 2)
      return map[cur.y][cur.x][0];
  }

  int bottom = -1;
  int& cur_size = map[cur.y][cur.x][0];
  for (int i = 1; i <= cur_size; ++i) {
    if (map[cur.y][cur.x][i] == index) {
      bottom = i;
      break;
    }
  }

  int move[5] = {0,};
  int& move_size = move[0];
  for (int i = bottom; i <= cur_size; ++i)
    move[++move_size] = map[cur.y][cur.x][i];
  cur_size = bottom - 1;
  if (color[next.y][next.x] == 1) {
    for (int i = 1; i <= move_size / 2; ++i) {
      int temp = move[i];
      move[i] = move[move_size-i+1];
      move[move_size-i+1] = temp;
    }
  }

  int& next_size = map[next.y][next.x][0];
  for (int i = 1; i <= move_size; ++i) {
    map[next.y][next.x][++next_size] = move[i];
    pos[move[i]].y = next.y;
    pos[move[i]].x = next.x;
    if (next_size >= 4)
      return next_size;
  }
  return next_size;
}

int main() {
  cin >> n >> k;
  for (int y = 0; y < n; ++y)
    for (int x = 0; x < n; ++x)
      cin >> color[y][x];

  for (int i = 0; i < k; ++i) {
    int y, x, d;
    cin >> y >> x >> d;
    --y, --x, --d;
    pos[pos_size].y = y;
    pos[pos_size].x = x;
    pos[pos_size].d = d;
    int& size = map[y][x][0];
    map[y][x][++size] = pos_size;
    ++pos_size;
  }

  int loop = 0, ret = -1;
  while (loop <= 1000 && ret == -1) {
    ++loop;
    for (int i = 0; i < k; ++i) {
      int h = turn(i);
      if (h >= 4) {
        ret = loop;
        break;
      }
    }
  }
  cout << ret << endl;

  return 0;
}
