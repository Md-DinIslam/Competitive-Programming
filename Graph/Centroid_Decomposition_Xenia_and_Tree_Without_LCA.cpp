/* GREEN UNIVERSITY OF BANGLADESH
    Md DinIslam, Batch-221 (CSE)
    Time: 18:12:59
    Date: 09-09-2025
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
vector<int> subtree, distRED;
vector<bool> vis;
vector<vector<arr<int, 2>>> ancestors;

void reset(int n) {
    g.assign(n + 1, {});
    subtree.assign(n + 1, 0);
    distRED.assign(n + 1, 2e9); // fill with inf
    vis.assign(n + 1, 0);
    ancestors.assign(n + 1, {});
}

void dfs(int node, int par) {
    subtree[node] = 1;
    for (auto &child : g[node]) {
        if (child != par && !vis[child]) {
            dfs(child, node);
            subtree[node] += subtree[child];
        }
    }
}

int getCentroid(int node, int par, int new_subtree) {
    int centroid = node;
    for (auto &child : g[node]) {
        if (child != par && !vis[child] && (subtree[child] * 2 > new_subtree)) {
            // alternative...
            // centroid = getCentroid(child, node, new_subtree);
            return getCentroid(child, node, new_subtree);
        }
    }
    return centroid;
}

void getDist(int node, int par, int centroid, int curr_dist) {
    ancestors[node].push_back({centroid, curr_dist});
    for (auto &child : g[node]) {
        if (child != par && !vis[child]) {
            getDist(child, node, centroid, curr_dist + 1);
        }
    }
}

void buildCentroid(int node, int par) {
    dfs(node, 0);
    int centroid = getCentroid(node, par, subtree[node]);
    vis[centroid] = 1;

    for (auto &child : g[centroid]) {
        if (!vis[child]) {
            getDist(child, centroid, centroid, 1);
        }
    }

    for (auto &child : g[centroid]) {
        if (!vis[child]) {
            buildCentroid(child, centroid);
        }
    }

}

void upd(int node) {
    distRED[node] = 0;
    for (auto &[child, child_dist] : ancestors[node]) {
        distRED[child] = min(distRED[child], child_dist);
    }
}

int qry(int node) {
    int ans = distRED[node];
    for (auto &[child, curr_dist] : ancestors[node]) {
        ans = min(ans, distRED[child] + curr_dist);
    }
    return ans;
}

void Din() {
    int n, q;
    cin >> n >> q;

    reset(n);

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    // dg(g);

    buildCentroid(1, 0);

    // dg(ancestors);

    upd(1);

    while (q--) {
        int tp, node;
        cin >> tp >> node;

        if (tp == 1) {
            upd(node);
        }
        else {
            cout << qry(node) << '\n';
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
