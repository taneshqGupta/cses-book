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

const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m;
    cin >> n >> m;

    // Djisktra

    using pll = pair<ll, ll>;

    priority_queue<pll, vector<pll>, greater<pll>> q;

    vector<vector<pll>> adj(n);

    for (ll i = 0; i < m; ++i) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        adj[a].push_back({b, c});
    }

    vector<ll> d(n, INF);
    vector<ll> p(n, -1);

    d[0] = 0;
    q.push({0, 0});

    while (!q.empty()) {
        auto [d_v, v] = q.top();
        q.pop();

        if (d_v > d[v]) continue;

        for (auto [to, d_to] : adj[v]) {

            if (d[v] + d_to < d[to]) {
                d[to] = d[v] + d_to;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }

    for (ll c : d) cout << c << ' ';
    cout << nl;
}