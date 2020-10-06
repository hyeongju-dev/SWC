#include <iostream>
using namespace std;

int n, k, m;
int map[101][101];
int head_y, head_x, tail_index;
int snake_y[10101], snake_x[10101];
char cmd[10001];

const int dy[] = {0,1,0,-1};
const int dx[] = {1,0,-1,0};

int main() {
    cin >> n >> k;

    int y, x;
    for (int i = 0; i < k; ++i) {
        cin >> y >> x;
        map[y][x] = 1;
    }

    int time;
    char c;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> time >> c;
        cmd[time] = c;
    }

    int dir = 0;
    time = 0;
    head_y = 1, head_x = 1, tail_index = time;
    snake_y[time] = head_y, snake_x[time] = head_x;
    map[head_y][head_x] = -1;

    while (true) {
        ++time;

        head_y += dy[dir];
        head_x += dx[dir];

        if (head_y < 1 || head_y > n || head_x < 1 || head_x > n || map[head_y][head_x] == -1)
            break;

        snake_y[time] = head_y;
        snake_x[time] = head_x;
        if (map[head_y][head_x] == 0) {
            int tail_y = snake_y[tail_index];
            int tail_x = snake_x[tail_index];
            map[tail_y][tail_x] = 0;
            ++tail_index;
        }
        map[head_y][head_x] = -1;

        if (cmd[time] == 'D')
            dir = (dir + 1) % 4;

        if (cmd[time] == 'L')
            dir = (dir + 3) % 4;
    }

    cout << time << endl;

    return 0;
}
