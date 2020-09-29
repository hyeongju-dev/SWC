// https://www.acmicpc.net/problem/2533
// 친구 관계 트리가 주어졌을 때, 모든 개인이 새로운 아이디어를 수용하기 위하여 필요한 최소 얼리 어답터의 수를 구하는 프로그램을 작성하시오.

#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

int dp[1000000][2];		// 1000000으로 해도 문제 맞게 풀 수 있는데, 왜 대개 1010101과 같이 여유를 둘까?
vector<int> input[1000000];
vector<int> g[1000000];
int n;

void makeDfsTree(int curr, int prev) {
	for (auto next : input[curr]) {
		if (next ^ prev) {
			g[curr].push_back(next);
			makeDfsTree(next, curr);
		}
	}
}

int f(int curr, bool isEA) {
	int &res = dp[curr][isEA];
	if (res != -1)
		return res;

	res = 0;
	if (!isEA) {
		for (auto next : g[curr])
			res += f(next, true);
	} else {
		for (auto next : g[curr]) {
			int t0 = f(next, false);
			int t1 = f(next, true);
			res += min(t0, t1);
		}
		res++;
	}

	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 0; i < n-1; ++i) {
		int a, b;
		cin >> a >> b;
		input[a].push_back(b);
		input[b].push_back(a);
	}

	makeDfsTree(1, 0);

	memset(dp, -1, sizeof(dp));
	cout << min(f(1, false), f(1, true));

	return 0;
}
