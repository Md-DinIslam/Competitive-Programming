/*
    author: Din_ED
    Time: 23:20:42
    Date: 15-10-2026
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

struct AhoCorasick {
    enum {alpha = 26, first = 'a'}; // can change
    struct Node {
        int back, next[alpha], start = -1, end = -1, nmatches = 0;
        Node (int v) {
            memset(next, v, sizeof(next));
        }
    };

    vector<Node> N;
    vector<int> backp, bfsOrd, patNode;

    void insert(string &s, int j) {
        assert(!s.empty());
        int n = 0;
        for (char c : s) {
            int &m = N[n].next[c-first];
            if (m == -1) {
                n = m = sz(N);
                N.emplace_back(-1);
            }
            else {
                n = m;
            }
        }
        if (N[n].end == -1) {
            N[n].start = j;
        }
        backp.push_back(N[n].end);
        N[n].end = j;
        N[n].nmatches++;
        patNode.push_back(n);
    }

    AhoCorasick (vector<string> &pat) : N(1, -1) {
        for (int i = 0; i < sz(pat); ++i) {
            insert(pat[i], i);
        }
        
        N[0].back = sz(N);
        N.emplace_back(0);

        queue<int> q;
        for (q.push(0); !q.empty(); q.pop()) {
            int n = q.front(), prev = N[n].back;
            bfsOrd.push_back(n);
            for (int i = 0; i < alpha; ++i) {
                int &ed = N[n].next[i], y = N[prev].next[i];
                if (ed == -1) ed = y;
                else {
                    N[ed].back = y;
                    (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
                    N[ed].nmatches += N[y].nmatches;
                    q.push(ed);
                }
            }
        }
    }

    vector<int> find(string &word) {
        int n = 0;
        vector<int> ans;
        for (char c : word) {
            n = N[n].next[c-first];
            ans.push_back(N[n].end);
        }
        return ans;
    }

    vector<int> getCnt (int m, string &word) {
        vector<int> nodeCnt(sz(N), 0);
        int n = 0;
        for (char c : word) {
            n = N[n].next[c-first];
            nodeCnt[n] += 1;
        }
        for (int i = sz(bfsOrd)-1; i > 0; --i) {
            int u = bfsOrd[i];
            nodeCnt[N[u].back] += nodeCnt[u];
        }
        vector<int> ans(m, 0);
        for (int i = 0; i < m; ++i) {
            ans[i] = nodeCnt[patNode[i]];
        }
        return ans;
    }
};

void Din() {
    int q;
    string s;
    cin >> q >> s;

    vector<string> pat(q);
    for (int i = 0; i < q; ++i) {
        cin >> pat[i];
    }

    AhoCorasick aho(pat);
    vector<int> ans = aho.getCnt(q, s);
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case " << i << ":\n";
        Din();
    }
    return 0;
}
