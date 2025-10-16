/*
    author: Din_ED
    Time: 19:21:55
    Date: 15-10-2025
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

void Din() {
    int n, m;
    cin >> n >> m;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }

    vector<vector<ll>> dp(n + 1, vector<ll> (m + 1, 0));
    // dp[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        if (i == 1) {
            for (int j = 1; j <= m; ++j) {
                dp[i][j] = 1;
            }
        }
        else {
            for (int j = 1; j <= m; ++j) {
                dp[i][j] += dp[i - 1][j];
                dp[i][j] += dp[i - 1][j - 1];
                if (j + 1 <= m)
                    dp[i][j] += dp[i - 1][j + 1];
                dp[i][j] %= mod;
            }
        }
        if (v[i] != 0) {
            for (int j = 1; j <= m; ++j) {
                if (v[i] != j) {
                    dp[i][j] = 0;
                }
            }
        }
    }

    ll ans = 0ll;
    for (int j = 1; j <= m; ++j) {
        ans += dp[n][j];
        ans %= mod;
    }

    // cout << dp[n][m] << '\n';
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
