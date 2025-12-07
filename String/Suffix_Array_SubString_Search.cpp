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
    string s;
    vector<int> ans, lcp;
    int n;
    suffixArray(string _s, int lim = 256) {
        s = _s;
        s.push_back(0);
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

            // Kasai's Algorithm
            for (int i = 0, j = 0; i < n - 1; lcp[rank[i++]] = k) {
                for (k && k--, j = ans[rank[i] - 1]; i + k < n && j + k < n && s[i + k] == s[j + k]; k++);
            }
        }
    }
    
    bool findSubStr(const string &pat, int m) {
        int lb = 0, rb = n-1;
        while (lb <= rb) {
            int mid = lb + (rb - lb) / 2;
            int pos = ans[mid]; // index from suffix array
            
            int k = 0;
            while (k < m && pos + k < n && s[pos + k] == pat[k]) {
                k += 1;
            }
            
            if (k == m) return 1;
            
            if (pos + k < n && s[pos + k] > pat[k]) {
                rb = mid - 1;
            }
            else {
                lb = mid + 1;
            }
        }
        return 0;
    }
};

void Din() {
    string s;
    cin >> s;
    
    suffixArray t(s);

    // for (int i = 0; i < sz(t.ans); ++i) {
    //     cout << t.ans[i] << " ";
    //     // cout << s.substr(t.ans[i], n - t.ans[i]) << '\n';
    // }
    
    int q;
    cin >> q;
    
    while (q--) {
        string pat;
        cin >> pat;
        
        if (t.findSubStr(pat, sz(pat))) {
            cout << "Yes\n";
        } 
        else {
            cout << "No\n";
        }
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
