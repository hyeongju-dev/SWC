#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a;
    a.reserve(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    int b, c;
    cin >> b >> c;

    long long cnt = 0;
    for (int i = 0; i < n; ++i) {
        a[i] -= b;
        cnt++;

        if (a[i] > 0) {
            cnt += a[i] / c;
            if (a[i] % c)
                cnt++;
        }
    }

    cout << cnt << endl;

    return 0;
}
