// https://www.acmicpc.net/problem/14888
// 연산자 끼워넣기

#include <iostream>
using namespace std;

int n;
int number[11];
int op[4];
int ret_min = 0x7fffffff, ret_max = ret_min * -1;

void dfs(int result, int count) {
	if (count == n-1) {
		if (ret_min > result)
			ret_min = result;
		if (ret_max < result)
			ret_max = result;
		return;
	}

	for (int i = 0; i < 4; ++i) {
		if (op[i] != 0) {
			--op[i];
			if (i == 0) {
				dfs(result + number[count+1], count+1);
			} else if (i == 1) {
				dfs(result - number[count+1], count+1);
			} else if (i == 2) {
				dfs(result * number[count+1], count+1);
			} else if (i == 3) {
				dfs(result / number[count+1], count+1);
			}
			++op[i];
		}
	}
}

int main() {
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> number[i];
	for (int i = 0; i < 4; ++i)
		cin >> op[i];

	dfs(number[0], 0);

	cout << ret_max << "\n" << ret_min << "\n";

	return 0;
}
