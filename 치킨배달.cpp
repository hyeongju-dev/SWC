#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct POS {
  int y, x;
};

int n, m, type, ret;
vector<POS> house, shop, pick;

void dfs(int pos) {
    if (pick.size() == m) {
      int cand = 0;
      for (int i=0; i<house.size(); ++i) {
          int min_dist = 0x7fffffff;
          for (int j=0; j<pick.size(); ++j)
              min_dist = min(min_dist, abs(house[i].y-pick[j].y)+abs(house[i].x-pick[j].x));
          cand += min_dist;
      }

      if (ret > cand)
        ret = cand;

      return;
    }

    for (int i=pos; i<shop.size(); ++i) {
        pick.push_back(shop[i]);
        dfs(i+1);
        pick.pop_back();
    }
}

int main() {
    POS target;
    cin >> n >> m;
    for (int y=0; y<n; ++y) {
        for (int x=0; x<n; ++x) {
            cin >> type;
            if (type == 1) {
                target.y = y, target.x = x;
                house.push_back(target);
            } else if (type == 2) {
                target.y = y, target.x = x;
                shop.push_back(target);
            }
        }
    }

    ret = 0x7fffffff;
    dfs(0);
    cout << ret << endl;

    return 0;
}
