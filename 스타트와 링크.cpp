#include <iostream>
using namespace std;

#define abs(a,b) ((a)-(b) > 0? (a)-(b) : (b)-(a))

int n, ret;
int table[20][20];
int start[10], link[10];
bool pick[20];

void update() {
  int start_size = 0, link_size = 0;
  for (int i = 0; i < n; ++i)
    if (pick[i])
      start[start_size++] = i;
    else
      link[link_size++] = i;

  int sum_start = 0, sum_link = 0;
  for (int i = 0; i < n/2; ++i) {
    for (int j = i+1; j < n/2; ++j) {
      sum_start += (table[start[i]][start[j]] + table[start[j]][start[i]]);
      sum_link += (table[link[i]][link[j]] + table[link[j]][link[i]]);
    }
  }

  if (ret > abs(sum_start, sum_link))
    ret = abs(sum_start, sum_link);
}

void dfs(int cur, int pick_cnt) {
  if (pick_cnt == n/2) {
    update();
    return;
  }

  for (int i = cur; i < n; ++i) {
    pick[i] = true;
    dfs(i+1, pick_cnt+1);
    pick[i] = false;
  }
}

int main() {
  cin >> n;
  for (int row = 0; row < n; ++row)
    for (int col = 0; col < n; ++col)
      cin >> table[row][col];

  ret = 0x7fffffff;
  dfs(0,0);
  cout << ret << endl;

  return 0;
}
