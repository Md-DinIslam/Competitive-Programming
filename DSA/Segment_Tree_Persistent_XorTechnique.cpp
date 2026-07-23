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
        sg[cur].sum = sg[sg[cur].lc].sum ^ sg[sg[cur].rc].sum;
        return cur;
    }

    int upd (int prev, int indx, ll val, int s, int e) {
        int cur = RT++;
        sg[cur] = sg[prev];
        if (s == e) {
            sg[cur].sum ^= val;
            return cur;
        }
        int mid = (s + e) / 2;
        if (indx <= mid) {
            sg[cur].lc = upd(sg[prev].lc, indx, val, s, mid);
        }
        else {
            sg[cur].rc = upd(sg[prev].rc, indx, val, mid+1, e);
        }
        sg[cur].sum = sg[sg[cur].lc].sum ^ sg[sg[cur].rc].sum;
        return cur;
    }

    int qry (int prev, int cur, int s, int e) {
        if ((sg[prev].sum ^ sg[cur].sum) == 0) return 0;
        if (s == e) return s;
        int mid = (s + e) / 2;
        ll leftXor = sg[sg[prev].lc].sum ^ sg[sg[cur].lc].sum;
        if (leftXor != 0) {
            return qry(sg[prev].lc, sg[cur].lc, s, mid);
        }
        else {
            return qry(sg[prev].rc, sg[cur].rc, mid+1, e);
        }
    }
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll getRand(ll a, ll b) {
    uniform_int_distribution<ll> interval(a, b);
    return interval(rng);
}

void Din() {
    int n;
    cin >> n;

    v.assign(n+1, 0);
    root.assign(n+1, 0);
    
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }
    
    // dg(1ll << 60);
    vector<ll> hash(n+1);
    for (int i = 1; i <= n; ++i) {
        hash[i] = getRand(1, 2e18);
    }
    
    // dg(hash);
    
    auto sorted_v = v;
    sort(all(sorted_v));
    sorted_v.erase(unique(all(sorted_v)), sorted_v.end());
    // dg(sorted_v);

    persistentSegTree t(n);
    root[0] = t.build(1, n);

    for (int i = 1; i <= n; ++i) {
        int id = lower_bound(all(sorted_v), v[i])-begin(sorted_v);
        root[i] = t.upd(root[i-1], id, hash[id], 1, n);
        // dg(id, hash[id]);
    }

    // for (int i = 1; i <= n; ++i) {
    //     dg(t.qry(root[1], 1, i, 1, n));
    // }

    int q;
    cin >> q;
    ll last = 0;

    while (q--) {
        int L, R;
        cin >> L >> R;
        L ^= last; R ^= last;
        L -= 1;
        dg(L, R);
        assert(L >= 0 && L < R && R <= n);
        int indx = t.qry(root[L], root[R], 1, n);
        assert(indx >= 0 && indx <= n);
        last = sorted_v[indx];
        cout << last << "\n";
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

// https://codeforces.com/contest/1771/problem/F
