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
    };
    vector<Node> t;

    Trie() {
        t.emplace_back();
        memset(t[0].nxt, -1, sizeof(t[0].nxt));
    }

    int newNode() {
        t.emplace_back();
        memset(t.back().nxt, -1, sizeof(t.back().nxt));
        return (int)t.size() - 1;
    }

    void insert(const string &s) {
        int cur = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (t[cur].nxt[ch] == -1) t[cur].nxt[ch] = newNode();
            cur = t[cur].nxt[ch];
            t[cur].cntPrefix++;
        }
        t[cur].cntEnd++;
    }

    // single traversal, no wasted re-scan
    void erase(const string &s) {
        int cur = 0;
        vector<int> path = {0};
        for (char c : s) {
            int ch = c - 'a';
            if (t[cur].nxt[ch] == -1) return; // word doesn't exist
            cur = t[cur].nxt[ch];
            path.push_back(cur);
        }
        if (t[cur].cntEnd == 0) return; // not actually an end
        t[cur].cntEnd--;
        for (int i = 1; i < (int)path.size(); i++) t[path[i]].cntPrefix--;
    }

    int countEqual(const string &s) {
        int cur = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (t[cur].nxt[ch] == -1) return 0;
            cur = t[cur].nxt[ch];
        }
        return t[cur].cntEnd;
    }

    int countPrefix(const string &s) {
        int cur = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (t[cur].nxt[ch] == -1) return 0;
            cur = t[cur].nxt[ch];
        }
        return t[cur].cntPrefix;
    }

    bool startsWith(const string &s) {
        int cur = 0;
        for (char c : s) {
            int ch = c - 'a';
            if (t[cur].nxt[ch] == -1) return false;
            cur = t[cur].nxt[ch];
        }
        return true;
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
        if (t.startsWith(pat)) {
            dg(t.countPrefix(pat));
            cout << pat << "\n";
        }
        else {
            cout << "-1\n";
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
