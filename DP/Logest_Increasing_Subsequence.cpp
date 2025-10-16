/*
    author: Din_ED
    Time: 23:49:56
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

void Din() {
    int n;
    cin >> n;

    vector<int> v(n);
    vector<int> ans;

    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        if (i == 0 || v[i] > ans.back()) {
            ans.push_back(v[i]);
        }
        else {
            auto indx = lower_bound(all(ans), v[i]);
            ans[indx - begin(ans)] = v[i];
        }
    }

    // dg(ans);

    cout << sz(ans) << "\n";
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
