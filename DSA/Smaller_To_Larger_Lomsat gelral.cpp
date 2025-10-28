/*
    author: Din_ED
    Time: 20:23:02
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
vector<ll> v(mxN), ans(mxN), maxCnt(mxN), sum(mxN);

vector<vector<int>> g;
vector<unordered_map<ll, ll>> cnt(mxN);

int n, q;

void dfs(int node, int par) {
    cnt[node][v[node]] += 1;
    maxCnt[node] += 1;
    sum[node] += v[node];

    for (auto &child : g[node]) {
        if (child != par) {
            dfs(child, node);
            if (sz(cnt[node]) < sz(cnt[child])) {
                swap(cnt[node], cnt[child]);
                swap(sum[node], sum[child]);
                swap(maxCnt[node], maxCnt[child]);
            }

            for (auto &[val, freq] : cnt[child]) {
                cnt[node][val] += freq;
                if (cnt[node][val] > maxCnt[node]) {
                    maxCnt[node] = cnt[node][val];
                    sum[node] = val;
                }
                else if (cnt[node][val] == maxCnt[node]) {
                    sum[node] += val;
                }
            }

            cnt[child].clear();
        }
    }

    ans[node] = sum[node];
}

void Din() {
    cin >> n;

    for (int i = 1; i <= n; ++i) {
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
    
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " ";
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

https://codeforces.com/contest/600/problem/E

*/
