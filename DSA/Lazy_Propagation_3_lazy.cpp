/*
    author: Din_ED
    Time: 02:04:37
    Date: 09-11-2026
*/

#include <bits/stdc++.h>
#include <cassert>
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

struct Node {
    ll maxa, up, down;
    Node () : maxa(0), up(0), down(0) {}
};

struct lazySegTree {
    vector<Node> sg;
    vector<ll> lz;
    vector<int> lz2;
    vector<bool> lazyDada;
    
    lazySegTree (int n) : sg(4*n+1), lz(4*n+1, 0), lz2(4*n+1, 0), lazyDada(4*n+1, 0) {
        build(1, n);
    }

    void build (int s, int e, int i = 1) {
        if (s == e) {
            sg[i].up = 1;
            return;
        }
        int mid = (s + e) / 2;
        build(s, mid, 2*i);
        build(mid+1, e, 2*i+1);
        sg[i] = Merge(sg[2*i], sg[2*i+1]);
    }

    Node Merge (const Node &a, const Node &b) {
        Node temp;
        temp.up = a.up + b.up;
        temp.down = a.down + b.down;
        temp.maxa = max(a.maxa, b.maxa);
        return temp;
    }

    void Apply (int s, int e, ll val, int flip, int bal, int i) {
        if (bal) { // flip
            sg[i].maxa = 0;
            if (flip) {
                swap(sg[i].up, sg[i].down);
                lz2[i] ^= 1;
            }

            lz[i] = 0;
            lazyDada[i] = 1;
        }
        if (sg[i].up) {
            sg[i].maxa += val;
            lz[i] += val;
        }
    }

    void Push(int s, int mid, int e, int i) {
        if (lz[i] || lz2[i] || lazyDada[i]) {
            Apply(s, mid, lz[i], lz2[i], lazyDada[i], 2*i);
            Apply(mid+1, e, lz[i], lz2[i], lazyDada[i], 2*i+1);
        }
        lz[i] = 0;
        lz2[i] = 0;
        lazyDada[i] = 0;
    }

    void upd (int lb, int rb, ll val, int flip, int s, int e, int i = 1) {
        if (s > rb || e < lb) return;
        if (s >= lb && e <= rb) {
            Apply(s, e, val, flip, flip, i);
            return;
        }
        int mid = (s + e) / 2;
        Push(s, mid, e, i);
        upd(lb, rb, val, flip, s, mid, 2*i);
        upd(lb, rb, val, flip, mid+1, e, 2*i+1);
        sg[i] = Merge(sg[2*i], sg[2*i+1]);
    }

    Node qry (int lb, int rb, int s, int e, int i = 1) {
        if (s > rb || e < lb) return Node();
        if (s >= lb && e <= rb) return sg[i];
        int mid = (s + e) / 2;
        Push(s, mid, e, i);
        return Merge(qry(lb, rb, s, mid, 2*i), qry(lb, rb, mid+1, e, 2*i+1));
    }
};

void Din() {
    int n, q;
    cin >> n >> q;

    lazySegTree t(n);

    while (q--) {
        int qt, lb, rb;
        cin >> qt >> lb >> rb;
        if (qt == 1) {
            ll val;
            cin >> val;
            t.upd(lb, rb, val, false, 1, n);
        }
        else if (qt == 2){
            t.upd(lb, rb, 0, true, 1, n);
        }
        else {
            cout << t.qry(lb, rb, 1, n).maxa << "\n";
        }

        // for (int i = 1; i <= n; ++i) {
        //     auto now = t.qry(i, i, 1, n);
        //     dbg(qt, i, now.upSum, now.up, now.maxa);
        // }
        // dbg("==");
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


// https://atcoder.jp/contests/abc441/tasks/abc441_g