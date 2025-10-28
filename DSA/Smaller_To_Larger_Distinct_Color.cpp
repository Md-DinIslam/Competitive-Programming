/* GREEN UNIVERSITY OF BANGLADESH
    Md DinIslam, Batch-221 (CSE)
    Time: 23:43:34
    Date: 23-08-2025
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
vector<unordered_set<int>> subtree;
vector<int> v, ans;
 
// Small to Large merging technique...
 
void dfs(int node, int par) {
    subtree[node].insert(v[node]);
    for (auto &child : g[node]) {
        if (child != par) {
            dfs(child, node);
            if (subtree[node].size() < subtree[child].size()) {
                // for merging smaller to larger, for time saving O(N^2) to O(NlogN);
                swap(subtree[node], subtree[child]);
            }
 
            for (auto &x : subtree[child]) {
                subtree[node].insert(x);
            }
 
            // it's temporary to reduce memory space...
            subtree[child].clear();
        }
    }
 
    ans[node] = subtree[node].size();
}
 
void init(int n) {
    v.assign(n + 1, 0);
    ans.assign(n + 1, 0);
    subtree.resize(n + 1);
    g.resize(n + 1);
}
 
void Din() {
    int n;
    cin >> n;
 
    init(n);
 
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
        // subtree[i].insert(v[i]);
        // v[i] = i;
    }
 
    dg(1 << 18);
 
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
 
    // dg(g);
 
    dfs(1, 0);
 
    dg(subtree);
 
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " \n"[i == n];
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