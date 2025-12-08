/*
    author: Din_ED
    Time: 19:32:21
    Date: 08-12-2025
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
#define vi vector<int>
#define rep(i, a, n) for(int i = a; i < n; ++i)

arr<vi, 2> manacher(const string &s, int n) {
    arr<vi, 2> p = {vi(n + 1), vi(n)};
    rep(z, 0, 2) {
        for (int i = 0, l = 0, r = 0; i < n; ++i) {
            int t = r - i + !z;
            if (i < r) p[z][i] = min(t, p[z][l + t]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1]) {
                p[z][i]++, L--, R++;
            }
            if (R > r) l = L, r = R;
        }
    }
    return p;
}

void Din() {
    string s;
    cin >> s;

    int n = sz(s);

    auto [even, odd] = manacher(s, n);

    int len = 1, pos = 0;
    for (int i = 0; i < n; ++i) {
        if (even[i]) {
            int curr_len = 2 * even[i];
            if (curr_len > len) {
                len = curr_len;
                pos = i - even[i];
            }
        }
        if (odd[i]) {
            int curr_len = 2 * odd[i] + 1;
            if (curr_len > len) {
                len = curr_len;
                pos = i - odd[i];
            }
        }
    }

    cout << s.substr(pos, len) << "\n";
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
