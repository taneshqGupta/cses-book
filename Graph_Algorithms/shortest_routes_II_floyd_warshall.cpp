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
const ll N = 505;
ll dist[N][N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m, q;
    cin >> n >> m >> q;

    for (ll i = 0; i < n; ++i) {

        for (ll j = 0; j < n; ++j) {

            dist[i][j] = INF;
        }
    }

    for (ll i = 0; i < m; ++i) {
        ll a, b, c;
        cin >> a >> b >> c;

        a--;
        b--;

        dist[b][a] = min(dist[a][b], c);
        dist[a][b] = dist[b][a];
    }

    for (ll i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }

    for (ll i = 0; i < n; ++i) {

        for (ll j = 0; j < n; ++j) {

            for (ll k = 0; k < n; ++k) {

                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
                dist[k][j] = dist[j][k];
            }
        }
    }

    while (q--) {

        ll a, b;

        cin >> a >> b;

        a--;
        b--;

        if (dist[a][b] != INF) cout << dist[a][b] << nl;
        else cout << "-1\n";
    }
}