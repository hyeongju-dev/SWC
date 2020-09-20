// TODO: another way

#include <iostream>
using namespace std;

int n, l, ret = 0;
int map[200][100];

int main() {
    cin >> n >> l;
    for (int y = 0; y < n; ++y)
        for (int x = 0; x < n; ++x)
            cin >> map[y][x];

    for (int y = 0; y < n; ++y)
        for (int x = 0; x < n; ++x)
            map[n+y][x] = map[x][y];

    int count = 0;
    int i, j;

    ret = 0;
    for (i = 0; i < 2*n; ++i) {
        count = 1;
        for (j = 0; j < n-1; ++j) {
            if (map[i][j] == map[i][j + 1])
                ++count;
            else if (map[i][j] + 1 == map[i][j + 1] && count >= l)
                count = 1;
            else if (map[i][j] - 1 == map[i][j + 1] && count >= 0)
                count = (1 - l);
            else
                break;
        }
        if (j == (n-1) && count >= 0)
            ++ret;
    }

    cout << ret << endl;

    return 0;
}
