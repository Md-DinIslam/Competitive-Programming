/*
    author: Din_ED
    Time: 23:55:42
    Date: 21-10-2025
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

vector<vector<int>> g;
vector<int> parent, depth, tin, heavy, root;

class segTree {
    vector<int> sg, lz;
public:
    segTree (int n) : sg(4*n+1, 0), lz(4*n+1, -1) {};

    void Apply(int s, int e, int val, int i) {
        sg[i] = val * (e - s + 1);
        lz[i] = val;
    }

    void Push(int s, int mid, int e, int i) {
        if (lz[i] != -1) {
            Apply(s, mid, lz[i], 2*i);
            Apply(mid+1, e, lz[i], 2*i+1);
        }
        lz[i] = -1;
    }

    void upd(int lb, int rb, int val, int s, int e, int i = 1) {
        if (s > rb || e < lb) return;
        if (s >= lb && e <= rb) {
            Apply(s, e, val, i);
        }
        else {
            int mid = (s + e) / 2;
            Push(s, mid, e, i);
            upd(lb, rb, val, s, mid, 2*i);
            upd(lb, rb, val, mid+1, e, 2*i+1);
            sg[i] = sg[2*i] + sg[2*i+1];
        }
    }

    int qry(int lb, int rb, int s, int e, int i = 1) {
        if (s > rb || e < lb) return 0;
        if (s >= lb && e <= rb) return sg[i];
        int mid = (s + e) / 2;
        Push(s, mid, e, i);
        return qry(lb, rb, s, mid, 2 * i) + qry(lb, rb, mid+1, e, 2*i+1);
    }
};

void reset(int n) {
    g.assign(n+1, {});
    parent.assign(n+1, 0);
    depth.assign(n+1, 0);
    tin.assign(n+1, 0);
    heavy.assign(n+1, 0);
    root.assign(n+1, 0);
}

int dfs(int node, int par) {
    int subTree = 1, mxChildSize = 0;
    depth[node] = depth[par] + 1;
    parent[node] = par;

    for (auto &child : g[node]) {
        if (child ^ par) {
            int childSize = dfs(child, node);
            subTree += childSize;
            if (childSize > mxChildSize){
                mxChildSize = childSize;
                heavy[node] = child;
            }
        }
    }
    return subTree;
}

void dfs2(int node, int par) {
    depth[node] = depth[par] + 1;
    for (auto &child : g[node]) {
        if (child ^ par) {
            dfs2(child, node);
        }
    }
}

int timer = 1;
void decompose(int node, int par, int top) {
    root[node] = top;
    tin[node] = timer++;
    if (heavy[node]) {
        decompose(heavy[node], node, top);
    }
    for (auto &child : g[node]) {
        if (child != par && child != heavy[node]) {
            decompose(child, node, child);
        }
    }
}

void updateHLD(int a, int b, int val, int n, segTree &t) {
    while (root[a] != root[b]) {
        if (depth[root[a]] < depth[root[b]]) {
            swap(a, b);
        }
        t.upd(tin[root[a]], tin[a], val, 1, n);
        a = parent[root[a]];
    }

    if (depth[a] > depth[b]) {
        swap(a, b);
    }
    t.upd(tin[a], tin[b], val, 1, n);
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

    dfs2(1, 0);
    int mxNode = 0, mxDepth = 0;
    for (int i = 1; i <= n; ++i) {
        if (mxDepth < depth[i]) {
            mxNode = i, mxDepth = depth[i];
        }
        depth[i] = 0;
    }

    dfs2(mxNode, 0);

    mxNode = 0, mxDepth = 0;
    for (int i = 1; i <= n; ++i) {
        if (mxDepth < depth[i]) {
            mxNode = i, mxDepth = depth[i];
        }
        depth[i] = 0;
    }

    dfs(mxNode, 0);
    decompose(mxNode, 0, mxNode);

    segTree t(n);
    
    while (q--) {
        int a, b, x, y;
        cin >> a >> b >> x >> y;

        updateHLD(a, b, 1, n, t);
        updateHLD(x, y, 1, n, t);
        
        cout << t.qry(1, n, 1, n) << '\n';
        
        // De-update...
        updateHLD(a, b, 0, n, t);
        updateHLD(x, y, 0, n, t);
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

https://codeforces.com/gym/106059/problem/D

*/
