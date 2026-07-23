/*
    author: Din_ED
    Time: 01:32:24
    Date: 24-07-2026
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

vector<int> v, root;

struct Node {
    ll sum;
    int lc, rc;
    Node () : sum(0), lc(0), rc(0) {}
};

class persistentSegTree {
    vector<Node> sg;
    int RT;
public: // Alert 40*n for PST
    persistentSegTree (int _n) : sg(40*_n+1), RT(1) {}

    int build (int s, int e) {
        int cur = RT++; // root
        if (s == e) return cur;
        int mid = (s + e) / 2 ;
        sg[cur].lc = build(s, mid);
        sg[cur].rc = build(mid+1, e);
        sg[cur].sum = sg[sg[cur].lc].sum + sg[sg[cur].rc].sum;
        return cur;
    }

    int upd (int prev, int indx, ll val, int s, int e) {
        int cur = RT++;
        sg[cur] = sg[prev];
        if (s == e) {
            sg[cur].sum = val; // set
            return cur;
        }
        int mid = (s + e) / 2;
        if (indx <= mid) {
            sg[cur].lc = upd(sg[prev].lc, indx, val, s, mid);
        }
        else {
            sg[cur].rc = upd(sg[prev].rc, indx, val, mid+1, e);
        }
        sg[cur].sum = sg[sg[cur].lc].sum + sg[sg[cur].rc].sum;
        return cur;
    }

    ll qry (int i, int lb, int rb, int s, int e) {
        if (s > rb || e < lb) return 0ll;
        if (s >= lb && e <= rb) return sg[i].sum;
        int mid = (s + e) / 2;
        return (qry(sg[i].lc, lb, rb, s, mid) + qry(sg[i].rc, lb, rb, mid+1, e));
    }
};

void Din() {
    int n, q;
    cin >> n >> q;

    v.assign(n+1, 0);
    // root.assign(n+1, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }

    persistentSegTree t(n);

    root.push_back(t.build(1, n));
    for (int i = 1; i <= n; ++i) {
        root[0] = t.upd(root[0], i, v[i], 1, n);
    }

    root.push_back(root[0]);

    // for (int i = 1; i <= n; ++i) {
    //     dg(t.qry(root[1], 1, i, 1, n));
    // }

    while (q--) {
        int qt;
        cin >> qt;
        if (qt == 1) { // upd
            int k, indx, val;
            cin >> k >> indx >> val;
            root[k] = t.upd(root[k], indx, val, 1, n);
        }
        else if (qt == 2) { // sum
            int k, L, R;
            cin >> k >> L >> R;
            cout << t.qry(root[k], L, R, 1, n) << "\n";
        }
        else { // copy
            int k;
            cin >> k;
            root.push_back(root[k]);
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

// https://cses.fi/problemset/task/1737