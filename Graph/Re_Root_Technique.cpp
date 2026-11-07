/*
    author: Din_ED
    Time: 22:19:54
    Date: 07-11-2026
*/

#include <bits/stdc++.h>
#include <cassert>
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

const ll inf = 1e15;

int m, n;
vector<ll> c, p, dp, suffix, subtree, alone;
vector<int> ord;
vector<vector<int>> g;

void reset () {
    c.assign(m+1, 0);
    p.assign(m+1, 0);
    suffix.assign(m+2, inf);
    ord.assign(m+1, 0);
    iota(all(ord), 0);

    dp.assign(n+1, inf);
    alone.assign(n+1, 0);
    subtree.assign(n+1, 0);
    g.assign(n+1, {});
}

ll getCost (int x) {
    int idx = lower_bound(all(c), x) - c.begin();
    return suffix[idx];
}

void upd (int node, int isRoot) {
    int cnt = sz(g[node]) - !isRoot;
    dp[node] = inf;
    if (cnt <= c.back()) {
        dp[node] = min(dp[node], getCost(cnt) + alone[node]);
    }
    if (subtree[node] <= c.back()) {
        dp[node] = min(dp[node], getCost(subtree[node]));
    }
}

void dfs (int node, int par) {
    subtree[node] = 1;
    for (auto &child : g[node]) {
        if (child != par) {
            dfs(child, node);
            subtree[node] += subtree[child];
            alone[node] += dp[child];
            // dbg(node, child, subtree[node], subtree[child]);
        }
    }

    upd (node, par == 0);

    // dbg(node, subtree[node], dp[node]);
}

void dfs2(int node, int par, ll &ans) {
    ans = min(ans, dp[node]);
    for (auto &child : g[node]) { // node -> child, new root child.
        if (child != par) {
            ll dchild = dp[child], dnode = dp[node];
            ll achild = alone[child], anode = alone[node];
            ll schild = subtree[child], snode = subtree[node];

            subtree[node] -= subtree[child];
            subtree[child] += subtree[node];

            alone[node] -= dp[child];
            upd(node, 0); // update dp[node]

            alone[child] += dp[node]; // after update dp[node], add it
            upd(child, 1);

            dfs2(child, node, ans);

            // reset
            dp[child] = dchild, dp[node] = dnode;
            alone[child] = achild, alone[node] = anode;
            subtree[child] = schild, subtree[node] = snode;
        }
    }
}

void Din() {
    cin >> m >> n;

    reset();

    for (int i = 1; i <= m; ++i) cin >> c[i];
    for (int i = 1; i <= m; ++i) cin >> p[i];

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    auto cmp = [&] (int i, int j) -> bool {
        if (c[i] < c[j]) return 1;
        if (c[i] == c[j] && p[i] < p[j]) return 1;
        return 0;
    };

    sort(all(ord), cmp);
    // dbg(ord);

    for (int i = m; i >= 1; --i) {
        suffix[i] = min(p[ord[i]], suffix[i+1]);
    }

    p = c;
    for (int i = 1; i <= m; ++i) {
        c[i] = p[ord[i]];
    }

    // dbg(suffix);
    // dbg(c);

    dfs(1, 0);

    // dbg(subtree);
    // dbg(alone);
    // dbg(dp);

    ll ans = inf;

    dfs2(1, 0, ans);

    if (ans >= inf) ans = -1;
    cout << ans << "\n";
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


// https://codeforces.com/gym/106810/problem/G