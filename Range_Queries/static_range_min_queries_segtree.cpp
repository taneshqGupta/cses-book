#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef long long ll;
#define nl '\n'
#define all(x) (x).begin(), (x).end()
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
const ll MOD = 1e9 + 7;

struct Node {
    ll minx;
};

struct SegTree {

    vector<Node> t;

    SegTree(const vector<ll> &a) {
        ll n = a.size();
        t.assign(4 * n + 1, {0});
        if (n > 0) {
            init_build(1, 0, n - 1, a);
        }
    }

    Node merge(const Node &l, const Node &r) const {
        return {min(l.minx, r.minx)};
    }

    void init_build(ll v, ll tl, ll tr, const vector<ll> &a) {
        if (tl == tr) {
            t[v] = {a[tl]};
        } else {
            ll tm = tl + (tr - tl) / 2;
            init_build(v * 2, tl, tm, a);
            init_build(v * 2 + 1, tm + 1, tr, a);
            t[v] = merge(t[v * 2], t[v * 2 + 1]);
        }
    }

    Node query(ll v, ll tl, ll tr, ll l, ll r) {
        if (l == tl && r == tr) return t[v];
        ll tm = tl + (tr - tl) / 2;
        if (l > tm) {
            return query(v * 2 + 1, tm + 1, tr, l, r);
        }
        if (r <= tm) {
            return query(v * 2, tl, tm, l, r);
        }
        return merge(query(v * 2 + 1, tm + 1, tr, tm + 1, r),
                     query(v * 2, tl, tm, l, tm));
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll &c : a) cin >> c;

    SegTree tree(a);

    while (q--) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;

        ll ans = tree.query(1, 0, n - 1, a, b).minx;

        cout << ans << nl;
    }
}