/*
    author: Din_ED
    Time: 17:13:43
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

typedef uint64_t ull;

struct H {
    ull x;
    H (ull _x = 0) : x(_x) {}
    H operator+(H o) const { return x + o.x + (x + o.x < x); }
    H operator-(H o) const { return *this + ~o.x; }
    H operator*(H o) const {
        auto m = (__uint128_t) x * o.x;
        return H((ull)m) + (ull) (m >> 64);
    }
    ull get() const { return x + !~x; }
    bool operator==(H o) const {return get() == o.get(); }
    bool operator<(H o) const {return get() < o.get(); } 
};

const H prime = (ll) 1e11 + 3;

struct hashInterval {
    struct Node {
        H hsh = 0;
        int len = 0;
    };
    int n;
    vector<H> pw;
    vector<Node> sg;
    hashInterval (string &s) {
        n = sz(s);
        sg.resize(4*n+1);
        pw.resize(n+1);
        pw[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pw[i] = pw[i-1] * prime;
        }
        for (int i = 1; i <= n; ++i) {
            upd(i, s[i-1], 1, n);
        }
    }

    Node merge (const Node &a, const Node &b) {
        Node temp;
        temp.hsh = a.hsh * pw[b.len] + b.hsh;
        temp.len = a.len + b.len;
        return temp;
    }

    void upd (int idx, char val, int s, int e, int i = 1) {
        if (s == e) {
            sg[i] = {val, 1};
            return;
        }
        int mid = (s + e) / 2;
        if (idx <= mid) {
            upd (idx, val, s, mid, 2*i);
        }
        else {
            upd (idx, val, mid+1, e, 2*i+1);
        }
        sg[i] = merge(sg[2*i], sg[2*i+1]);
    }

    Node qry (int lb, int rb, int s, int e, int i = 1) {
        if (s > rb || e < lb) return {0, 0};
        if (s >= lb && e <= rb) return sg[i];
        int mid = (s + e) / 2;
        return merge(qry(lb, rb, s, mid, 2*i), qry(lb, rb, mid+1, e, 2*i+1));
    }
};

void Din() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;

    hashInterval prefix(s);
    reverse(all(s));
    hashInterval suffix(s);
    
    while (q--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int idx;
            char ch;
            cin >> idx >> ch;
            prefix.upd(idx, ch, 1, n);
            suffix.upd(n-idx+1, ch, 1, n);
        }
        else {
            int lb, rb;
            cin >> lb >> rb;
            H hsh_prefix = prefix.qry(lb, rb, 1, n).hsh;
            H hsh_suffix = suffix.qry(n-rb+1, n-lb+1, 1, n).hsh;
            if (hsh_prefix == hsh_suffix) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
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
