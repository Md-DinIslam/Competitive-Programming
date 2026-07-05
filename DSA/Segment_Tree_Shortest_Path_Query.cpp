/*
    author: Din_ED
    Time: 18:56:37
    Date: 05-07-2026
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

const ll inf = 1e12;

vector<string> v(5);

struct Node {
    ll mat[4][4];
    Node () { // identity matrix...
        for (int i = 1; i <= 3; ++i) {
            for (int j = 1; j <= 3; ++j) {
                mat[i][j] = inf;
                if (i == j) {
                    mat[i][j] = 0;
                }
            }
        }
    }
};

class segTree {
    vector<Node> sg;
public:
    segTree (int n) : sg(4*n+1) {};

    Node merge (const Node &a, const Node &b) {
        Node now;
        for (int i = 1; i <= 3; ++i) {
            for (int j = 1; j <= 3; ++j) {
                ll &best = now.mat[i][j];
                best = inf;
                for (int k = 1; k <= 3; ++k) {
                    best = min(best, a.mat[i][k] + b.mat[k][j]);
                }
            }
        }
        return now;
    }

    void upd (int indx, Node &val, int s, int e, int i = 1) {
        if (s == e) {
            sg[i] = val;
            return;
        }
        int mid = (s + e) / 2;
        if (indx <= mid) {
            upd (indx, val, s, mid, 2*i);
        }
        else {
            upd (indx, val, mid+1, e, 2*i+1);
        }
        sg[i] = merge(sg[2*i], sg[2*i+1]);
    }

    ll qry () {
        ll ans = sg[1].mat[1][3];
        if (ans >= inf) return -1;
        return ans-1;
    }
};

Node getValue (int col) {
    Node now;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            int L = i, R = j;
            if (L > R) swap(L, R);
            now.mat[i][j] = R - L + 1;
            for (int k = L; k <= R; ++k) {
                if (v[k][col] == '#') {
                    now.mat[i][j] = inf;
                    break;
                }
            }
        }
    }
    return now;
}

void Din() {
    int n;
    cin >> n;
    
    for (int i = 1; i <= 3; ++i) {
        cin >> v[i];
        v[i] = "*" + v[i];
    }

    segTree t(n);

    for (int i = 1; i <= n; ++i) {
        Node val = getValue(i); // getting value for each column..
        t.upd(i, val, 1, n);
    }

    int q;
    cin >> q;
    while (q--) {
        int r, c;
        cin >> r >> c;

        v[r][c] = (v[r][c] == '.' ? '#' : '.');

        Node val = getValue(c);
        t.upd(c, val, 1, n);

        cout << t.qry() << "\n";
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

https://atcoder.jp/contests/abc429/tasks/abc429_f

*/