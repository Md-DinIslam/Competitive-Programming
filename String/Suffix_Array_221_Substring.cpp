/*
    author: Din_ED
    Time: 04:36:44
    Date: 30-07-2026
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

struct suffixArray {
    string s;
    vector<int> ans, lcp;
    int n;
    suffixArray(string _s, int lim = 256) {
        s = _s;
        s.push_back('#');
        n = sz(s);
        int k = 0, a, b;
        vector<int> rank(all(s)), temp(n), cnt(max(n, lim));
        ans = lcp = temp;
        iota(all(ans), 0);

        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j;
            iota(all(temp), n - j);
            for (int i = 0; i < n; ++i) {
                if (ans[i] >= j) {
                    temp[p++] = ans[i] - j;
                }
            }
            fill(all(cnt), 0);
            for (int i = 0; i < n; ++i) {
                cnt[rank[i]] += 1;
            }
            for (int i = 1; i < lim; ++i) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = n; i--;) {
                ans[--cnt[rank[temp[i]]]] = temp[i];
            }

            swap(rank, temp);
            p = 1;
            rank[ans[0]] = 0;

            for (int i = 1; i < n; ++i) {
                a = ans[i - 1];
                b = ans[i];
                if (temp[a] == temp[b] && temp[a + j] == temp[b + j]) {
                    rank[b] = p - 1;
                }
                else {
                    rank[b] = p++;
                }
            }

        }
        // Kasai's Algorithm
        for (int i = 0, j = 0; i < n - 1; lcp[rank[i++]] = k) {
            for (k && k--, j = ans[rank[i] - 1]; i + k < n && j + k < n && s[i + k] == s[j + k] && (s[i+k] != '$' && s[i+k] != '#'); k++);
        }
    }

    void show () {
        dg(ans);
        for (int i = 0; i < n; ++i) {
            cout << s.substr(ans[i]) << "\n";
        }
        dg(lcp);
    }
};

void Din() {
    int n;
    cin >> n;

    vector<int> v(n);
    for (auto &x : v) {
        cin >> x;
    }
    
    string s;
    for (int i = 0; i < n;) {
        int j = i;
        int cnt = 0;
        while (j < n && v[i] == v[j]) {
            cnt += 1;
            j += 1;
        }
        char ch = char('0' + v[i]);
        if (cnt == v[i]) {
            s.push_back(ch);
        }
        else if (cnt > v[i]) {
            s.push_back(ch);
            s.push_back('$');
            s.push_back(ch);
        }
        else {
            s.push_back('$');
        }
        i = j;
    }

    suffixArray t(s);
    // dg(s);

    // t.show();
    s.push_back('$');
    
    int m = sz(s);
    ll ans = 0;
    for (int i = 0; i < m;) {
        if (s[i] == '$') {
            i += 1;
            continue;

        }
        int j = i, cnt = 0;
        while (j < m && s[j] != '$') {
            cnt += 1;
            j += 1;
        }
        ans += (1ll * cnt * (cnt+1) / 2);
        i = j;
    }

    for (int i = 0; i < sz(t.lcp); ++i) {
        ans -= t.lcp[i];
    }

    cout << ans << "\n";
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

// https://atcoder.jp/contests/abc452/tasks/abc452_g
