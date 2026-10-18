/*
    author: Din_ED
    Time: 18:48:29
    Date: 18-10-2026
*/

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(x...)
#endif

#define ll long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) int(x.size())
#define arr array

struct suffixArray {
    string s;
    int n;
    vector<int> idx, lcp, rank;
    
    suffixArray (string &now, int lim = 256) {
        s = now;
        s.push_back(0);
        n = sz(s);
        int k = 0, a, b;
        rank = vector<int> (all(s));
        vector<int> temp(n), cnt(max(n, lim));
        idx = lcp = temp;
        iota(all(idx), 0);

        for (int j = 0, p = 0; p < n; j = max(1, 2*j), lim = p) {
            p = j;
            iota(all(temp), n-j);
            for (int i = 0; i < n; ++i) {
                if (idx[i] >= j) {
                    temp[p++] = idx[i] - j;
                }
            }
            fill(all(cnt), 0);
            for (int i = 0; i < n; ++i) {
                cnt[rank[i]] += 1;
            }
            for (int i = 1; i < lim; ++i) {
                cnt[i] += cnt[i-1];
            }
            for (int i = n; i--;) {
                idx[--cnt[rank[temp[i]]]] = temp[i];
            }
            swap(rank, temp);
            p = 1;
            rank[idx[0]] = 0;
            for (int i = 1; i < n; ++i) {
                a = idx[i-1];
                b = idx[i];
                if (temp[a] == temp[b] && temp[a + j] == temp[b + j]) {
                    rank[b] = p-1;
                }
                else {
                    rank[b] = p++;
                }
            }
        }

        // Kasai's Algo
        for (int i = 0, j = 0; i < n-1; lcp[rank[i++]] = k) {
            for (k && k--, j = idx[rank[i]-1]; i + k < n && j + k < n && s[i + k] == s[j + k]; k++) {}
        }
    }
};

void Din() {
    string s;
    cin >> s;

    int n = sz(s);

    suffixArray t(s);
    dbg(t.lcp);

    auto lcp = t.lcp;
    lcp.push_back(0);

    vector<ll> cnt(n+1, 0);
    vector<int> prev(n+1, 0), next(n+1, n+1);

    stack<int> st;
    for (int i = 1; i <= n; ++i) {
        while (sz(st) && lcp[st.top()] >= lcp[i]) {
            st.pop();
        }
        if (sz(st)) {
            prev[i] = st.top();
        }
        st.push(i);
    }

    while (sz(st)) st.pop();

    for (int i = n; i >= 1; --i) {
        while (sz(st) && lcp[st.top()] > lcp[i]) {
            st.pop();
        }
        if (sz(st)) {
            next[i] = st.top();
        }
        st.push(i);
    }

    for (int i = 1; i <= n; ++i) {
        if (lcp[i] == 0) continue;
        int L = lcp[prev[i]], R = lcp[next[i]];
        int new_lenght_subCnt = lcp[i] - max(L, R);
        int indx_cnt = next[i] - prev[i];
        cnt[indx_cnt] += 1ll * new_lenght_subCnt * indx_cnt;
    }

    cnt[1] = 1ll * n * (n+1) / 2;
    for (int i = n-1; i > 1; --i) {
        cnt[i] += cnt[i+1];
    }

    // dbg(cnt);
    // dbg(prev);
    // dbg(next);

    int q;
    cin >> q;
    while (q--) {
        int f;
        cin >> f;

        if (f > n) {
            cout << "0\n";
        }
        else {
            cout << cnt[f] << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        // cout << "Case " << i << ": ";
        Din();
    }
    return 0;
}

// https://www.codechef.com/problems/ANUSAR