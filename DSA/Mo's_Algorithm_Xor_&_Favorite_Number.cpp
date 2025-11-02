/*
    author: Din_ED
    Time: 21:49:18
    Date: 01-11-2025
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

const int mxN = 1e5 + 10, mxV = 3e6 + 10;
vector<ll> v(mxN), freq(mxV);

int n, q, k;
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
} query[mxN];

void add(int x) {
    int need = k ^ x;
    cnt += freq[need];
    freq[x] += 1;
    // cerr << "Cnt: " << cnt << " Need -> " << need << ", " << freq[need] << '\n';
}

void remove(int x) {
    freq[x] -= 1;
    int need = k ^ x;
    cnt -= freq[need];
}

void Din() {
    cin >> n >> q >> k;

    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
        v[i] ^= v[i-1];
        // cerr << v[i] << " \n"[i == n - 1];
    }

    int len = (int) sqrtl(n) + 1;
    for (int i = 0; i < q; ++i) {
        int lb, rb;
        cin >> lb >> rb;
        query[i].lb = lb - 1, query[i].rb = rb;
        query[i].indx = i, query[i].block = query[i].lb / len;
    }

    sort(query, query + q);
    
    freq[0] += 1; // if R start with 1...

    int L = 0, R = 1; // 1'based, start with 1

    // other way, comment freq[0] line, and can start L = R = 0....

    for (int i = 0; i < q; ++i) {
        while (R <= query[i].rb) add(v[R++]);
        while (R > query[i].rb + 1) remove(v[--R]);
        while (L < query[i].lb) remove(v[L++]);
        while (L > query[i].lb) add(v[--L]);

        // cerr << query[i].lb << " " << query[i].rb << '\n';
        // cerr << "\n";
        int indx = query[i].indx;
        query[indx].ans = cnt;
    }
    
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
