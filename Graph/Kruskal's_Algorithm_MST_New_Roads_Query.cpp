/* 
    author: Din_ED
    Time: 14:47:15
    Date: 02-11-2025
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

const int mxN = 1e5 + 1;
const int inf = 1e9;

vector<arr<int, 3>> g;
vector<vector<arr<int, 2>>> tree;
vector<int> depth;
vector<vector<int>> parent;
vector<vector<int>> ans;

int n, m, q, logN;

struct DSU {
    vector<int> ps;
    DSU(int n) : ps(n+1, -1) {};

    int Find(int x) {
        return ps[x] < 0 ? x : ps[x] = Find(ps[x]);
    }

    bool is_same(int a, int b) {
        return (Find(a) == Find(b));
    }

    bool Union(int a, int b) {
        a = Find(a), b = Find(b);
        if (a == b) return 0; // same parent...
        if (ps[a] > ps[b]) swap(a, b);
        ps[a] += ps[b];
        ps[b] = a;
        return 1;
    }
};

void dfs(int node, int par, int val) {
    depth[node] = depth[par] + 1;
    parent[node][0] = par;
    ans[node][0] = val;

    for (int i = 1; i < logN; ++i) {
        parent[node][i] = parent[parent[node][i-1]][i-1];
        ans[node][i] = max(ans[node][i-1], ans[parent[node][i-1]][i-1]);
    }

    for (auto &[wg, child] : tree[node]) {
        if (child ^ par) {
            dfs(child, node, wg);
        }
    }
}

int getAns(int a, int b) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }
    int max_a = 0;
    int diff = depth[a] - depth[b];
    for (int i = 0; i < logN; ++i) {
        if ((diff >> i) & 1) {
            max_a = max(max_a, ans[a][i]);
            a = parent[a][i];
        }
    }
    if (a == b) return max_a;
    for (int i = logN-1; i >= 0; --i) {
        if (parent[a][i] != parent[b][i]) {
            max_a = max({max_a, ans[a][i], ans[b][i]});
            a = parent[a][i], b = parent[b][i];
        }
    }
    return max({max_a, ans[a][0], ans[b][0]});
}

void reset() {
    logN = 32 - __builtin_clz(n);
    g.assign(m+1, {}); // size of edge..
    tree.assign(n+1, {});
    depth.assign(n+1, 0);
    parent.assign(n+1, vector<int>(logN, 0));
    ans.assign(n+1, vector<int>(logN, 0));

    // for (auto &x : g) {
    //     cerr << x[0] << '\n';
    // }
}

void Din() {
    cin >> n >> m >> q;

    reset();

    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        g[i] = {i, x, y};
        // cerr << sz(g[i]) << '\n';
    }

    // sort(all(g));

    DSU t(n);

    // ll sum = 0;
    for (int i = 1; i <= m; ++i) {
        int x = g[i][1];
        int y = g[i][2];
        int wg = g[i][0];

        // cerr << x << " " << y << " wg: " << wg << '\n';

        if (t.Union(x, y)){
            tree[x].push_back({wg, y});
            tree[y].push_back({wg, x});
            // sum += wg;
            // cerr << "ok";
        }
    }

    // for (int i = 1; i <= n; ++i) {
    //     cerr << i << " Child: ";
    //     for(auto &[wg, child] : tree[i]) {
    //         cerr << child << " ";
    //     }
    //     cerr << "\n";
    // }

    // cerr << sum << '\n';

    // for (int i = 1; i <= n; ++i) {
    //     cerr << sz(tree[i]) << " ";
    //     cerr << t.ps[i] << "\n";
    // }

    for (int i = 1; i <= n; ++i){
        if (depth[i] == 0) {
            dfs(i, 0, 0);
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        // cerr << a << " " << b << "\n";
        if(!t.is_same(a, b)) {
            cout <<"-1\n";
        }
        else {
            cout << getAns(a, b) << '\n';
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
