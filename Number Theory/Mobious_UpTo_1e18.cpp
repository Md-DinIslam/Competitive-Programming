/*
    author: Din_ED
    Time: 02:48:32
    Date: 26-07-2026
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

const int mxN = 50000100;
vector<int> spf(mxN), mob(mxN), prefixMob(mxN);

void precompute () {
    iota(all(spf), 0);
    for (int i = 2; i * i < mxN; ++i) {
        if (spf[i] == i) {
            for (int j = i*i; j < mxN; j += i) {
                spf[j] = spf[i];
            }
        }
    }

    mob[1] = 1;
    prefixMob[1] = 1;
    for (int i = 2; i < mxN; ++i) {
        if (spf[i] == i) {
            mob[i] = -1; 
        }
        else {
            int p = spf[i];
            int x = i / p;
            if (x % p == 0) {
                mob[i] = 0;
            }
            else {
                mob[i] = -mob[x];
            }
        }

        prefixMob[i] = prefixMob[i-1] + mob[i];
    }
}

unordered_map<ll, ll> dp;

int getMertens (ll n) {
    if (n < mxN) return prefixMob[n];
    if (dp.count(n)) return dp[n];
    
    ll ans = 1;
    for (ll i = 2, nxt; i <= n; i = nxt + 1) {
        // 5/3 = 1, 5/1 = 5, range [3, 5] cover same mobious[q]
        ll q = n / i;
        nxt = n / q;
        ans -= (nxt - i + 1) * getMertens(q);
    }

    return dp[n] = ans;
}

void Din() {
    ll n;
    cin >> n;

    ll sq = sqrtl(n);
    ll ans = 0, last = 0;
    for (ll i = 1, nxt; i <= sq; i = nxt + 1) {
        // same like getMertens but cover range for square
        ll val = n / (i*i);
        ll nxt_sq = sqrtl(n/val);
        nxt = min(sq, nxt_sq);
        ll curr = getMertens(nxt);
        ans += (curr - last) * val; // inclusion/exclusion
        last = curr;
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    // cin >> t;
    precompute();
    for (int i = 1; i <= t; ++i) {
        // cout << "Case " << i << ": ";
        Din();
    }
    return 0;
}
