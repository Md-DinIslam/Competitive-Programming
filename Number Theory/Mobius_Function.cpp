/*
    author: Din_ED
    Time: 13:36:14
    Date: 16-11-2025
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

const int mxN = 1e5 + 1;

vector<ll> a, b, freq_a, freq_b, cnt_a, cnt_b, spf(mxN), mob(mxN, -1);

void preCal() {
    iota(all(spf), 0);
    for (int i = 2; i * i < mxN; ++i) {
        if (spf[i] == i) {
            for (int j = i * i; j < mxN; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }

    mob[1] = 1;
    for (int i = 2; i < mxN; ++i) {
        if (spf[i] != i) {
            int p = spf[i];
            int x = i / p;
            if (x % p == 0) {
                mob[i] = 0;
            }
            else {
                mob[i] = -mob[x];
            }
        }
    }
}

void reset(int n) {
    a.assign(n+1, 0);
    b.assign(n+1, 0);
    freq_a.assign(n+1, 0);
    freq_b.assign(n+1, 0);
    cnt_a.assign(n+1, 0);
    cnt_b.assign(n+1, 0);
}

void Din() {
    int n;
    cin >> n;

    reset(n);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        freq_a[a[i]] += 1;
    }
    
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        freq_b[b[i]] += 1;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            cnt_a[i] += freq_a[j];
            cnt_b[i] += freq_b[j];
        }
    }

    ll ans = 0;
    for (int i = 2; i <= n; ++i) {
        if (spf[i] != i) continue;
        ll add = 0;
        for (int j = 1; j * i <= n; ++j) {
            int d = j * i;
            add += (mob[j] * cnt_a[d] * cnt_b[d]);
        }
        ans += add;
    }
    
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    preCal();
    for (int i = 1; i <= t; ++i) {
        // cout << "Case " << i << ": ";
        Din();
    }
    return 0;
}
