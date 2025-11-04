/*
    author: Din_ED
    Time: 23:47:37
    Date: 04-11-2025
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

const int mxN = 5e5 + 1;

vector<vector<int>> g, cnt(mxN, vector<int> (27, 0));
vector<int> v, depth, tin, tout;

int n, q, timer;
string s;

struct Node {
    int lb, rb, block, ans, indx, dist;
    bool operator<(const Node &Q) const {
        if (block == Q.block) { // zig-zag
            return (block & 1 ? rb > Q.rb : rb < Q.rb);
        }
        return (block < Q.block);
    }
} query[mxN];

void dfs(int node, int par) {
    tin[node] = timer++;
    depth[node] = depth[par] + 1;
    for (auto &child : g[node]) {
        if (child != par) {
            dfs(child, node);
        }
    }
    tout[node] = timer;
}

void add(int x, int d) {
    cnt[d][x] += 1;
}

void remove(int x, int d) {
    cnt[d][x] -= 1;
}

void reset() {
    depth.assign(n+1, 0);
    tin.assign(n+1, 0);
    tout.assign(n+1, 0);
    g.assign(n+1, {});
    timer = 1;
}

void Din() {
    cin >> n >> q;

    reset();

    for (int i = 2; i <= n; ++i) {
        int x;
        cin >> x;
        g[x].push_back(i);
        g[i].push_back(x);
    }

    cin >> s;
    for (auto &x : s) {
        v.push_back(x - 'a' + 1);
    }
    
    dfs(1, 0);

    auto temp = v;
    auto temp_depth = depth;

    for (int i = 1; i <= n; ++i) {
        v[tin[i] - 1] = temp[i-1];
        depth[tin[i]] = temp_depth[i];
    }

    int len = (int) sqrtl(n) + 1;
    for (int i = 0; i < q; ++i) {
        int node, h;
        cin >> node >> h;
        int lb = tin[node], rb = tout[node] - 1;
        query[i].lb = lb - 1, query[i].rb = rb - 1;
        query[i].indx = i, query[i].block = query[i].lb / len;
        query[i].dist = h;
    }

    sort(query, query + q);
    
    int L = 0, R = 0;
    for (int i = 0; i < q; ++i) {
        while (R <= query[i].rb) {
            add(v[R], depth[R+1]);
            R += 1;
        }
        while (R > query[i].rb + 1) {
            R -= 1;
            remove(v[R], depth[R+1]);
        }
        while (L < query[i].lb) {
            remove(v[L], depth[L + 1]);
            L += 1;
        }
        while (L > query[i].lb) {
            L -= 1;
            add(v[L], depth[L + 1]);
        }

        int k = query[i].dist;
        int odd = 0;
        
        for (auto &x : cnt[k]) {
            odd += (x & 1);
        }

        if (odd <= 1) {
            query[query[i].indx].ans = 1;
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << (query[i].ans == 1 ? "Yes" : "No") << "\n";
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

https://codeforces.com/problemset/problem/570/D

*/