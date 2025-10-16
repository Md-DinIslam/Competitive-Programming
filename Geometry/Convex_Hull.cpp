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
    void read() { cin >> x >> y; }
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
        return (b - *this) * (c - *this);
    }
    // Check P1 is inside between a and b or not...
    bool isInside (const Point &a, const Point &b) const {
        return (a.x <= x && x <= b.x && a.y <= y && y <= b.y);
    }
    bool operator<(const Point &a) const {
        return make_pair(x, y) < make_pair(a.x, a.y);
    }
    friend istream& operator>>(istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
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
        // x.read();
        cin >> x;
    }
    sort(all(p));
    vector<Point> hull;
    for (int rep = 0; rep < 2; ++rep) {
        const int m = hull.size();
        for (auto &c : p) {
            while ((int) hull.size() - m > 1) {
                Point a = hull.end()[-2];
                Point b = hull.end()[-1];

                int sign = getOrientation(a.crossProduct(b, c));
                if (sign <= 0) break; // good, or collinear
                hull.pop_back(); // remove b
            }
            hull.push_back(c);
        }
        hull.pop_back(); // end point count twice, so remove
        reverse(all(p)); // calculate for down part
    }

    cout << hull.size() << "\n";
    for (auto &x : hull) {
        cout << x << "\n";
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

problem: https://codeforces.com/gym/106084/problem/L

*/