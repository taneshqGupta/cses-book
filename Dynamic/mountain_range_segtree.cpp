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

struct Node {
    ll max_val;
};

struct SegTree {
    vector<Node> t;

    SegTree(ll n) {
        t.assign(4 * n + 1, {0});
    }

    Node merge(const Node &l, const Node &r) const {
        return {max(l.max_val, r.max_val)};
    }

    void update(ll v, ll tl, ll tr, ll i, ll new_val) {
        if (tl == tr) {
            t[v] = {new_val};
        } else {
            ll tm = tl + (tr - tl) / 2;
            if (i <= tm) {
                update(v * 2, tl, tm, i, new_val);
            } else {
                update(v * 2 + 1, tm + 1, tr, i, new_val);
            }
            t[v] = merge(t[v * 2], t[v * 2 + 1]);
        }
    }

    Node query(ll v, ll tl, ll tr, ll l, ll r) {
        if (l > r) return {0};
        if (l == tl && r == tr) return t[v];
        ll tm = tl + (tr - tl) / 2;
        if (l > tm) {
            return query(2 * v + 1, tm + 1, tr, l, r);
        }
        if (r <= tm) {
            return query(2 * v, tl, tm, l, r);
        }
        return merge(query(2 * v + 1, tm + 1, tr, tm + 1, r),
                     query(2 * v, tl, tm, l, tm));
    }
};

const ll MOD = 1e9 + 7;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ll n;
    cin >> n;

    vector<ll> mountains(n + 2, 0);
    for (ll i = 1; i <= n; ++i) {
        ll num;
        cin >> num;
        mountains[i] = num;
    }

    // Stack to find nearest taller or equal mountain to the left
    stack<ll> st;
    vector<ll> L(n + 2, 0);

    for (ll i = 1; i <= n; ++i) {
        while (!st.empty() && mountains[st.top()] < mountains[i]) {
            st.pop();
        }
        if (!st.empty()) L[i] = st.top();
        st.push(i);
    }

    // Stack to find nearest taller or equal mountain to the left
    st = stack<ll>();
    vector<ll> R(n + 2, n + 1);

    for (ll i = n; i >= 1; --i) {
        while (!st.empty() && mountains[st.top()] < mountains[i]) {
            st.pop();
        }
        if (!st.empty()) R[i] = st.top();
        st.push(i);
    }

    map<ll, vector<ll>> height_groups;

    for (ll i = 1; i <= n; ++i) {
        height_groups[mountains[i]].push_back(i);
    }

    SegTree tree(n + 1);
    ll max_ans = 0;

    for (auto const &[h, indices] : height_groups) {
        vector<pair<ll, ll>> updates;

        for (ll i : indices) {
            ll ql = L[i] + 1;
            ll qr = R[i] - 1;
            ll best_prev = 0;
            if (ql <= qr) {
                best_prev = tree.query(1, 1, n, ql, qr).max_val;
            }
            ll current_dp = 1 + best_prev;
            updates.push_back({i, current_dp});
            max_ans = max(max_ans, current_dp);
        }

        for (auto const &[i, new_val] : updates) {
            tree.update(1, 1, n, i, new_val);
        }
    }

    cout << max_ans << nl;
}