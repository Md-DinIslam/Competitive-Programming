/*
    author: Din_ED
    Time: 00:37:31
    Date: 17-10-2025
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

void Din() {
    int n;
    cin >> n;

    ll k = n * (n + 1) / 2;
    if (k & 1) {
        cout << "0\n";
        return;
    }

    dg(k);
    k /= 2;

    vector<int> v(n + 1);
    iota(all(v), 0);

    vector<ll> dp(k + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int sum = k; sum >= 0; --sum) {
            if (sum - v[i] >= 0) {
                dp[sum] += dp[sum - v[i]];
                dp[sum] %= mod;
            }
        }
    }

    // dg(dp);
    // dg(k);
    // cout << dp[k] / 2 << '\n';
    ll ans = dp[k] * binExp(2, mod - 2) % mod;
    cout << ans << '\n';
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
