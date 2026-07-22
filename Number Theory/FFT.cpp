/*
    author: Din_ED
    Time: 05:51:39
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
#define dbl double
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) int(x.size())
#define arr array
#define PI acos(-1.0)

const int mxN = 1e6 + 9;
vector<int> cnt(mxN);

struct Base { // complex number
    dbl a, b;
    Base (dbl _a = 0, dbl _b = 0) : a(_a), b(_b) {}
    Base operator+(const Base &o) const { 
        return Base(a+o.a, b+o.b); 
    }
    Base operator-(const Base &o) const { 
        return Base(a-o.a, b-o.b); 
    }
    Base operator*(const Base &o) const { 
        return Base(a*o.a - b*o.b, a*o.b + b*o.a);
    }
};

void FFT (vector<Base> &p, bool inv = 0) {
    int n = sz(p), i = 0;
    for (int j = 1; j < n-1; ++j) {
        int k = n/2;
        while (k > (i ^= k)) k /= 2;
        if (j < i) swap(p[i], p[j]);
    }
    for (int z = 1; 2*z <= n; z *= 2) {
        dbl ang = 2*PI/(2*z);
        Base wj = Base(cos(ang), (inv?1:-1)*sin(ang)), w;
        for (int i = 0, j, k; i < n; i += 2*z) {
            for (w = Base(1, 0), j = i, k = i+z; j < k; ++j, w = w*wj) {
                Base t = w * p[j+z];
                p[j+z] = p[j] - t; p[j] = p[j] + t;
            }
        }
    }
    if (inv)  {
        for (int i = 0; i < n; ++i) {
            p[i].a /= n; p[i].b /= n;
        }
    }
}

vector<ll> multiply(vector<int> &a, vector<int> &b) {
    int n = sz(a), m = sz(b), nm = n+m-1, lg = 1;
    while (lg < nm) lg*=2;
    vector<Base> x(lg), y(lg);
    for (int i = 0; i < lg; ++i) {
        x[i] = i < n ? Base(a[i], 0) : Base(0, 0);
        y[i] = i < m ? Base(b[i], 0) : Base(0, 0);
    }
    FFT(x), FFT(y);
    for (int i = 0; i < lg; ++i) x[i] = x[i] * y[i];
    FFT(x, 1);
    vector<ll> ans(lg);
    for (int i = 0; i < lg; ++i) ans[i] = (ll) round(x[i].a);
    while(sz(ans) > 1 && ans.back()==0) ans.pop_back();
    return ans;
}

void Din() {
    int n; 
    cin >> n;

    vector<int> v(n);
    for (auto &x : v) {
        cin >> x;
        cnt[x] = 1;
    }

    // dg(v);

    auto ans = multiply(cnt, cnt);
    ll now = 0;
    for (int i = 0; i < mxN; ++i) {
        if (cnt[i]) {
            now += ans[2*i]/2;
        }
    }
    cout << now << "\n";
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