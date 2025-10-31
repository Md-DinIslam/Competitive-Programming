/*
    author: Din_ED
    Time: 20:15:09
    Date: 28-10-2025
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

const int mxN = 2e4 + 10;
vector<ll> v(mxN), bit(mxN);

int n, q;
ll cnt = 0;

struct Node {
    int lb, rb, block, indx;
    ll ans;
    bool operator<(const Node &Q) const {
        if (block == Q.block) { // zig-zag
            return (block & 1 ? rb > Q.rb : rb < Q.rb);
        }
        return (block < Q.block);
    }
};

bool cmp(const Node &a, const Node &b) {
    return a.indx < b.indx;
}

void upd(int i, int val) {
    while (i > 0 && i <= n) {
        bit[i] += val;
        i += (i & -i);
    }
}

ll qry(int i) {
    ll ans = 0;
    while (i > 0) {
        ans += bit[i];
        i -= (i & -i);
    }
    return ans;
}

void add(int x, int dir) {
    if (dir == 1) { // going Left..
        cnt += qry(x-1); 
    }
    else if (dir == 2) { // going Right.. 
        cnt += qry(n) - qry(x);
    }
    upd(x, 1);
}

void remove(int x, int dir) {
    upd(x, -1);
    if (dir == 1) { // going Left..
        cnt -= qry(x-1);
    }
    else if (dir == 2) { // going Right.. 
        cnt -= (qry(n) - qry(x));
    }
}

void Din() {
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    vector<ll> temp(v.begin(), v.begin()+n);
    sort(all(temp));
    for (int i = 0; i < n; ++i) {
        v[i] = lower_bound(all(temp), v[i]) - temp.begin() + 1;
        cerr << v[i] << " \n"[i == n-1];
    }

    cin >> q;

    Node query[q+1];

    int len = (int) sqrtl(n) + 1;
    for (int i = 0; i < q; ++i) {
        int lb, rb;
        cin >> lb >> rb;
        query[i].lb = lb - 1, query[i].rb = rb - 1;
        query[i].indx = i, query[i].block = query[i].lb / len;
    }

    sort(query, query + q);
    
    int L = 0, R = 0;
    for (int i = 0; i < q; ++i) {
        while (R <= query[i].rb) add(v[R++], 2);
        while (R > query[i].rb + 1) remove(v[--R], 2);
        while (L < query[i].lb) remove(v[L++], 1);
        while (L > query[i].lb) add(v[--L], 1);

        cerr << query[i].lb << " " << query[i].rb << '\n';
        query[i].ans = cnt;
        cerr << cnt << '\n';
    }
    
    sort(query, query + q, cmp);

    for (int i = 0; i < q; ++i) {
        cout << query[i].ans << '\n';
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

https://www.codechef.com/problems/IITI15

*/