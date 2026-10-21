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

struct Cx {
    dbl a, b;
    Cx (dbl _a = 0, dbl _b = 0) : a(_a), b(_b) {}
    Cx operator+(Cx o) const { return Cx(a+o.a, b+o.b); }
    Cx operator-(Cx o) const { return Cx(a-o.a, b-o.b); }
    Cx operator*(Cx o) const { return Cx(a*o.a-b*o.b, a*o.b+b*o.a); }
};
void FFT (vector<Cx> &p, bool inv = 0) {
    int n = sz(p);
    static vector<Cx> rt(2, Cx(1));
    for (int z = sz(rt); z < n; z *= 2) {
        rt.resize(2*z);
        for (int j = 0; j < z; ++j) {
            ld g = PI*j/z;
            rt[z+j] = Cx(cosl(g), sinl(g));
        }
    }
    for (int i = 1, j = 0; i < n; ++i) {
        int b = n >> 1;
        for (; j & b; b >>= 1) j ^= b;
        j ^= b;
        if (i < j) swap(p[i], p[j]);
    }
    for (int z = 1; z < n; z *= 2) {
        for (int i = 0; i < n; i += 2*z) {
            for (int j = 0; j < z; ++j) {
                Cx t = rt[z+j]*p[i+j+z];
                p[i+j+z] = p[i+j]-t;
                p[i+j] = p[i+j]+t;
            }
        }
    }
    if (inv) {
        reverse(p.begin()+1, p.end());
        for (auto &x : p)
            x.a /= n, x.b /= n;
    }
}

template<class T>
vector<ll> mulFFT (vector<T> &a, vector<T> &b) {
    if (!sz(a) || !sz(b)) return {};
    int nm = sz(a)+sz(b)-1;
    int n = 1;
    while (n < nm) n *= 2;
    vector<Cx> x(n);
    for (int i = 0; i < n; ++i) {
        if (i < sz(a)) x[i].a = a[i];
        if (i < sz(b)) x[i].b = b[i];
    }
    FFT(x);
    for (auto &c : x) c = c * c;
    FFT(x, 1);
    vector<ll> ans(nm);
    for (int i = 0; i < nm; ++i)
        ans[i] = llround(x[i].b / 2);
    return ans;
}

const int mxN = 1e6 + 9;
vector<int> cnt(mxN, 0);

void Din() {
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt[x] += 1;
    }

    auto conv = mulFFT(cnt, cnt);
    ll ans = 0;
    for (int i = 0; i < mxN; ++i) {
        if (cnt[i]) {
            ans += conv[2*i] / 2;
        }
    }

    cout << ans << "\n";
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


// https://atcoder.jp/contests/abc392/tasks/abc392_g