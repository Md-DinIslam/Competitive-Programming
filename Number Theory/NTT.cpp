/*
    author: Din_ED
    Time: 21:15:22
    Date: 21-10-2026
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
#define dbl double
#define ld long double
#define PI acosl(-1.0)
#define vll vector<ll>

const int mod = 998244353;

// NTT<M>: M = c*2^k+1 prime (998244353: len<=2^23, 167772161: 2^25, 469762049: 2^26), root R=3
template<int M, int R = 3> struct NTT {
    ll binExp(ll a, ll b) {
        ll ans = 1;
        for (a %= M; b; b >>= 1, a = a * a % M)
            if (b & 1) ans = ans * a % M;
        return ans;
    }
    void run(vll &p, bool inv = 0){
        int n = sz(p);
        assert((M-1) % n == 0); // too big
        vll rt(2, 1);
        for (int z = sz(rt); z < n; z*=2) {
            rt.resize(2*z);
            ll g = binExp(R, (M-1)/ (2*z));
            rt[z] = 1;
            for (int k = 1; k < z; ++k) 
                rt[z+k] = rt[z+k-1]*g%M;
        }
        for (int i = 1, j = 0; i < n; ++i){
            int b = n >> 1;
            for (; j & b; b>>=1) j ^= b;
            j ^= b;
            if (i < j) swap(p[i], p[j]);
        }
        for (int z = 1; z < n; z *= 2) {
            for (int i = 0; i < n; i += 2*z) {
                for (int k = 0; k < z; ++k) {
                    ll x = p[i+k], y = p[i+k+z] * rt[z+k] % M;
                    p[i+k] = x+y >= M ? x+y-M : x+y;
                    p[i+k+z] = x-y < 0 ? x-y+M : x-y;
                }
            }
        }
        if (inv) {
            reverse(p.begin()+1, p.end());
            ll ni = binExp(n, M-2);
            for (auto &x : p) x = x*ni%M;
        }
    }
    vll mul(vll a, vll b) {
        if (!sz(a) || !sz(b)) return {};
        for (auto &x : a) x = (x%M+M)%M;
        for (auto &x : b) x = (x%M+M)%M;
        int nm = sz(a)+sz(b)-1, n = 1;
        while (n < nm) n *= 2;
        a.resize(n), b.resize(n);
        run(a), run(b);
        for (int i = 0; i < n; ++i)
            a[i] = a[i] * b[i] % M;
        run(a, 1); a.resize(nm);
        return a;
    }
};

// Any modulus M (1e9+7, 1e9+9, ...), M <= ~2e9, |a|+|b|-1 <= 2^23. 3 NTTs + Garner CRT.
// 998244353, 167772161, 469762049
vll mulMod(vll a, vll b, ll M) {
    if (!sz(a) || !sz(b)) return {};
    for (auto &x : a) x = (x%M+M)%M;
    for (auto &x : b) x = (x%M+M)%M;
    const ll p1 = (119 << 23)+1, p2 = (5 << 25)+1, p3 = (7 << 26)+1;
    NTT<p1> x; NTT<p2> y; NTT<p3> z;
    auto r = x.mul(a, b), s = y.mul(a, b), t = z.mul(a, b);
    ll k1 = y.binExp(p1, p2-2), k2 = z.binExp(p1*p2%p3, p3-2), p12 = p1%M*(p2%M)%M;
    for (int i = 0; i < sz(r); ++i) {
        ll j1 = ((s[i]-r[i])%p2+p2) % p2 * k1 % p2;
        ll j2 = ((t[i]-r[i] - p1 % p3 * j1) % p3 + p3) % p3 * k2 % p3;
        r[i] = (r[i]%M+p1%M * j1 + p12 * j2) % M;
    }
    return r;
}

void Din() {
    int n, m;
    cin >> n >> m;
    
    vector<ll> a(n), b(m);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;

    NTT<mod> t;
    auto conv = t.mul(a, b);
    // auto conv = mulMod(a, b, mod);

    for (auto &x : conv) {
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


// https://atcoder.jp/contests/practice2/tasks/practice2_f