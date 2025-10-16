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
int n;

ll getAns(int i, int j) {
    if (i == j) return v[i];
    if (i > n || j <= 0 || i > j) return 0ll;

    ll &ans = dp[i][j];
    if (ans != -inf) return ans;

    ans = max(ans, v[i] - getAns(i + 1, j));
    ans = max(ans, v[j] - getAns(i, j - 1));

    return ans;
}

void Din() {
    // int n;
    cin >> n;

    v.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }

    dp.assign(n + 1, vector<ll> (n + 1, -inf));

    ll taru = getAns(1, n);
    ll ans = accumulate(all(v), 0ll) + taru;
    
    // dg(ans / 2);
    // cout << taru << '\n';
    cout << ans / 2 << '\n';
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
