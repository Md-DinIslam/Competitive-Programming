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

template<class T>
struct RMQ {
    vector<vector<T>> sp;
    RMQ () {}
    RMQ (vector<T> &v) : sp(1, v) {
        int n = sz(v);
        for (int i = 1, p = 1; p * 2 <= n; p *= 2, ++i) {
            sp.emplace_back(n-2*p+1);
            for (int j = 0; j < sz(sp[i]); ++j) {
                sp[i][j] = min(sp[i-1][j], sp[i-1][j+p]);
            }
        }
    }

    T qry (int a, int b) {
        b += 1;
        int len = 31 - __builtin_clz(b-a);
        return min(sp[len][a], sp[len][b-(1<<len)]);
    }
};

struct suffixArray {
    string s;
    int n;
    vector<int> idx, lcp, rank;
    RMQ <int> rmq;
    
    suffixArray (string &now, int lim = 256) {
        s = now; s.push_back(0);
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

        temp.clear();
        for (int i = 1; i < n; ++i) {
            temp.push_back(lcp[i]);
        }
        rmq = RMQ <int> (temp);
    }

    int getLCP (int i, int j) {
        if (i == j) return n - i - 1;
        i = rank[i], j = rank[j];
        if (i > j) swap(i, j);
        j -= 1;
        return rmq.qry(i, j);
    }
};

void Din() {
    int n;
    cin >> n;
    string a;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        a.push_back(x + '0');
    }

    string s = a + a;
    suffixArray t(s);
    
    dbg(a, s);
    dbg(t.lcp);

    int best_k = 1;
    for (int i = 1; i < n; ++i) {
        int len = t.getLCP(best_k, i);
        if (len >= n) continue;
        if (s[len] != s[(i + len) % n]) {
            best_k = i;
        }
    }

    // dbg(best_k);

    char o = '0';
    for (int i = 0; i < n; ++i) {
        int x = (s[i] - o) ^ (s[i+best_k] - o);
        cout << x << " ";
    }
    cout << '\n';
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


// https://codeforces.com/gym/106356/problem/E