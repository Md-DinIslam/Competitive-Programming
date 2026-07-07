/*
    author: Din_ED
    Time: 14:45:06
    Date: 07-07-2026
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

struct Trie {
    static const int ALPHABET = 26;
    struct Node {
        int nxt[ALPHABET];
        int cntEnd = 0;
        int cntPrefix = 0;
        int bestCnt = 0;
        string bestWord = "";
    };

    vector<Node> t;

    Trie() {
        t.emplace_back();
        memset(t[0].nxt, -1, sizeof(t[0].nxt));
    }

    int newNode() {
        t.emplace_back();
        memset(t.back().nxt, -1, sizeof(t.back().nxt));
        return sz(t) - 1;
    }

    void insert(const string &s) {
        int cur = 0;
        vector<int> path = {cur};
        for (auto &ch : s) {
            int x = ch - 'a';
            if (t[cur].nxt[x] == -1) {
                int indx = newNode();
                t[cur].nxt[x] = indx;
            }
            cur = t[cur].nxt[x];
            path.push_back(cur);
            // t[cur].cntPrefix++;
        }

        t[cur].cntEnd++;
        // dg(s, t[cur].cntEnd);
        
        int now = t[cur].cntEnd;
        for (auto &node : path) {
            if (now > t[node].bestCnt) {
                t[node].bestCnt = now;
                t[node].bestWord = s;
            }
            else if (now == t[node].bestCnt) {
                string prev_best = t[node].bestWord;
                if (sz(prev_best) == 0 || s < prev_best) {
                    t[node].bestWord = s;
                }
            }
        }
        
        // dg(s, t[cur].bestCnt, t[cur].bestWord);
    }

    string getAns(const string &s) {
        int cur = 0;
        for (auto ch : s) {
            int x = ch - 'a';
            if (t[cur].nxt[x] == -1) return "-1";
            cur = t[cur].nxt[x];
        }

        string ans = t[cur].bestWord + " " + to_string(t[cur].bestCnt);
        return ans;
    }
};

void Din() {
    int n;
    cin >> n;

    Trie t;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        t.insert(s);
    }

    int q;
    cin >> q;
    while (q--) {
        string pat;
        cin >> pat;
        cout << t.getAns(pat) << '\n';
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

https://www.spoj.com/problems/TRYCOMP/

*/