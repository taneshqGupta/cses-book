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

struct Edge {
    ll a, b, cost;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    // todo!
    // look at cses analysis code, it is much more elegant.

    ll n, m;
    cin >> n >> m;

    vector<Edge> graph(m);

    for (ll i = 0; i < m; ++i) {
        ll a, b, cost;

        cin >> a >> b >> cost;

        a--;
        b--;

        graph[i] = Edge{a, b, -cost};
    }

    vector<ll> d(n, INF);

    d[0] = 0;

    for (ll i = 0; i < n; ++i) {

        for (const auto &e : graph) {

            if (d[e.a] < INF && d[e.b] > (d[e.a] + e.cost)) {

                d[e.b] = d[e.a] + e.cost;
            }
        }
    }

    for (ll i = 0; i < n; ++i) {

        for (const auto &e : graph) {

            if (d[e.a] < INF) {

                if (d[e.a] == -INF || (d[e.a] + e.cost) < d[e.b]) {

                    d[e.b] = -INF;
                }
            }
        }
    }

    if (d[n - 1] == -INF) cout << -1 << nl;
    else cout << -d[n - 1] << nl;
}