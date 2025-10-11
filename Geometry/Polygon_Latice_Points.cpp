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

    void set(int x, int y) {
        this->x = x;
        this->y = y;
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

    ll crossProduct(const Point &b, const Point &c) const {
        // *this = p1,p1 to b and p1 to c cross product
        return (b - *this) * (c - *this);
    }
    // Check P1 is inside between a and b or not...
    bool isInside (const Point &a, const Point &b) const {
        ll x0 = this->x, y0 = this->y;
        return (a.x <= x0 && x0 <= b.x && a.y <= y0 && y0 <= b.y);
    }
    // Checking on segment..
    bool onSegment(Point a, Point b) {
        if (this->crossProduct(a, b)) { // parallel checking..
            return 0; // no co-linear
        }
        if (a.x > b.x) swap(a.x, b.x);
        if (a.y > b.y) swap(a.y, b.y);
        ll x0 = this->x, y0 = this->y;
        return (a.x <= x0 && x0 <= b.x && a.y <= y0 && y0 <= b.y);
    }
    // friend istream& operator>>(istream &is, Point &p) {
    //     return is >> p.x >> p.y;
    // }

    friend ostream& operator<<(ostream &os, const Point &p) {
        os << p.x << " " << p.y;
        return os;
    }
};

inline int getOrientation(ll x) {
    return ((x > 0) - (x < 0));
}

bool isInstersect(Point p1, Point p2, Point p3, Point p4) {
    // First check Co-linear..
    if ((p2 - p1) * (p4 - p3) == 0) {
        if (p1.crossProduct(p2, p3)) {
            return 0; // No Intersection..
        }
        // Check Box-Overlapping..
        for (int rep = 0; rep < 2; ++rep) {
            if ((max(p1.x, p2.x) < min(p3.x, p4.x)) || (max(p1.y, p2.y) < min(p3.y, p4.y))) {
                return 0; // No Intersection..
            }
            swap(p1, p3);
            swap(p2, p4);
        }
        return 1;
    }

    // now check side using sign..
    for (int rep = 0; rep < 2; ++rep) {
        int sign = getOrientation(p1.crossProduct(p2, p3));
        int sign2 = getOrientation(p1.crossProduct(p2, p4));

        if ((sign > 0 && sign2 > 0) || (sign < 0 && sign2 < 0)) {
            return 0; // No Intersection..
        }

        swap(p1, p3);
        swap(p2, p4);
    }
    return 1; // Intersection..
}

void Din() {
    int n;
    cin >> n;

    vector<Point> p(n);
    for (auto &x : p) {
        x.read();
    }

    // ----> Pick's Theorem <----
    // area = interior + boundary / 2 - 1;
    // interior = area - boundary / 2 + 1;
    // 2 * interior = 2 * area - boundary + 2 ;

    ll ans_inside = 0, area = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += p[i] * p[j];
    }

    area = abs(area); // twicw of area.. 2*area

    ll ans_boundary = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        Point diff = p[j] - p[i];
        ll gcd = __gcd(abs(diff.x), abs(diff.y));
        ans_boundary += gcd;
    }

    // divide by 2, because of twice of area..
    ans_inside = (area - ans_boundary + 2) / 2; 
    
    cout << ans_inside << " " << ans_boundary << '\n';
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
