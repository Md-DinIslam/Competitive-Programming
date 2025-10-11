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

    void operator -=(const Point &p) {
        x -= p.x;
        y -= p.y;
    }

    ll operator *(const Point &p) const {
        return x * p.y - y * p.x;
    }

    ll triangle(const Point &b, const Point &c) const {
        // *this = p1,p1 to b and p1 to c cross product
        return (b - *this) * (c - *this);
    }
    // Call like --> Point::isBoxOverlap(p[0], p[1], p[2], p[3])
    static bool isBoxOverlap(Point &p1, Point &p2, Point &p3, Point &p4) {
        for (int rep = 0; rep < 2; ++rep) {
            if ((max(p1.x, p2.x) < min(p3.x, p4.x)) || (max(p1.y, p2.y) < min(p3.y, p4.y))) {
                return 0;
            }
            swap(p1, p3);
            swap(p2, p4);
        }
        return 1;
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
    vector<Point> p(4);
    for (auto &x : p) {
        x.read();
    }

    // At first, Co-linearity Check...
    if ((p[1] - p[0]) * (p[3] - p[2]) == 0) {
        // p1 to p2, p3 to p4, if their cross product is 0, then check for co-linearity...
        // if ((p[1] - p[0]) * (p[2] - p[0]) != 0) {
        if (p[0].triangle(p[1], p[2])) {
            cout << "NO\n";
            return;
        }

        // Check if two bounding box intersect...
        if (!Point::isBoxOverlap(p[0], p[1], p[2], p[3])) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
        }
        return;
    }

    // Check 1st segment to 2nd segment 1st poin and 2nd point.. and similar to 2nd segment to 1st segment.. [orientation check]
    for (int rep = 0; rep < 2; ++rep) {
        int sign = getSign(p[0].triangle(p[1], p[2]));
        int sign2 = getSign(p[0].triangle(p[1], p[3]));

        if ((sign < 0 && sign2 < 0) || (sign > 0 && sign2 > 0)) {
            cout << "NO\n";
            return;
        }

        swap(p[0], p[2]);
        swap(p[1], p[3]);
    }

    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        // cout << "Case " << i << ": ";
        Din();
    }
    return 0;
}
