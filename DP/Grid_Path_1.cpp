/*
    author: Din_ED
    Time: 23:00:46
    Date: 14-10-2025
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
    int n;
    cin >> n;

    vector<string> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }

    vector<vector<ll>> dp(n+1, vector<ll> (n+1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 0) {
                dp[i][j] = 1;
            }
            else {
                if (i) {
                    dp[i][j] += dp[i-1][j];
                    dp[i][j] %= mod;
                }
                if (j) {
                    dp[i][j] += dp[i][j-1];
                    dp[i][j] %= mod;
                }
            }
            if (s[i][j] == '*') {
                dp[i][j] = 0;
            }
        }
    }

    cout << dp[n-1][n-1] << '\n';
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
