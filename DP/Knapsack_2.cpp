/*
    author: Din_ED
    Time: 22:30:08
    Date: 18-10-2025
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

void Din() {
    int n, w;
    cin >> n >> w;

    vector<int> weight(n + 1), val(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> weight[i] >> val[i];
    }

    int m = accumulate(all(val), 0);

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 1e9));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j] = dp[i - 1][j]; // if not take...
            if (j - val[i] >= 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - val[i]] + weight[i]);
            }
        }
    }

    const int mxN = 1e5;
    for (int i = m; i; --i) {
        if (dp[n][i] <= w) {
            cout << i << "\n";
            return;
        }
    }
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
