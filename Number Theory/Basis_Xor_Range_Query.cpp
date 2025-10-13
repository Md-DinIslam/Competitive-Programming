/*
    author: Din_ED
    Time: 00:00:33
    Date: 08-10-2025
*/

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define dg(x...)
#endif

#define ll long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) int(x.size())
#define arr array
#define vvi vector<vector<int>>
#define vi vector<int>

const int m = 31;

vector<int> v;

class segTree {
    vector<vector<int>> sg;
public:
    segTree(int n) : sg(4 * n, vector<int> (m, 0)) {};

    vi merge(const vi &a, const vi &b) {
        vi ans = a;
        for (auto &x : b) {
            insert(ans, x);
        }
        return ans;
    }

    void insert(vi &a, int val) {
        if (!val) return;
        for (int k = m - 1; k >= 0; --k) {
            if ((val >> k) & 1) {
                if (a[k] == 0) {
                    a[k] = val;
                    return;
                }
                val ^= a[k];
            }
        }
    }

    void build(int s, int e, int i = 1) {
        if (s == e) {
            insert(sg[i], v[s]);
        }
        else {
            int mid = (s + e) / 2;
            build(s, mid, 2 * i);
            build(mid + 1, e, 2 * i + 1);
            sg[i] = merge(sg[2 * i], sg[2 * i + 1]);
        }
    }

    vi qry(int lb, int rb, int s, int e, int i = 1) {
        if (s > rb || e < lb) return (vector<int> (m, 0));
        if (s >= lb && e <= rb) return sg[i];
        int mid = (s + e) / 2;
        return merge(qry(lb, rb, s, mid, 2 * i), qry(lb, rb, mid + 1, e, 2 * i + 1));
    }

    int qry(int lb, int rb, int n) {
        int ans = 0;
        auto basis = qry(lb, rb, 1, n);
        for (int k = m - 1; k >= 0; --k) {
            ans = max(ans, ans ^ basis[k]);
        }
        return ans;
    }
};

void Din() {
    int n, q, k;
    cin >> n >> q >> k;

    v.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
        v[i] |= k;
        v[i] ^= k;
    }
    
    segTree t(n);
    t.build(1, n);

    while (q--) {
        int lb, rb;
        cin >> lb >> rb;
        ll ans = (k | t.qry(lb, rb, n));
        cout << ans << '\n';
        // cout << (k | t.qry(lb, rb, n)) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        // cout << "Case " << i << ": ";
        Din();
    }
    return 0;
}
