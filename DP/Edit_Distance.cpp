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
    string a, b;
    cin >> a >> b;

    int n = a.size();
    int m = b.size();

    vector<vector<int>> dp(n + 1, vector<int> (m + 1, 0));
    // dp[0][0] = 0;
    // for (int i = 1; i <= n; ++i) {
    //     dp[i][0] = 0;
    // }
    // for (int j = 1; j <= m; ++j) {
    //     dp[0][j] = 0;
    // }

    a = "#" + a;
    b = "#" + b;

    for (int i = 1; i <= n; ++i) {
        dp[i][0] = i;
        for (int j = 1; j <= m; ++j) {
            dp[0][j] = j;
            dp[i][j] = 1e9;
            if (a[i] == b[j]) {
                // dg(a[i], b[j], i, j);
                dp[i][j] = dp[i - 1][j - 1];
            }
            else {
                int min_cost = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                // dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
                // dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
                // dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
                dp[i][j] = min(dp[i][j], min_cost);
            }
        }
    }

    cout << dp[n][m] << '\n';
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
