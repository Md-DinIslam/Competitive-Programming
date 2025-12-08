/*
    author: Din_ED
    Time: 23:09:59
    Date: 05-12-2025
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
#define ff first
#define ss second
#define vi vector<int>
#define rep(i, a, n) for(int i = a; i < n; ++i)

template <class T>
struct RMQ {
    vector<vector<T>> sp;
    RMQ (vector<T> &v) : sp(1, v) {
        int n = sz(v);
        for (int i = 1, p = 1; p * 2 <= n; p *= 2, ++i) {
            sp.emplace_back(n - p * 2 + 1);
            int m = sz(sp[i]);
            for (int j = 0; j < m; ++j) {
                sp[i][j] = max(sp[i - 1][j], sp[i - 1][j + p]);
            }
        }
    }

    T qry(int a, int b) {
        b += 1; // exlucsive
        int len = 31 - __builtin_clz(b - a);
        return max(sp[len][a], sp[len][b - (1 << len)]);
    }
};

// - Description: z[i] computes the length of the longest common prefix of s[i:] and s,

// - except z[0] = 0. (abacaba -> 0010301)

vi Z(const string &s, int n) {
    vi v(n);
    int l = -1, r = -1;
    rep(i, 1, n) {
        v[i] = i >= r ? 0 : min(r - i, v[i - l]);
        while (i + v[i] < n && s[i + v[i]] == s[v[i]]) {
            v[i] += 1;
        }
        if (i + v[i] > r) {
            l = i, r = i + v[i];
        }
    }
    return v;
}

void Din() {
    string s;
    cin >> s;

    int n = sz(s);
    auto ans = Z(s, n);
    RMQ rmq(ans);

    int len = 0;
    for (int i = 1; i < n; ++i) {
        if (i + ans[i] == n) {
            int prefix_len = ans[i];
            if (i > 1) {
                int mid_len = rmq.qry(1, i - 1);
                if (mid_len >= prefix_len) {
                    len = max(len, prefix_len);
                }
            }
        }
    }

    if (len == 0) {
        cout << "Just a legend\n";
    }
    else {
        cout << s.substr(0, len) << "\n";
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


/*

https://codeforces.com/problemset/problem/126/B

*/