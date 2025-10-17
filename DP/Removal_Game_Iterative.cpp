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
#define vll vector<vector<ll>>

const int mod = 1e9 + 7;
const ll inf = 1e18;

vector<int> v;
vll dp;

void Din() {
    int n;
    cin >> n;

    v.assign(n + 1, 0);
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
        ans += v[i];
    }

    dp.assign(n + 1, vector<ll>(n + 1, 0));

    for (int i = n; i > 0; --i) {
        for (int j = i; j <= n; ++j) {
            if (i == j) {
                dp[i][j] = v[i];
            }
            else {
                dp[i][j] = max(v[i] - dp[i + 1][j], v[j] - dp[i][j - 1]);
            }
        }
    }

    // dg(dp);

    ans += dp[1][n];
    ans /= 2;

    cout << ans << '\n';
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
