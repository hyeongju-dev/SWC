// It's more general way to solve a problem!
#include <iostream>
#define abs(a) (a>0? a : -a)
using namespace std;

int n, l;
int map[100][100];

int solve() {
  int ans = 0;

  for (int i=0; i<n; ++i) {
    /* row */
    int cnt = 1;  // length of flat road until now
    bool passable = true; // can traverse the road(row or column) or not
    for (int j=0; j<n-1; ++j) {
      int diff = map[i][j] - map[i][j+1];

      if (diff == -1) { // go higher
        if (cnt < l) {
          passable = false;
          break;
        } else {
          cnt = 1;
        }
      } else if (diff == 1) { // go lower
        cnt = 1;
        j++;
        while (j < n-1 && map[i][j] == map[i][j+1]) {
          cnt++;
          j++;
        }
        if (cnt < l) {
          passable = false;
          break;
        } else {
          cnt = cnt - l;
          j--;
        }
      } else if (abs(diff) > 1) {
        passable = false;
        break;
      } else {
        cnt++;
      }
    }
    if (passable)
      ans++;

    /* column */
    cnt = 1;          // ^_^; encountered an error: redeclaration of 'int cnt'
    passable = true;
    for (int j=0; j<n-1; ++j) {
      int diff = map[j][i] - map[j+1][i];

      if (diff == -1) {
        if (cnt < l) {
          passable = false;
          break;
        } else {
          cnt = 1;
        }
      } else if (diff == 1) {
        cnt = 1;
        j++;
        while (j < n-1 && map[j][i] == map[j+1][i]) {
          cnt++;
          j++;
        }
        if (cnt < l) {
          passable = false;
          break;
        } else {
          cnt = cnt - l;
          j--;
        }
      } else if (abs(diff) > 1) {
        passable = false;
        break;
      } else {
        cnt++;
      }
    }
    if (passable)
      ans++;
  }

  return ans;
}

int main() {
  cin >> n >> l;
  for (int y=0; y<n; ++y)
    for (int x=0; x<n; ++x)
      cin >> map[y][x];

  cout << solve() << endl;

  return 0;
}
