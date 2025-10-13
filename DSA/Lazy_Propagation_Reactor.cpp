/*
    author: Din_ED
    Time: 01:17:18
    Date: 13-10-2025
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

const ll inf = 1e18;

vector<ll> v;

struct Node {
    ll min_x, cnt, done;
};

class lazySegTree {
    vector<Node> sg;
    vector<ll> lz, max_p, lz2;
public:
    lazySegTree(int n) : sg(4 * n + 1, {inf, 0, 0}), lz(4 * n + 1), lz2(lz), max_p(lz) {};

    void build(int s, int e, int i = 1) {
        if (s == e) {
            sg[i].min_x = v[s];
            max_p[i] = v[s];
            if (v[s] == 1) {
                sg[i].done = 1;
                sg[i].min_x = inf;
                max_p[i] = inf;
            }
        }
        else {
            int mid = (s + e) / 2;
            build(s, mid, 2 * i);
            build(mid + 1, e, 2 * i + 1);
            sg[i] = merge(sg[2 * i], sg[2 * i + 1]);
        }
    }

    Node merge(Node a, Node b) {
        ll min_x = min(a.min_x, b.min_x);
        ll cnt = a.cnt + b.cnt;
        ll done = a.done + b.done;
        return {min_x, cnt, done};
    }

    void Apply(int s, int e, ll val, ll x, int i) {
        sg[i].min_x -= val;
        sg[i].cnt += sg[i].done * x;
        lz[i] += val;
        lz2[i] += x;
    }

    void Push(int s, int mid, int e, int i) {
        if (lz[i]) {
            Apply(s, mid, lz[i], lz2[i], 2 * i);
            Apply(mid + 1, e, lz[i], lz2[i], 2 * i + 1);
        }
        lz[i] = 0;
        lz2[i] = 0;
    }

    void upd2(int lb, int rb, int s, int e, int i = 1) {
        if (s > rb || e < lb) return;
        if (s >= lb && e <= rb) {
            if (sg[i].min_x > 0) return;
        }
        if (s == e) {
            sg[i].cnt += 1;
            v[s] = max(v[s] / 2, 1ll);
            sg[i].min_x = v[s];
            if (v[s] == 1) {
                sg[i].min_x = inf;
                sg[i].done = 1;
                v[s] = inf;
            }
        }
        else {
            int mid = (s + e) / 2;
            Push(s, mid, e, i);
            upd2(lb, rb, s, mid, 2 * i);
            upd2(lb, rb, mid + 1, e, 2 * i + 1);
            sg[i] = merge(sg[2 * i], sg[2 * i + 1]);
        }
    }

    void upd(int lb, int rb, ll val, ll x, int s, int e, int i = 1) {
        if (s > rb || e < lb) return;
        if (s >= lb && e <= rb) {
            Apply(s, e, val, x, i);
        }
        else {
            int mid = (s + e) / 2;
            Push(s, mid, e, i);
            upd(lb, rb, val, x, s, mid, 2 * i);
            upd(lb, rb, val, x, mid + 1, e, 2 * i + 1);
            sg[i] = merge(sg[2 * i], sg[2 * i + 1]);
        }
    }

    Node qry(int lb, int rb, int s, int e, int i = 1) {
        if (s > rb || e < lb) return {inf, 0, 0};
        if (s >= lb && e <= rb) return sg[i];
        int mid = (s + e) / 2;
        Push(s, mid, e, i);
        return merge(qry(lb, rb, s, mid, 2 * i), qry(lb, rb, mid + 1, e, 2 * i + 1));
    }
};

void Din() {
    int n, q;
    cin >> n >> q;

    v.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }

    lazySegTree t(n);
    t.build(1, n);

    while (q--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int lb, rb, val;
            cin >> lb >> rb >> val;
            t.upd(lb, rb, val, 1ll, 1, n);

            Node ans = t.qry(lb, rb, 1, n);
            if (ans.min_x < 1) {
                t.upd2(lb, rb, 1, n);
            }
        }
        else {
            int lb, rb;
            cin >> lb >> rb;
            cout << t.qry(lb, rb, 1, n).cnt << '\n';
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

https://codeforces.com/gym/106084/problem/I

*/