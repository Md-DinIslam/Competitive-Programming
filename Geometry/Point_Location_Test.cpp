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

    // friend istream& operator>>(istream &is, Point &p) {
    //     return is >> p.x >> p.y;
    // }

    // friend ostream& operator<<(ostream &os, const Point &p) {
    //     os << p.x << " " << p.y;
    //     return os;
    // }
};

void Din() {
    Point p, p2, p3;
    // vector<Point> p(3);
    // for (auto &x : p) {
    //     x.read();
    // }
    p.read();
    p2.read();
    p3.read();

    p2 -= p; // A vector, p2 - p
    p3 -= p; // B vector, p3 - p,

    // then A * B [cross product]

    ll cross_product = p2 * p3; // in vector direction matter, p2 * p3

    if (cross_product < 0) {
        // P3 is left from P2 point, so right from P1
        cout << "RIGHT\n";
    }
    else if (cross_product > 0) {
        cout << "LEFT\n";
    }
    else {
        cout << "TOUCH\n";
    }
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
