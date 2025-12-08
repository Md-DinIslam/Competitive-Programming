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

template <class T>
struct RMQ {
    vector<vector<T>> sp;
    RMQ (vector<T> &v) : sp(1, v) {
        int n = sz(v);
        for (int i = 1, p = 1; p * 2 <= n; p *= 2, ++i) {
            sp.emplace_back(n - p * 2 + 1);
            int m = sz(sp[i]);
            for (int j = 0; j < m; ++j) {
                sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + p]);
            }
        }
    }

    T qry(int a, int b) {
        b += 1; // exlucsive
        int len = 31 - __builtin_clz(b - a);
        return min(sp[len][a], sp[len][b - (1 << len)]);
    }
};

struct suffixArray {
    string s;
    vector<int> ans, lcp, rank;
    int n;
    RMQ <int> *rmq;

    suffixArray(string _s, int lim = 256) {
        s = _s;
        s.push_back(0);
        n = sz(s);
        int k = 0, a, b;
        rank = vector<int>(all(s));
        vector<int> temp(n), cnt(max(n, lim));
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

        dg(ans, lcp, rank);

        vector<int> new_temp(n);
        for (int i = 1; i < n; ++i) {
            new_temp[i - 1] = lcp[i];
        }

        rmq = new RMQ<int>(new_temp);
    }

    int getLCP(int i) {return lcp[i];}
    int getLCP(int i, int j) {
        i = rank[i], j = rank[j];
        if (i > j) swap(i, j);
        return rmq->qry(i, j);
    }
    
    arr<int, 2> getLCS() {
        int best = 0, pos = -1;
        for (int i = 1; i < n; ++i) {
            if (lcp[i] > best) {
                best = lcp[i];
                pos = ans[i];
            }
        }
        
        if (best == 0) return {-1, -1};
        return {pos, best};
    }
};

void Din() {
    string s;
    cin >> s;

    int n = sz(s);
    suffixArray t(s);

    auto [pos, len] = t.getLCS();
    // dg(pos, len);
    if (pos == -1) {
        cout << "-1\n";
    }
    else {
        cout << s.substr(pos, len) << '\n';
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
