/* GREEN UNIVERSITY OF BANGLADESH
    Md DinIslam, Batch-221 (CSE)
    Time: 03:14:03
    Date: 25-08-2025
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
#define vvl vector<vector<ll>>

const int mod = 1e9 + 7;

vvl matExp(vvl &a, vvl &b, int n) {
    vvl ans(n, vector<ll> (n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int via = 0; via < n; ++via) {
                ans[i][j] += ((a[i][via] * b[via][j]) % mod);
                ans[i][j] %= mod;
            }
        }
    }
    return ans;
}

void Din() {
    int n;
    ll k;
    cin >> n >> k;

    vector<ll> a(n), c(n);
    for (auto &x : a)
        cin >> x;
    for (auto &x : c)
        cin >> x;

    ll p, q, r;
    cin >> p >> q >> r;

    if (k < n) {
        cout << a[k] << '\n';
    }
    else {
        // equation after express
        // (a1...an) + (p+q+r) + (q+2r) + r

        vvl mat(n + 3, vector<ll> (n + 3, 0));
        vvl ans = mat; // identity matrix..

        for (int i = 0; i < n + 3; ++i) {
            ans[i][i] = 1;
        }

        // for non-homogeneous function...
        vector<ll> last_state(n + 3, 0);

        // like a[i] = a[i-1], a[i-2]..
        for (int i = 0; i < n; ++i) {
            last_state[i] = a[n - 1 - i]; // order matter
        }

        last_state[n] = 1; // constant
        last_state[n + 1] = n - 1; // i = (i - 1) + 1
        last_state[n + 2] = ((n - 1) * (n - 1)) % mod; // i^2 = (i-1)^2 + 2(i-1) + 1

        for (int i = 0; i < n; ++i) {
            mat[0][i] = c[i];
        }

        mat[0][n] = (p + q + r) % mod;
        mat[0][n + 1] = (q + 2 * r) % mod;
        mat[0][n + 2] = r;

        // dg(mat);

        for (int i = 1; i < n; ++i) {
            mat[i][i - 1] = 1;
        }

        mat[n][n] = 1;
        mat[n + 1][n] = mat[n + 1][n + 1] = 1;
        mat[n + 2][n] = 1, mat[n + 2][n + 1] = 2, mat[n + 2][n + 2] = 1;

        // dg(mat);
        // dg(last_state);

        ll b = k - n + 1;
        while (b) {
            if (b & 1) {
                ans = matExp(ans, mat, n + 3);
            }
            mat = matExp(mat, mat, n + 3);
            b >>= 1;
        }

        ll ans_ak = 0;
        for (int i = 0; i < n + 3; ++i) {
            ans_ak += ((ans[0][i] * last_state[i]) % mod);
            ans_ak %= mod;
        }

        // dg(last_state, mat);
        cout << ans_ak << '\n';
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
