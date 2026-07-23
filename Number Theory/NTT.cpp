/*
    author: Din_ED
    Time: 20:05:48
    Date: 22-07-2026
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
#define vi vector<int>
#define vll vector<ll>

const int mxN = 1 << 20, root = 3;
const int mod = 998244353;

ll lim, inv_lim;
vll rev(mxN), wo(mxN), wj(mxN);

void reduce(ll &x) {x = (x+mod) % mod;}
ll binExp(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1) ans = (ans * a) % mod;
        a = (a * a) % mod; b >>= 1;
    }
    return ans;
}
void preCal(int len) {
    int LOG = -1;
    lim = wj[0] = 1;
    while (lim < len) lim *= 2, LOG++;
    for (int i = 0; i < lim; ++i) {
        rev[i] = (rev[i/2] / 2) | (i & 1) << LOG;
    }
    const ll g = binExp(root, (mod-1) / lim);
    inv_lim = binExp(lim, mod-2);
    for (int i = 1; i < lim; ++i) wj[i] = (wj[i-1]*g) % mod;
}
void NTT(vll &p, int ok = 0) {
    for (int i = 1; i < lim; ++i) {
        if (i < rev[i]) swap(p[i], p[rev[i]]);
    }
    for (int i = 1; i < lim; i *= 2) {
        for (int j = 0, t = lim/i/2; j < i; ++j) {
            wo[j] = wj[j*t];
        }
        for (int j = 0; j < lim; j += (2*i)) {
            for (int k = 0; k < i; ++k) {
                const ll x = p[k+j], y = (p[k+j+i]*wo[k]) % mod;
                reduce(p[k+j] += y-mod), reduce(p[k+j+i] = x-y);
            }
        }
    }
    if (ok) {
        reverse(begin(p)+1, begin(p)+lim);
        for (int i = 0; i < lim; ++i) p[i] = (p[i]*inv_lim)%mod;
    }
}
vll multiply(vll &a, vll &b) {
    if (a.empty() || b.empty()) return {};
    int n = sz(a)+sz(b)-1; preCal(n);
    vll x = a, y = b;
    x.resize(lim), y.resize(lim);
    NTT(x), NTT(y);
    for (int i = 0; i < lim; ++i) x[i] = (x[i]*y[i])%mod;
    NTT(x, 1); x.resize(n);
    return x;
}
void Din() {
    int n, m;
    cin >> n >> m;

    vll a(n), b(m);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;

    // dg(mxN);
    // dg(binExp(3, 3));
    auto ans = multiply(a, b);
    for (auto &x : ans) {
        cout << x << " ";
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

// atcoder: Convolution