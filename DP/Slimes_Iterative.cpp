/*
    author: Din_ED
    Time: 17:17:54
    Date: 20-10-2025
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

vector<ll> p;
vector<vector<ll>> dp;

void Din() {
    int n;
    cin >> n;

    vector<int> v(n + 1);
    p.assign(n + 1, 0);
    dp.assign(n + 1, vector<ll> (n + 1, 1e18));

    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
        p[i] = p[i - 1] + v[i];
    }

    // dp[0][0] = 0;

    for (int i = 0; i <= n; ++i) {
        dp[i][i] = 0;
    }

    for (int it = 1; it < n; ++it) {
        for (int i = 1; i + it <= n; ++i) {
            int j = i + it;
            for (int k = i; k < j; ++k) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + (p[j] - p[i - 1]));
            }
        }
    }

    // dg(dp[1]);

    cout << dp[1][n] << '\n';
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
