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
    int n, k;
    cin >> n >> k;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }

    vector<vector<ll>> dp(n + 1, vector<ll> (k + 1));
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        // prefix sum of previous row...
        for (int j = 1; j <= k; ++j) {
            dp[i - 1][j] += dp[i - 1][j - 1];
            dp[i - 1][j] %= mod;
        }

        for (int j = 0; j <= k; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j - v[i] > 0) {
                // can not distribute, so subtract it..
                int k = j - v[i] - 1;
                dp[i][j] -= dp[i - 1][k];
            }

            dp[i][j] = (dp[i][j] % mod + mod) % mod;
        }
    }

    // dg(dp);

    cout << dp[n][k] << '\n';
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
