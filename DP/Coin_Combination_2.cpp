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
    int n, x;
    cin >> n >> x;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }

    sort(all(v));

    vector<ll> dp(x + 1, 0);
    dp[0] = 1;

    // iterate for each value, getting distinct order ways..
    for (int i = 1; i <= n; ++i) { 
        for (int sum = 1; sum <= x; ++sum) {
            if (sum - v[i] >= 0) {
                dp[sum] += dp[sum - v[i]];
                dp[sum] %= mod;
            }
        }
    }
    
    cout << dp[x] << "\n";
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
