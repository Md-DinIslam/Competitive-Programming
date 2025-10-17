/*
    author: Din_ED
    Time: 03:13:46
    Date: 18-10-2025
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

vector<int> v;

struct Node {
    ll sum;
    vector<ll> freq;
    Node() : sum(0), freq(10, 0) {}
};

class lazySegTree {
    vector<Node> sg;
    vector<ll> lz;
public:
    lazySegTree(int n) : sg(4 * n + 1), lz(4 * n + 1) {};

    void build(int s, int e, int i = 1) {
        if (s == e) {
            sg[i].sum = v[s];
            sg[i].freq[v[s]] = 1;
            return;
        }
        int mid = (s + e) / 2;
        build(s, mid, 2 * i);
        build(mid + 1, e, 2 * i + 1);
        sg[i] = merge(sg[2 * i], sg[2 * i + 1]);
    }

    Node merge(Node a, Node b) {
        Node ans;
        ans.sum = a.sum + b.sum;
        for (int i = 0; i <= 9; ++i) {
            ans.freq[i] = a.freq[i] + b.freq[i];
        }
        return ans;
    }

    void Apply(int s, int e, ll val, int i) {
        val %= 10;
        Node ans;
        vector<ll> cnt = sg[i].freq;
        // shifting count.. easy man...
        for (int i = 0; i <= 9; ++i) {
            int digit = (i + val) % 10;
            ans.freq[digit] += cnt[i];
            ans.sum += digit * cnt[i];
        }
        sg[i] = ans;
        lz[i] += val;
    }

    void Push(int s, int mid, int e, int i) {
        if (lz[i]) {
            Apply(s, mid, lz[i], 2 * i);
            Apply(mid + 1, e, lz[i], 2 * i + 1);
        }
        lz[i] = 0;
    }

    void upd(int lb, int rb, ll val, int s, int e, int i = 1) {
        if (s > rb || e < lb) return;
        if (s >= lb && e <= rb) {
            Apply(s, e, val, i);
            return;
        }
        int mid = (s + e) / 2;
        Push(s, mid, e, i);
        upd(lb, rb, val, s, mid, 2 * i);
        upd(lb, rb, val, mid + 1, e, 2 * i + 1);
        sg[i] = merge(sg[2 * i], sg[2 * i + 1]);
    }

    Node qry(int lb, int rb, int s, int e, int i = 1) {
        if (s > rb || e < lb) {
            Node temp;
            temp.sum = 0;
            return temp;
        }
        if (s >= lb && e <= rb) return sg[i];
        int mid = (s + e) / 2;
        Push(s, mid, e, i);
        return merge(qry(lb, rb, s, mid, 2 * i), qry(lb, rb, mid + 1, e, 2 * i + 1));
    }

    void test(int n) {
        for (int i = 1; i <= n; ++i) {
            Node ans = qry(i, i, 1, n);
            cout << ans.sum << "\n";
        }
        cout << "\n";
    }
};

void Din() {
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    v.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int x = s[i - 1] - '0';
        v[i] = x;
    }

    lazySegTree t(n);
    t.build(1, n);

    while (q--) {
        int lb, rb;
        cin >> lb >> rb;

        Node ans = t.qry(lb, rb, 1, n);
        cout << ans.sum << "\n";

        // cout << ans.sum << " ?\n\n";
        t.upd(lb, rb, 1ll, 1, n);
        
        // t.test(n);
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
