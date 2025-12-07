/*
    author: Din_ED
    Time: 01:20:38
    Date: 01-12-2025
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
#define ull uint64_t

const int mxN = 2e6 + 1;

struct Hash {
    ull x;
    Hash (ull _x = 0) : x(_x) {}
    Hash operator+(Hash o) {
        return x + o.x + (x + o.x < x);
    }
    Hash operator-(Hash o) {
        return *this + ~o.x;
    }
    Hash operator*(Hash o) {
        auto m = (__uint128_t) x * o.x;
        return Hash((ull)m) + (ull) (m >> 64);
    }
    ull get() const {
        return x + !~x;
    }
    bool operator==(Hash o) {
        return get() == o.get();
    }
    bool operator!=(Hash o) {
        return get() != o.get();
    }
    bool operator<(Hash o) {
        return get() < o.get();
    }
};

static const Hash prime = (ll) 1e11 + 3;

struct hashInterval {
    vector<Hash> pw;
    Hash hsh;

    hashInterval(string &s, int n) : hsh(0), pw(mxN) {
        pw[0] = 1;
        for (int i = 1; i < mxN; ++i) {
            pw[i] = pw[i-1] * prime;
        }

        for (int i = 0; i < n; ++i) {
            hsh = hsh * prime + s[i];
        }
    }

    Hash qry() {
        return hsh;
    }

    void addFront(char ch, int len) {
        hsh = Hash(ch) * pw[len] + hsh;
    }

    void addBack(char ch) {
        hsh = hsh * prime + ch;
    }
};

void Din() {
    string s;
    cin >> s;

    int n = sz(s);

    hashInterval prefix(s, n);
    reverse(all(s));
    hashInterval suffix(s, n);

    // if (prefix.qry() == suffix.qry()) {
    //     cerr << "fine\n";
    // }

    int q;
    cin >> q;
    
    int len = n;

    while (q--) {
        char pos, ch;
        int rep;
        cin >> pos >> ch >> rep;

        for (int i = 0; i < rep; ++i) {
            if (pos == 'L') {
                prefix.addFront(ch, len + i);
                suffix.addBack(ch);
            }
            else {
                prefix.addBack(ch);
                suffix.addFront(ch, len + i);
            }
        }

        len += rep;

        if (prefix.qry() == suffix.qry()) {
            cout << "Yes\n";
        }
        else {
            cout << "No\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case " << i << ":\n";
        Din();
    }
    return 0;
}
