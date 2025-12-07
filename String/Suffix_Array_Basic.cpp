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

struct suffixArray {
    vector<int> ans, lcp;
    suffixArray(string s, int lim = 256) {
        s.push_back(0);
        int n = sz(s), k = 0, a, b;
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

            // Kasai's Algorithm
            for (int i = 0, j = 0; i < n - 1; lcp[rank[i++]] = k) {
                for (k && k--, j = ans[rank[i] - 1]; i + k < n && j + k < n && s[i + k] == s[j + k]; k++);
            }
        }
    }
};

void Din() {
    string s;
    cin >> s;

    int n = sz(s) + 1;
    suffixArray t(s);

    for (int i = 0; i < sz(t.ans); ++i) {
        cout << t.ans[i] << " ";
        // cout << s.substr(t.ans[i], n - t.ans[i]) << '\n';
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
