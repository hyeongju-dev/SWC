#include <iostream>
using namespace std;

struct CCTV {
    int type, row, col;
};

int n, m, ret;
int map[8][8];
int cctv_size;
CCTV cctv[8];

const int rot_size[] = {4, 2, 4, 4, 1};

void map_copy(int dest[8][8], int src[8][8]) {
    for (int row = 0; row < n; ++row)
        for (int col = 0; col < m; ++col)
            dest[row][col] = src[row][col];
}

void update(int dir, CCTV cctv) {
    dir = (dir % 4);

    if (dir == 0) {
        for (int col = cctv.col + 1; col < m; ++col) {
            if (map[cctv.row][col] == 6)
                break;
            map[cctv.row][col] = -1;
        }
    }
    if (dir == 1) {
        for (int row = cctv.row - 1; row >= 0; --row) {
            if (map[row][cctv.col] == 6)
                break;
            map[row][cctv.col] = -1;
        }
    }
    if (dir == 2) {
        for (int col = cctv.col - 1; col >= 0; --col) {
            if (map[cctv.row][col] == 6)
                break;
            map[cctv.row][col] = -1;
        }
    }
    if (dir == 3) {
        for (int row = cctv.row + 1; row < n; ++row) {
            if (map[row][cctv.col] == 6)
                break;
            map[row][cctv.col] = -1;
        }
    }
}

void dfs(int cctv_index) {
    if (cctv_index == cctv_size) {
        int cand = 0;
        for (int row = 0; row < n; ++row)
            for (int col = 0; col < m; ++col)
                if (map[row][col] == 0)
                    ++cand;

        if (ret > cand)
            ret = cand;

        return;
    }

    int backup[8][8];
    int type = cctv[cctv_index].type;
    for (int dir = 0; dir < rot_size[type]; ++dir) {
        map_copy(backup, map);
        if (type == 0) {
            update(dir, cctv[cctv_index]);
        }
        if (type == 1) {
            update(dir, cctv[cctv_index]);
            update(dir+2, cctv[cctv_index]);
        }
        if (type == 2) {
            update(dir, cctv[cctv_index]);
            update(dir+1, cctv[cctv_index]);
        }
        if (type == 3) {
            update(dir, cctv[cctv_index]);
            update(dir+1, cctv[cctv_index]);
            update(dir+2, cctv[cctv_index]);
        }
        if (type == 4) {
            update(dir, cctv[cctv_index]);
            update(dir+1, cctv[cctv_index]);
            update(dir+2, cctv[cctv_index]);
            update(dir+3, cctv[cctv_index]);
        }
        dfs(cctv_index+1);
        map_copy(map, backup);
    }
}

int main() {
    cin >> n >> m;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < m; ++col) {
            cin >> map[row][col];

            if (map[row][col] != 0 && map[row][col] != 6) {
                cctv[cctv_size].row = row;
                cctv[cctv_size].col = col;
                cctv[cctv_size].type = map[row][col]-1;
                ++cctv_size;
            }
        }
    }

    ret = 100;
    dfs(0);

    cout << ret << endl;

    return 0;
}
