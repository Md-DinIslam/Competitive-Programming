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
    int n, x;
    cin >> n >> x;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }

    vector<ll> dp(x + 1, 1e9);
    dp[0] = 0;
    for (int j = 1; j <= x; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (j - v[i] >= 0) {
                dp[j] = min(dp[j], dp[j - v[i]] + 1);
            }
        }
    }

    dg(dp);

    if (dp[x] == 1e9) {
        dp[x] = -1;
    }

    cout << dp[x] << '\n';
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
