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
    ll a, b, c;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m;
    cin >> n >> m;

    vector<Edge> edges(m);

    for (ll i = 0; i < m; ++i) {
        ll a, b, c;
        cin >> a >> b >> c;

        a--;
        b--;

        edges[i] = {a, b, c};
    }

    vector<ll> d(n, 0);
    vector<ll> p(n, -1);

    d[0] = 0;

    ll x = -1;

    for (ll i = 0; i < n; ++i) {

        x = -1;

        for (auto [a, b, c] : edges) {

            if (d[b] > (d[a] + c)) {
                x = b;
                d[b] = d[a] + c;
                p[b] = a;
            }
        }
    }
    if (x == -1) cout << "NO\n";
    else {
        cout << "YES\n";

        for (ll i = 0; i < n; ++i) {
            x = p[x];
        }

        ll curr = x;
        vector<ll> cycle;

        while (true) {
            cycle.push_back(curr);
            if (curr == x && cycle.size() > 1) break;
            curr = p[curr];
        }

        reverse(all(cycle));

        for (ll c : cycle) cout << c + 1 << ' ';
        cout << nl;
    }
}