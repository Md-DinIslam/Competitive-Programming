/*
    author: Din_ED
    Time: 21:47:04
    Date: 19-10-2025
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
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    for (auto &x : v) {
        cin >> x;
    }

    vector<int> dp(k + 1, 0);

    for (int j = 0; j <= k; ++j) {
        for (int i = 0; i < n; ++i) {
            if (j - v[i] >= 0) {
                dp[j] |= (dp[j - v[i]] == 0);
            }
        }
    }

    // for (int i = 0; i <= n; ++i) {
    //     dg(dp[i]);
    // }

    cout << (dp[k] == 1 ? "First" : "Second");
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