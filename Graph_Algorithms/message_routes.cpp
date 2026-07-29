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
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n);
    for (ll i = 0; i < m; ++i) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    queue<ll> q;
    vector<ll> d(n, -1), p(n, -1);

    q.push(0);
    d[0] = 0;

    while (!q.empty()) {
        ll mo = q.front();
        q.pop();

        for (ll co : adj[mo]) {
            if (d[co] == -1) {
                q.push(co);
                d[co] = d[mo] + 1;
                p[co] = mo;
            }
        }
    }

    if (d[n - 1] == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << d[n - 1] + 1 << nl;
        vector<ll> path;
        ll i = n - 1;
        while (i != 0) {
            path.push_back(i + 1);
            i = p[i];
        }
        path.push_back(1);
        reverse(all(path));
        for (ll p : path) cout << p << ' ';
        cout << nl;
    }
}