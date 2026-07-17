#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define nl '\n'
#define all(x) (x).begin(), (x).end()

struct Node {
    ll sum, pref, suff, ans;
};

struct SegTree {
    vector<Node> t;

    SegTree(const vector<ll> &a) {
        ll n = a.size();
        t.assign(4 * n + 1, {0, 0, 0, 0});
        if (n > 0) {
            init_build(1, 0, n - 1, a);
        }
    }

    Node merge(const Node &l, const Node &r) const {
        Node res;
        res.sum = l.sum + r.sum;
        res.pref = max(l.pref, l.sum + r.pref);
        res.suff = max(r.suff, r.sum + l.suff);
        res.ans = max({l.ans, r.ans, l.suff + r.pref});
        return res;
    }

    void init_build(int v, int tl, int tr, const vector<ll> &a) {
        if (tl == tr) {
            ll val = a[tl];
            ll p = max(0LL, val);
            t[v] = {val, p, p, p};
        } else {
            int tm = tl + (tr - tl) / 2;
            init_build(v * 2, tl, tm, a);
            init_build(v * 2 + 1, tm + 1, tr, a);
            t[v] = merge(t[v * 2], t[v * 2 + 1]);
        }
    }

    void update(int v, int tl, int tr, int i, ll new_val) {
        if (tl == tr) {
            ll p = max(0LL, new_val);
            t[v] = {new_val, p, p, p};
        } else {
            int tm = tl + (tr - tl) / 2;
            if (i <= tm) {
                update(v * 2, tl, tm, i, new_val);
            } else {
                update(v * 2 + 1, tm + 1, tr, i, new_val);
            }
            t[v] = merge(t[v * 2], t[v * 2 + 1]);
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for (ll &x : a) cin >> x;

    SegTree st(a);

    while (m--) {
        ll k, x;
        cin >> k >> x;
        k--;
        st.update(1, 0, n - 1, k, x);
        cout << st.t[1].ans << nl;
    }
}