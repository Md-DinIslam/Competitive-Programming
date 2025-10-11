/*
    author: Din_ED
    Time: 15:31:11
    Date: 10-10-2025
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

const int mxN = 1e6 + 1;
vector<int> spf(mxN), prime(1, 2);
vector<ll> v(mxN);

void preCal() {
    iota(all(spf), 0);
    spf[1] = 0;
    for (int i = 2; i * i < mxN; ++i) {
        if (spf[i] == i) {
            for (int j = i * i; j < mxN; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }

    for (int i = 3; i < mxN; i += 2) {
        if (spf[i] == i) {
            prime.push_back(i);
        }
    }

    // dg(spf[5], spf[49], prime.size());
}

ll add_mod(ll a, ll b, ll mod) {
    return ((a += b) >= mod ? a - mod : a);
}

ll mul_mod(ll a, ll b, ll mod) {
    ll ans = ((__int128) a * b) % mod;
    return ans;
}

ll binExp(ll a, ll b, ll mod) {
    ll ans = 1;
    while (b) {
        if (b & 1)
            ans = mul_mod(ans, a, mod);
        a = mul_mod(a, a, mod);
        b >>= 1;
    }
    return ans % mod;
}

bool miller(ll n) {
    if (n <= 2 || (n % 2 == 0)) return (n == 2);
    if (n < mxN) return spf[n] == n;

    ll d = n - 1;
    while (d % 2 == 0) {
        d >>= 1;
    }

    for (int i = 0; i < 30; ++i) {
        ll x = prime[i];
        if (x >= n) return 1;

        ll curr_d = d;
        ll mod = binExp(x, curr_d, n);

        if (mod != 1) {
            while (curr_d != n - 1 && mod != n - 1) {
                mod = mul_mod(mod, mod, n);
                curr_d *= 2;
            }

            if (mod != n - 1) return 0;
        }
    }

    return 1;
}

ll pollardRho(ll n) {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    while (1) {
        ll x = rnd() % n, y = x, c = rnd() % n;
        ll g = 1, prev_g, i = 0;
        while (1) { // hare and tortois technique...
            x = mul_mod(x, x, n); x = add_mod(x, c, n);
            // updating y twice...
            y = mul_mod(y, y, n); y = add_mod(y, c, n);
            y = mul_mod(y, y, n); y = add_mod(y, c, n);

            if (x == y) break;

            prev_g = g;
            g = mul_mod(g, abs(x - y), n);

            if (!g) return __gcd(prev_g, n); // factor found...

            if (++i == 32) {
                i = 0;
                g = __gcd(g, n);
                if (g > 1 && g < n) return g;
            }
        }
        if (i) {
            g = __gcd(g, n);
            if (g > 1 && g < n) return g;
        }
    }
}

vector<ll> factorize(ll n) {
    if (n == 1) return {};
    if (miller(n)) return {n};

    vector<ll> ans, add;
    while (n > 1 && n < mxN) {
        ans.push_back(spf[n]);
        n /= spf[n];
    }

    if (n >= mxN) {
        ll x = pollardRho(n);
        ans = factorize(x);
        add = factorize(n / x);
        for (auto &x : add) { // ans.insert(ans.end(), all(add));
            ans.push_back(x);
        }
    }

    return ans;
}

void Din() {
    ll n;
    cin >> n;

    // dg(miller(n), n);

    auto ans = factorize(n);
    sort(all(ans));

    cout << ans.size() << " ";
    for (auto &x : ans) {
        cout << x << " ";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    cin >> t;
    preCal();
    for (int i = 1; i <= t; ++i) {
        // cout << "Case " << i << ": ";
        Din();
    }
    return 0;
}
