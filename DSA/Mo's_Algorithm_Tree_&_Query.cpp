/*
    author: Din_ED
    Time: 20:15:09
    Date: 28-10-2025
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

const int mxN = 1e5 + 10;
vector<int> v(mxN), bit(mxN), tin(mxN), tout(mxN), cnt(mxN);
vector<vector<int>> g;

int n, q;

void upd(int i, int val) {
    while (i > 0 && i <= n) {
        bit[i] += val;
        i += (i & -i);
    }
}

int qry(int i) {
    int ans = 0;
    while (i > 0 && i <= n) {
        ans += bit[i];
        i -= (i & -i);
    }
    return ans;
}

struct node {
    int lb, rb, block, ans, indx, lim;
    bool operator<(node Q) const {
        return (make_pair(this->block, rb) < make_pair(Q.block, Q.rb));
    }
} query[mxN];

bool cmp(node a, node b) {
    return a.indx < b.indx;
}

void add(int x) {
    upd(cnt[x], -1);
    cnt[x]++;
    upd(cnt[x], 1);
}

void remove(int x) {
    upd(cnt[x], -1);
    cnt[x]--;
    upd(cnt[x], 1);
}

int timer = 1;
void dfs(int node, int par) {
    tin[node] = timer++;
    for (auto &child : g[node]) {
        if (child != par) {
            dfs(child, node);
        }
    }
    tout[node] = timer;
}

void Din() {
    cin >> n >> q;
    int len = (int) sqrtl(n) + 1;
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    g.assign(n + 1, {});

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    dfs(1, 0);
    vector<int> temp(v.begin(), v.begin() + n);

    for (int i = 1; i <= n; ++i) {
        v[tin[i] - 1] = temp[i - 1];
        // cerr << tin[i] << " " << tout[i] << "\n";
        // cerr << temp[i] << " ";
    }

    for (int i = 0; i < q; ++i) {
        // cin >> query[i].lb >> query[i].rb;
        int node, limit;
        cin >> node >> limit;
        query[i].lb = tin[node], query[i].rb = tout[node] - 1;
        query[i].lb--, query[i].rb--;
        query[i].block = query[i].lb / len;
        query[i].indx = i;
        query[i].lim = limit;
    }

    sort(query, query + q);

    int x = 0, y = 0;
    for (int i = 0; i < q; ++i) {
        while (y <= query[i].rb) add(v[y++]);
        while (y > query[i].rb + 1) remove(v[--y]);
        while (x < query[i].lb) remove(v[x++]);
        while (x > query[i].lb) add(v[--x]);

        int limit = query[i].lim;

        if (limit <= n) {
            query[i].ans = qry(n) - qry(limit - 1);
        }
        else {
            query[i].ans = 0;
        }
        // query[i].ans = qry(n);
        // vis.clear();
    }
    sort(query, query + q, cmp);

    for (int i = 0; i < q; ++i) {
        cout << query[i].ans << '\n';
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

https://codeforces.com/contest/375/problem/D

*/