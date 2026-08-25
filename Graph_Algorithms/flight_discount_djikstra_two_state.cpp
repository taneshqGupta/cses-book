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

    vector<vector<pair<ll, ll>>> graph(n);

    for (ll i = 0; i < m; ++i) {
        ll a, b, c;

        cin >> a >> b >> c;

        a--;
        b--;

        graph[a].push_back({b, c});
    }

    vector<vector<ll>> d(n, vector<ll>(2, INF));

    d[0][0] = 0;

    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<>> pq;

    pq.push({0, 0, 0});

    while (!pq.empty()) {

        auto [d_u, u, used] = pq.top();

        pq.pop();

        if (d_u != d[u][used]) continue;

        for (auto [v, w] : graph[u]) {

            // Option 1: Don't use discount on this edge
            if (d[v][used] > d_u + w) {
                d[v][used] = d_u + w;
                pq.push({d[v][used], v, used});
            }

            // Option 2: Use discount on this edge (only if not used before)
            if (used == 0) {
                ll new_d = d_u + (w / 2);
                if (d[v][1] > new_d) {
                    d[v][1] = new_d;
                    pq.push({d[v][1], v, 1});
                }
            }
        }
    }

    cout << d[n - 1][1] << nl;
}