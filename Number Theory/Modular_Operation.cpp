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

#define ll long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) int(x.size())
#define arr array

template<ll MOD>
struct Mint {
    ll a;
    Mint(ll _a = 0) : a((_a % MOD + MOD) % MOD) {}
    
    Mint binExp(ll b) const {
        Mint res = 1, a = a;
        for (; b; b >>= 1, a *= a) if (b & 1) res *= a;
        return res;
    }
    
    Mint inv() const { return binExp(MOD - 2); }
    
    Mint operator-() const { return Mint(-a); }
    Mint operator+(Mint o) const { return a + o.a; }
    Mint operator-(Mint o) const { return a - o.a + MOD; }
    Mint operator*(Mint o) const { return a * o.a; }
    Mint operator/(Mint o) const { return a * o.inv().a; }
    
    Mint& operator+=(Mint o) { return *this = *this + o; }
    Mint& operator-=(Mint o) { return *this = *this - o; }
    Mint& operator*=(Mint o) { return *this = *this * o; }
    Mint& operator/=(Mint o) { return *this = *this / o; }
    
    bool operator==(Mint o) const { return a == o.a; }
    bool operator!=(Mint o) const { return a != o.a; }
    
    friend ostream& operator<<(ostream& os, Mint m) { 
        return os << m.a; 
    }
    friend istream& operator>>(istream& is, Mint& m) { 
        ll x; is >> x; m = Mint(x); return is; 
    }
};

const int mod = 11; // can any prime like 1e9 + 9....

using mint = Mint <mod>;

void Din() {
    int a = 10, b = 3;
    // cin >> a >> b;

    // mint x = a, y = b; // x = mint(a), y = mint(b)....
    mint x, y;
    cin >> x >> y;
    
    cout << x << " " << y << "\n"; // inital value of x % mod....
    cout << x.binExp(y.a) << '\n'; // like (a ^ b)....
    cout << x.inv() << '\n'; // like (1/x)...
    cout << x.inv() * y << '\n'; // like (1/x * y)....
    cout << x * y << "\n";
    cout << x / y << '\n';
    cout << ((x == y) ? "Equal" : "Not Equal") << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i) { // Kickstart
        // cout << "Case " << i << ": ";
        Din();
    }
    return 0;
}
