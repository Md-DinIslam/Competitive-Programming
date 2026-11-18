#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define all(x) x.begin(), x.end()
#define sz(x) int(x.size())
#define PI acos(-1.0)

template<class T> int sgn(T v) {
    return (v > 0) - (v < 0);
}

struct P {
    ll x, y;
    P operator+(P o) const {return {x+o.x, y+o.y};}
    P operator-(P o) const {return {x-o.x, y-o.y};}
    P operator*(ll k) const {return {x*k, y*k};}
    ll dot(P o) const { return x*o.x + y*o.y; }
    ll cross(P o) const {return x*o.y-y*o.x;}
    ll cross(P b, P c) const {
        return (b-*this).cross(c-*this);
    }
    ll n2() const {return x*x + y*y;}
    ld abs() const {return sqrtl(n2());}
    bool operator<(P o) const {return tie(x, y) < tie(o.x, o.y); }
    bool operator==(P o) const {return tie(x, y) == tie(o.x, o.y); }
};
istream& operator>>(istream &i, P &p) {
    return i >> p.x >> p.y;
}
ostream& operator<<(ostream &o, P p) {
    return o << p.x << " " << p.y;
}

bool onSeg (P a, P b, P p) {
    return a.cross(b, p) == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool segInter(P a, P b, P c, P d) {
    int d1 = sgn(a.cross(b, c)), d2 = sgn(a.cross(b, d));
    int d3 = sgn(c.cross(d, a)), d4 = sgn(c.cross(d, b));
    if (d1 * d2 < 0 && d3 * d4 < 0) return 1; // proper
    return onSeg(a, b, c) || onSeg(a, b, d) || onSeg(c, d, a) || onSeg(c, d, b); // touch/overlap
}

bool lineInter(P a, P b, P c, P d, ld &ix, ld &iy) {
    ll den = (b-a).cross(d-c);
    if (!den) return 0;
    ld t = (ld)(c-a).cross(d-c) / den;
    ix = a.x + t*(b-a).x;
    iy = a.y + t*(b-a).y;
    return 1;
}      

// 0 = outside, 1 = on boundary, 2 = inside (any simple polygon)
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