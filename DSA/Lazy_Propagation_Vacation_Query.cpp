/*
    author: Din_ED
    Time: 17:39:04
    Date: 19-07-2026
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

string v;

struct Node {
    int len, prefix, suffix, maxcons;
    Node () : len(0), prefix(0), suffix(0), maxcons(0) {};
};

class lazySegTree {
    vector<arr<Node, 2>> sg;
    vector<int> lz;
public:
    lazySegTree(int n) : sg(4*n+1), lz(4*n+1, 0) {};

    arr<Node, 2> merge (const arr<Node, 2> a, const arr<Node, 2> b) {
        arr<Node, 2> now;
        for (int i = 0; i < 2; ++i) {
            now[i].len = a[i].len + b[i].len;
            now[i].prefix = a[i].prefix;
            if (a[i].len == a[i].prefix) {
                now[i].prefix += b[i].prefix;
            }
            now[i].suffix = b[i].suffix;
            if (b[i].len == b[i].suffix) {
                now[i].suffix += a[i].suffix;
            }
            now[i].maxcons = max({a[i].maxcons, b[i].maxcons, a[i].suffix + b[i].prefix});
        }
        return now;
    }

    void build(int s, int e, int i = 1) {
        if (s == e) {
            int x = v[s] - '0';
            sg[i][0].len = 1;
            sg[i][1].len = 1;
            if (x) {
                sg[i][1].prefix = 1;
                sg[i][1].suffix = 1;
                sg[i][1].maxcons = 1;
            }
            else {
                sg[i][0].prefix = 1;
                sg[i][0].suffix = 1;
                sg[i][0].maxcons = 1;
            }
            return;
        }
        int mid = (s + e) / 2;
        build(s, mid, 2*i);
        build(mid+1, e, 2*i+1);
        sg[i] = merge(sg[2*i], sg[2*i+1]);
    }

    void Apply(int s, int e, int val, int i) {
        swap(sg[i][0], sg[i][1]);
        lz[i] ^= 1;
    }

    void Push (int s, int mid, int e, int i) {
        if (lz[i]) {
            Apply(s, mid, lz[i], 2*i);
            Apply(mid+1, e, lz[i], 2*i+1);
        }
        lz[i] = 0;
    }

    void upd (int lb, int rb, int val, int s, int e, int i = 1) {
        if (s > rb ||  e < lb) return;
        if (s >= lb && e <= rb) {
            Apply(s, e, val, i);
            return;
        }
        int mid = (s + e) / 2;
        Push(s, mid, e, i);
        upd(lb, rb, val, s, mid, 2*i);
        upd(lb, rb, val, mid+1, e, 2*i+1);
        sg[i] = merge(sg[2*i], sg[2*i+1]);
    }

    arr<Node, 2> qry (int lb, int rb, int s, int e, int i = 1) {
        if (s > rb || e < lb) return arr<Node, 2> ();
        if (s >= lb && e <= rb) return sg[i];
        int mid = (s + e) / 2;
        Push(s, mid, e, i);
        return merge(qry(lb, rb, s, mid, 2*i), qry(lb, rb, mid+1, e, 2*i+1));
    }
};

void Din() {
    int n, q;
    cin >> n >> q >> v;
    v = "#" + v;

    lazySegTree t(n);

    t.build(1, n);

    while (q--) {
        int tp, lb, rb;
        cin >> tp >> lb >> rb;
        if (tp == 1) {
            t.upd(lb, rb, 1, 1, n);
        }
        else {
            auto ans = t.qry(lb, rb, 1, n);
            cout << ans[1].maxcons << "\n";
        }
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

https://atcoder.jp/contests/abc322/tasks/abc322_f

*/