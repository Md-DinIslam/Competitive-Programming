/*
    author: Din_ED
    Time: 06:34:23
    Date: 18-11-2026
*/
 
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
 
#ifdef LOCAL
#include "debug.h"
#else
#define dbg(x...)
#endif
 
#define ll long long
#define ld double
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) int(x.size())
#define arr array
 
template<class T> int sgn(T v) {
    return (v > 0) - (v < 0);
}
 
struct P {
    ll x, y;
    P operator+(P o) const {return {x+o.x, y+o.y};}
    P operator-(P o) const {return {x-o.x, y-o.y};}
    P operator*(ll k) const {return {x*k, y*k};}
    ll dot(P o) const {return x*o.y+y*o.x;}
    ll cross(P o) const {return x*o.y-y*o.x;}
    ll cross(P b, P c) const {
        return (b-*this).cross(c-*this);
    }
    bool operator<(P o) const {return tie(x, y) < tie(o.x, o.y); }
    bool operator==(P o) const {return tie(x, y) == tie(o.x, o.y); }
};
 
bool onSeg (P a, P b, P p) {
    return a.cross(b, p) == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}
 
int inPoly(const vector<P> &p, P q) {
    int n = sz(p);
    bool in = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        P a = p[i], b = p[j];
        if (onSeg(a, b, q)) return 1;
        if ((a.y > q.y) != (b.y > q.y)) {
            ll c = a.cross(b, q);
            if (b.y > a.y ? c > 0 : c < 0) in = !in;
        }
    }
    return in ? 2 : 0;
}
 
istream& operator>>(istream &i, P &p) {
    return i >> p.x >> p.y;
}
ostream& operator<<(ostream &o, P p) {
    return o << p.x << " " << p.y;
}
 
void Din() {
    int n, q;
    cin >> n >> q;
 
    vector<P> p(n);
    for (auto &x : p) {
        cin >> x;
        // cerr << x.x << " " << x.y << "\n";
    }
 
    while (q--) {
        P x;
        cin >> x;
        int now = inPoly(p, x);
        if(now == 1) {
            cout << "BOUNDARY\n";
        }
        else if (now == 0) {
            cout << "OUTSIDE\n";
        }
        else {
            cout << "INSIDE\n";
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