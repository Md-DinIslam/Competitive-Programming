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

    vector<int> price(n + 1), books(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> price[i];
    }

    for (int i = 1; i <= n; ++i) {
        cin >> books[i];
    }
    
    // vector<vector<int>> dp(n + 1, vector<int> (x + 1, 0));

    // for (int i = 1; i <= n; ++i) {
    //     for (int tk = 0; tk <= x; ++tk) {
    //         dp[i][tk] = dp[i - 1][tk]; // not take...
    //         if (tk - price[i] >= 0) {
    //             dp[i][tk] = max(dp[i][tk], dp[i - 1][tk - price[i]] + books[i]);
    //         }

    //     }
    // }

    // cout << dp[n][x] << '\n';
    
    vector<int> dp(x + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int j = x; j >= price[i]; --j) {
            dp[j] = max(dp[j], dp[j - price[i]] + books[i]);
        }
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
