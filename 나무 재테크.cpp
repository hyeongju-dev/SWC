#include <iostream>
#include <algorithm>
using namespace std;

struct TREE {
  int y, x, age;
};

bool cmp(TREE& a, TREE& b) {
  return (a.age < b.age);
}

struct QUEUE {
  int f, b;
  TREE tree[68400];

  QUEUE() {
    init();
  }

  void init() {
    f = 0, b = 0;
  }

  bool isEmpty() {
    return (f == b);
  }

  void push(TREE val) {
    tree[b++] = val;
  }

  void pop() {
    ++f;
  }

  TREE front() {
    return tree[f];
  }

  int size() {
    return (b - f);
  }
};

const int dy[] = {-1,-1,-1,0,0,1,1,1};
const int dx[] = {-1,0,1,-1,1,-1,0,1};

int n, m, k;
QUEUE tree[2];
QUEUE newTree;
QUEUE deadTree, birthOfChildTree;

TREE initTree[100];
int map[10][10], add[10][10];

int main() {
  cin >> n >> m >> k;
  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      cin >> add[y][x];
      map[y][x] = 5;
    }
  }

  for (int i = 0; i < m; ++i) {
    cin >> initTree[i].y >> initTree[i].x >> initTree[i].age;
    initTree[i].y--, initTree[i].x--;
  }

  sort(initTree, initTree + m, cmp);

  int cur = 0, next = 0;
  for (int i = 0; i < m; ++i)
    tree[cur].push(initTree[i]);

  for (int i = 0; i < k; ++i) {
    next = (cur + 1) % 2;

    deadTree.init();
    birthOfChildTree.init();
    tree[next].init();

    while (!newTree.isEmpty()) {
      TREE curTree = newTree.front(); newTree.pop();

      if (map[curTree.y][curTree.x] >= curTree.age) {
        map[curTree.y][curTree.x] -= curTree.age;

        ++curTree.age;
        tree[next].push(curTree);
      } else {
        deadTree.push(curTree);
      }
    }

    while (!tree[cur].isEmpty()) {
      TREE curTree = tree[cur].front(); tree[cur].pop();

      if (map[curTree.y][curTree.x] >= curTree.age) {
        map[curTree.y][curTree.x] -= curTree.age;

        ++curTree.age;
        tree[next].push(curTree);

        if ((curTree.age % 5) == 0)
          birthOfChildTree.push(curTree);
      } else {
        deadTree.push(curTree);
      }
    }

    while (!deadTree.isEmpty()) {
      TREE curTree = deadTree.front(); deadTree.pop();
      map[curTree.y][curTree.x] += (curTree.age / 2);
    }

    newTree.init();
    while (!birthOfChildTree.isEmpty()) {
      TREE curTree = birthOfChildTree.front(); birthOfChildTree.pop();
      for (int dir = 0; dir < 8; ++dir) {
        TREE nextTree;
        nextTree.y = curTree.y + dy[dir];
        nextTree.x = curTree.x + dx[dir];
        nextTree.age = 1;
        if (nextTree.y < 0 || nextTree.y >= n || nextTree.x < 0 || nextTree.x >= n)
          continue;
        newTree.push(nextTree);
      }
    }

    for (int y = 0; y < n; ++y)
      for (int x = 0; x < n; ++x)
        map[y][x] += add[y][x];

    cur = next;
  }

  cout << tree[next].size() + newTree.size() << endl;

  return 0;
}
