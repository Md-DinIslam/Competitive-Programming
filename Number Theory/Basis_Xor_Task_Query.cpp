/*
    author: Din_ED
    Time: 01:40:15
    Date: 10-10-2025
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

const int mod = 1e9 + 7;

template<class T, int m = 31>
struct vecBasis {
    vector<T> basis;
    T b_size = 0;

    vecBasis() : basis(m, 0) {}

    void insert(T x) {
        for (int i = m - 1; ~i; --i) {
            if ((x >> i) & 1) {
                if (basis[i]) {
                    x ^= basis[i];
                }
                else {
                    b_size += 1;
                    basis[i] = x;
                    break;
                }
            }
        }
    }

    bool isPossible(T x) {
        for (int i = m - 1; ~i; --i) {
            x = min(x, x ^ basis[i]);
        }
        return x == 0;
    }

    T getMax() {
        T ans = 0;
        for (int i = m - 1; ~i; --i) {
            ans = max(ans, ans ^ basis[i]);
        } return ans;
    }

    T uniqueSubset() {
        dg(b_size);
        return (1 << b_size);
    }

    T getCnt(int n) {
        // dg(n, b_size);
        T cnt = (n - b_size) % mod;
        return binExp(2, cnt);
    }

    void view() {
        dg(basis);
    }

    ll binExp(ll a, ll b) {
        ll ans = 1;
        while (b) {
            if (b & 1) {
                ans = (ans * a) % mod;
            }
            a = (a * a) % mod;
            b >>= 1;
        }
        return ans;
    }
};

void Din() {
    int n, q;
    cin >> n >> q;

    vecBasis<int, 21> t;

    vector<ll> v(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }

    vector<vector<arr<int, 2>>> query(n + 1);
    for (int i = 1; i <= q; ++i) {
        int lb, x;
        cin >> lb >> x;
        // dg(lb, x);
        // query[i] = {lb, x, i};
        query[lb].push_back({x, i});
    }

    // dg(query);
    // dg(query[5]);

    vector<ll> ans(q + 1);
    for (int i = 1; i <= n; ++i) {
        t.insert(v[i]);
        // dg(t.uniqueSubset());

        for (auto &[x, indx] : query[i]) {
            // dg("got it", i);
            if (t.isPossible(x)) {
                // dg(x, indx, i, t.b_size);
                ans[indx] = t.getCnt(i);
            }
        }
    }

    // t.view();

    for (int i = 1; i <= q; ++i) {
        cout << ans[i] << "\n";
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

input:
5 5
0 1 2 3 4
4 3
2 0
3 7
5 7
5 8

output:
4
2
0
4
0


*/