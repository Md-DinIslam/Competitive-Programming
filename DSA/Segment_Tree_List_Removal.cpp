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
 
vector<int> v;
 
class segTree {
    vector<int> sg;
public:
    segTree (int n) : sg(4 * n + 1) {}
 
    int merge(int a, int b) {
        return (a + b);
    }
 
    void upd(int indx, int val, int s, int e, int i = 1) {
        if (s == e) sg[i] = val;
        else {
            int mid = (s + e) / 2;
            if (indx <= mid)
                upd(indx, val, s, mid, 2 * i);
            else
                upd(indx, val, mid + 1, e, 2 * i + 1);
            sg[i] = merge(sg[2 * i], sg[2 * i + 1]);
        }
    }
 
    int qry(int kth, int s, int e, int i = 1) {
        if (s == e) return s;
        int mid = (s + e) / 2;
        int left = sg[2 * i];
        if (left >= kth)
            return qry(kth, s, mid, 2 * i);
        else
            return qry(kth - left, mid + 1, e, 2 * i + 1);
    }
 
    int test(int lb, int rb, int s, int e, int i = 1) {
        if (s > rb || e < lb) return 0;
        if (s >= lb && e <= rb) return sg[i];
        int mid = (s + e) / 2;
        return merge(test(lb, rb, s, mid, 2 * i), test(lb, rb, mid + 1, e, 2 * i + 1));
    }
};
 
void Din() {
    int n;
    cin >> n;
 
    v.assign(n + 1, 0);
    segTree t(n);
 
    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
        t.upd(i, 1, 1, n);
    }
 
    for (int i = 1; i <= n; ++i) {
        int indx;
        cin >> indx;
        int kth = t.qry(indx, 1, n);
        // dg(kth - 1, indx);
        cout << v[kth] << ' ';
        t.upd(kth, 0, 1, n);
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