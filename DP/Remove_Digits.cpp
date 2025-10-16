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

    vector<int> dp(n+1, 1e9);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        vector<int> digit;
        int temp = i;
        while (temp > 0){
            int rem = temp % 10;
            digit.push_back(rem);
            temp /= 10;
        }
        for (auto &x : digit) {
            dp[i] = min(dp[i], dp[i - x] + 1);
        }
    }

    cout << dp[n] << '\n';
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
