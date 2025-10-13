/* GREEN UNIVERSITY OF BANGLADESH
    Md DinIslam, Batch-221 (CSE)
*/
#include <bits/stdc++.h>
using namespace std;

// Debug..
#ifdef LOCAL
#include "debug.h"
#else
#define dg(x...)
#endif

#define ll long long
#define all(x) x.begin(), x.end()
#define sz(x) int(x.size())

ll getGCD(ll a, ll b) {
    if (!b) return a;
    return getGCD(b, a % b);
}

template<class T> struct RMQ {
    vector<vector<T>> sp;
    RMQ(const vector<T>& v) : sp(1, v) {
        int n = v.size();
        for (int i = 1, p = 1; 2 * p <= n; p *= 2, ++i) {
            sp.emplace_back(n - (2 * p) + 1);
            int m = sp[i].size();
            for (int j = 0; j < m; ++j) {
                sp[i][j] = getGCD(sp[i - 1][j], sp[i - 1][j + p]);
            }
        }
    }

    T qry(int a, int b) {
        int depth = 31 - __builtin_clz(b - a);
        return getGCD(sp[depth][a], sp[depth][b - (1 << depth)]);
    }
};

void Din() {
    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &x : v) {
        cin >> x;
    }

    RMQ<int> rmq(v);

    // dg(rmq.qry(2, 3)); [inclusive, exclusive]..
    map<int, ll> ans;
    for (int i = 0; i < n; ++i) {
        int j = i;
        while (j < n) {
            int gcd = rmq.qry(i, j + 1);
            int lb = j, rb = n - 1;
            while (lb < rb) {
                int mid = lb + (rb - lb) / 2;
                ll curr_gcd = rmq.qry(i, mid + 1);
                if (curr_gcd < gcd) {
                    rb = mid;
                }
                else {
                    lb = mid + 1;
                }
            }

            if (rmq.qry(i, lb + 1) != gcd) {
                lb -= 1;
            }

            ans[gcd] += (lb - j + 1);
            j = lb + 1;
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << '\n';
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

/*

https://codeforces.com/problemset/problem/475/D

*/