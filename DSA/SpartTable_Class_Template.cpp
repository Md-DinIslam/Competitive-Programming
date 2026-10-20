/*
    author: Din_ED
    Time: 20:40:45
    Date: 20-10-2026
*/

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(x...)
#endif

#define ll long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) int(x.size())
#define arr array

template<class T> struct RMQ {
    vector<vector<T>> sp;
    RMQ () {}
    RMQ(const vector<T>& v) : sp(1, v) {
        int n = v.size();
        for (int i = 1, p = 1; 2 * p <= n; p *= 2, ++i) {
            sp.emplace_back(n - (2 * p) + 1);
            int m = sp[i].size();
            for (int j = 0; j < m; ++j) {
                sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + p]);
            }
        }
    }

    T qry(int a, int b) {
        b += 1;
        int depth = 31 - __builtin_clz(b - a);
        return min(sp[depth][a], sp[depth][b - (1 << depth)]);
    }
};

void Din() {
    int n, q;
    cin >> n >> q;
    
    vector<int> v(n);
    for (auto &x : v) {
        cin >> x;
    }

    RMQ<int> rmq(v);
    while (q--) {
        int lb, rb;
        cin >> lb >> rb;
        lb -= 1, rb -= 1;
        cout << rmq.qry(lb, rb) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i) {
        // cout << "Case " << i << ": ";
        Din();
    }
    return 0;
}
