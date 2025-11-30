/* GREEN UNIVERSITY OF BANGLADESH
    Md DinIslam, Batch-221 (CSE)
*/
#include <bits/stdc++.h>
using namespace std;

// Debug..
#ifdef LOCAL
#include "debug.h"
#else
#define dg(x...)
#endif

#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) int(x.size())
#define arr array
#define ll long long
#define ull uint64_t

struct Hash {
    ull x;
    Hash(ull x = 0) : x(x) {};

    Hash operator+(Hash op) {
        return x + op.x + (x + op.x < x);
    }

    Hash operator-(Hash op) {
        return *this + ~op.x;
    }

    Hash operator*(Hash op) {
        auto m = (__uint128_t) x * op.x;
        return Hash((ull) m) + (ull) (m >> 64);
    }

    ull get() const {
        return x + !~x;
    }

    bool operator==(Hash op) {
        return get() == op.get();
    }

    friend ostream& operator<<(ostream& out, Hash &op) {
        return out << op.x;
    }
};

static const Hash prime = (ll) 1e11 + 3;

class hashInterval {
    vector<Hash> pw, hsh, sg;
    int n;
public:
    hashInterval(string &s) {
        this->n = sz(s);
        hsh.resize(n + 1); pw = hsh;
        sg.resize(4 * n + 1);
        // dg(n);
        pw[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pw[i] = pw[i - 1] * prime;
            // cout << pw[i] << " ";
        }
        for (int i = 1; i <= n; ++i) {
            upd(i, s[i - 1]);
        }
    }

    void upd(int indx, char val, int s, int e, int i = 1) {
        if (s == e) sg[i] = val;
        else {
            int mid = (s + e) / 2;
            if (indx <= mid)
                upd(indx, val, s, mid, 2 * i);
            else
                upd(indx, val, mid + 1, e, 2 * i + 1);
            sg[i] = sg[2 * i] * pw[e - mid] + sg[2 * i + 1];
        }
    }

    void upd(int indx, char val) {
        upd(indx, val, 1, n);
    }

    pair<Hash, int> qry(int lb, int rb, int s, int e, int i = 1) {
        if (s > rb || e < lb) return {0, 0};
        if (s >= lb && e <= rb) return {sg[i], e - s + 1};
        int mid = (s + e) / 2;
        auto a = qry(lb, rb, s, mid, 2 * i);
        auto b = qry(lb, rb, mid + 1, e, 2 * i + 1);
        int k = b.second;
        Hash ans = a.first * pw[k] + b.first;
        int len = a.second + b.second;
        return {ans, len};
    }

    Hash qry(int a, int b) {
        // Hash test = qry(a, b, 1, n).first;
        // cout << test << "\n";
        return qry(a, b, 1, n).first;
    }
};

void Din() {
    string s;
    cin >> s;
    int n = sz(s);

    hashInterval prefix(s);
    reverse(all(s));
    hashInterval suffix(s);

    int q;
    cin >> q;
    while (q--) {
        string tp;
        cin >> tp;
        if (tp[0] == 'p') {
            int lb, rb;
            cin >> lb >> rb;
            bool same = prefix.qry(lb, rb) == suffix.qry(n - rb + 1, n - lb + 1);

            if (same)
                cout << "Yes\n";
            else
                cout << "No\n";
        }
        else {
            int indx;
            char ch;
            cin >> indx >> ch;
            prefix.upd(indx, ch);
            suffix.upd(n - indx + 1, ch);
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
