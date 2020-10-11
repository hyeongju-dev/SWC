#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define INT_MIN 0x80000000

int n;
int T[15], P[15];
int cache[15];

int solve(int day) {
  if (day > n)
    return INT_MIN;
  if (day == n)
    return 0;

  int& ret = cache[day];
  if (ret != -1)
    return ret;

  ret = max(solve(day+1), solve(day+T[day])+P[day]);

  return ret;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> T[i] >> P[i];

  memset(cache, -1, sizeof(cache));
  cout << solve(0) << endl;

  return 0;
}
