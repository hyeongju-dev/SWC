#include <iostream>
using namespace std;

int r, c, t;
int map[2][50][50];
int up_y, up_x, down_y, down_x;

const int dy[] = { -1, +1, 0, 0 };
const int dx[] = { 0, 0, -1, +1 };

void spead(int cur) {
    int next = (cur + 1) % 2;

    for (int y = 0; y < r; ++y)
        for (int x = 0; x < c; ++x)
            if (map[cur][y][x] == -1)
                map[next][y][x] = -1;
            else
                map[next][y][x] = 0;

    for (int y = 0; y < r; ++y) {
        for (int x = 0; x < c; ++x) {
            int val = (map[cur][y][x] / 5);
            int candi = 0;

            for (int dir = 0; dir < 4; ++dir) {
                int ny = y + dy[dir];
                int nx = x + dx[dir];

                if (ny < 0 || ny >= r || nx < 0 || nx >= c)
                    continue;

                if (map[next][ny][nx] != -1) {
                    map[next][ny][nx] += val;
                    candi += val;
                }
            }

            if (map[next][y][x] != -1)
                map[next][y][x] += (map[cur][y][x] - candi);

        }
    }
}

void move(int cur) {
    for (int y = up_y - 1; y > 0; --y)
        map[cur][y][0] = map[cur][y - 1][0];

    for (int x = 0; x < c - 1; ++x)
        map[cur][0][x] = map[cur][0][x + 1];

    for (int y = 0; y < up_y; ++y)
        map[cur][y][c - 1] = map[cur][y + 1][c - 1];

    for (int x = c - 1; x > 1; --x)
        map[cur][up_y][x] = map[cur][up_y][x - 1];

    map[cur][up_y][1] = 0;

    for (int y = down_y + 1; y < r; ++y)
        map[cur][y][0] = map[cur][y + 1][0];

    for (int x = 0; x < c - 1; ++x)
        map[cur][r - 1][x] = map[cur][r - 1][x + 1];

    for (int y = r - 1; y > down_y; --y)
        map[cur][y][c - 1] = map[cur][y - 1][c - 1];

    for (int x = c - 1; x > 1; --x)
        map[cur][down_y][x] = map[cur][down_y][x - 1];

    map[cur][down_y][1] = 0;
}

int main() {
    up_y = -1;
    cin >> r >> c >> t;
    for (int y = 0; y < r; ++y) {
        for (int x = 0; x < c; ++x) {
            cin >> map[0][y][x];
            if (map[0][y][x] == -1) {
                if (up_y == -1)
                    up_y = y, up_x = x;
                else
                    down_y = y, down_x = x;
            }
        }
    }

    int cur = 0;
    for (int time = 0; time < t; ++time) {
        spead(cur);
        cur = (cur + 1) % 2;
        move(cur);
    }

    int ret = 0;
    for (int y = 0; y < r; ++y)
        for (int x = 0; x < c; ++x)
            if (map[cur][y][x] != -1)
                ret += map[cur][y][x];

    cout << ret << endl;

    return 0;
}
