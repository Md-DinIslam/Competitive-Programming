/*
    author: Din_ED
    Time: 16:00:17
    Date: 04-11-2025
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

const int inf = 1e9;

int n, m, q;

struct DSU {
    vector<int> ps, days, cnt;
    DSU(int n) : ps(n+1), cnt(n+1, 1), days(n+1, inf) {
        iota(all(ps), 0);
    };

    int Find(int x) {
        return ps[x] == x ? x : Find(ps[x]);
    }

    bool is_same(int a, int b) {
        return (Find(a) == Find(b));
    }

    void Union(int a, int b, int wg) {
        a = Find(a), b = Find(b);
        if (a == b) return; // same parent...
        if (cnt[a] > cnt[b]) {
            swap(a, b);
        }
        cnt[b] += cnt[a];
        ps[a] = b; // root b..
        days[a] = wg; // children will get weight...
    }

    int qry(int a, int b) {
        if (!is_same(a, b)) return -1;
        int ans = 0;
        while (a != b) {
            if (days[a] < days[b]) {
                swap(a, b);
            }
            ans = max(ans, days[b]);
            b = ps[b];
            if (ans == inf) return -1;
        }
        return ans;
    }
};

void Din() {
    cin >> n >> m >> q;

    DSU t(n);

    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        t.Union(x, y, i);
    }

    // cerr << t.qry(1, 3) << "\n";

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << t.qry(a, b) << "\n";
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
