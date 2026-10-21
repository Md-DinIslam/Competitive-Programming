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
#define lld long double
#define PI acosl(-1.0)

struct Cx {
    dbl a, b;
    Cx (dbl _a = 0, dbl _b = 0) : a(_a), b(_b) {}
    Cx operator+(Cx o) const { return Cx(a+o.a, b+o.b); }
    Cx operator-(Cx o) const { return Cx(a-o.a, b-o.b); }
    Cx operator*(Cx o) const { return Cx(a*o.a-b*o.b, a*o.b+b*o.a); }
};

void FFT (vector<Cx> &p, bool inv = 0) {
    int n = sz(p);
    vector<Cx> rt(2, Cx(1));
    for (int z = sz(rt); z < n; z *= 2) {
        rt.resize(2*z);
        for (int j = 0; j < z; ++j) {
            lld g = PI * j / z;
            rt[z + j] = Cx(cosl(g), sinl(g));
        }
    }
    for (int i = 1, j = 0; i < n; ++i) {
        int b = n >> 1;
        for (; j & b; b >>= 1) j ^= b;
        j ^= b;
        if (i < j) swap(p[i], p[j]);
    }
    for (int z = 1; z < n; z *= 2) {
        for (int i = 0; i < n; i += 2 * z) {
            for (int j = 0; j < z; ++j) {
                Cx t = rt[z+j] * p[i+j+z];
                p[i+j+z] = p[i+j] - t;
                p[i+j] = p[i+j] + t;
            }
        }
    }
    if (inv) {
        reverse(p.begin()+1, p.end());
        for (auto &x : p) x.a /= n, x.b /= n;
    }
}

template<class T>
vector<ll> mulFFT (vector<T> &a, vector<T> &b) {
    if (a.empty() || b.empty()) return {};
    int nm = sz(a) + sz(b) - 1, n = 1;
    while (n < nm) n *= 2;
    vector<Cx> x(n), y(n);
    for (int i = 0; i < sz(a); ++i) {
        x[i].a = a[i];
    }
    for (int i = 0; i < sz(b); ++i) {
        y[i].a = b[i];
    }
    FFT(x), FFT(y);
    for (int i = 0; i < n; ++i) {
        x[i] = x[i] * y[i];
    }
    FFT (x, 1);
    vector<ll> ans(nm);
    for (int i = 0; i < nm; ++i) {
        ans[i] = llround(x[i].a);
    }
    return ans;
}

void Din() {
    string s, t;
    cin >> s >> t;

    int n = sz(s), m = sz(t);
    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) {
        a[i] = (s[i] == '1' ? 1 : -1);
    }
    for (int i = 0; i < m; ++i) {
        b[m-i-1] = (t[i] == '1' ? 1 : -1);
    }

    auto ans = mulFFT(a, b);
    // dbg(ans);
    // m = match + mismatch, mismatch = m - match,
    // ans[i+m-1] = match count
    int mismatches = m;
    for (int i = 0; i <= n - m; ++i) {
        // dbg(ans[i+m-1]);
        int now = (m - ans[i+m-1]) / 2;
        mismatches = min(mismatches, now);
    }

    cout << mismatches << '\n';
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

// https://atcoder.jp/contests/abc196/tasks/abc196_f