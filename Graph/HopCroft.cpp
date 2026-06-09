/*
    author: Din_ED
    Time: 01:51:30
    Date: 10-06-2026
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

vector<vector<int>> g;
vector<int> a, b;
vector<ll> dist;

int n, m;

const ll inf = 1e18;

void reset() {
    g.assign(n+1, {});
    a.assign(n+1, 0);
    b.assign(n+1, 0);
    dist.assign(n+1, 0);
}

bool bfs() {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (!a[i]) {
            dist[i] = 0;
            q.push(i);
        }
        else {
            dist[i] = inf;
        }
    }

    bool ok = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (auto &child : g[node]) {
            if (b[child] == 0) ok = 1;
            else if (dist[b[child]] == inf) {
                dist[b[child]] = dist[node] + 1;
                q.push(b[child]);
            }
        }
    }

    return ok;
}

bool dfs(int node) {
    for (auto &child : g[node]) {
        int v = b[child];
        if (v == 0 || (dist[v] == dist[node] + 1 && dfs(v))) {
            a[node] = child;
            b[child] = node;
            return 1;
        }
    }

    dist[node] = inf;
    return 0;
}

int HopCronft() {
    int ans = 0;

    while (bfs()) {
        for (int i = 1; i <= n; ++i) {
            if (!a[i] && dfs(i)) {
                ans += 1;
            }
        }
    }

    return ans;
}

void Din() {
    // int n, m;
    cin >> n >> m;

    reset();

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    // for (int i = 1; i <= n; ++i) {
    //     for (auto &x : g[i]) {
    //         cerr << x << " ";
    //     } cerr << "\n";
    // }

    int max_match = HopCronft();
    ll ans = 1ll * (2 * n - max_match) * 1013;

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


/*

https://atcoder.jp/contests/abc461/tasks/abc461_g

*/
