/*
    author: Din_ED
    Time: 23:39:58
    Date: 27-09-2025
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

struct Point {
    ll x, y;
    void read() {
        cin >> x >> y;
    }

    Point operator -(const Point &p) const {
        return Point{x - p.x, y - p.y};
    }

    ll operator *(const Point &p) const {
        return x * p.y - y * p.x;
    }

    ll triangle(const Point &b, const Point &c) const {
        // *this = p1, assuming that p1 will be (0, 0) point, so reducting b and c point, then cross product...
        return (b - *this) * (c - *this);
    }

    bool isInside (const Point &a, const Point &b) const {
        ll x = this->x, y = this->y;
        return (a.x <= x && x <= b.x && a.y <= y && y <= b.y);
    }
    // friend istream& operator>>(istream &is, Point &p) {
    //     return is >> p.x >> p.y;
    // }

    // friend ostream& operator<<(ostream &os, const Point &p) {
    //     os << p.x << " " << p.y;
    //     return os;
    // }
};

inline int getSign(ll x) {
    return ((x > 0) - (x < 0));
}

void Din() {
    int n;
    cin >> n;

    vector<Point> p(n);
    for (auto &x : p) {
        x.read();
    }

    ll area = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += p[i] * p[j];
    }

    area = abs(area); // it gives twice of polygon area, divide by two is actual area, but problem said to print 2*area.
    cout << area << '\n';
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
