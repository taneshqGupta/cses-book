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

struct DSU {
    vector<ll> parent, size;
    ll clusters;

    DSU(int n) {
        clusters = n;
        parent.resize(n);
        size.assign(n, 1);
        iota(all(parent), 0);
    }

    ll find(ll x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(ll a, ll b) {
        ll ra = find(a), rb = find(b);
        if (ra == rb) return;

        if (size[ra] < size[rb]) swap(ra, rb);

        parent[rb] = ra;
        size[ra] += size[rb];
        clusters--;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m;
    cin >> n >> m;

    vector<string> grid(n);
    vector<vector<ll>> mapx(n, vector<ll>(m, -1));

    for (auto &c : grid) cin >> c;

    ll N = 0;

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            if (grid[i][j] == '.') {
                mapx[i][j] = N;
                N += 1;
            }
        }
    }

    DSU tree(N);

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            if (grid[i][j] == '.') {
                if (i > 0) {
                    if (grid[i - 1][j] == '.') {
                        tree.unite(mapx[i][j], mapx[i - 1][j]);
                    }
                }
                if (j > 0) {
                    if (grid[i][j - 1] == '.') {
                        tree.unite(mapx[i][j], mapx[i][j - 1]);
                    }
                }
            }
        }
    }

    cout << tree.clusters << nl;
}