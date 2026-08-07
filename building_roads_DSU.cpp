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
    vector<ll> parents, sizes;
    gp_hash_table<ll, ll, custom_hash> roots;
    ll clusters;

    DSU(ll n) {
        clusters = n;
        sizes.assign(n, 1);
        parents.resize(n);
        iota(all(parents), 0);

        for (ll i = 0; i < n; ++i) {
            roots.insert({i, 1});
        }
    }

    ll find(ll x) {
        if (parents[x] != x) {
            parents[x] = find(parents[x]);
        }
        return parents[x];
    }

    void unite(ll a, ll b) {
        ll ra = find(a), rb = find(b);
        if (ra != rb) {
            if (sizes[ra] < sizes[rb]) swap(ra, rb);
            parents[rb] = ra;
            clusters--;
            sizes[ra] += sizes[rb];
            if (roots.find(rb) != roots.end()) roots.erase(rb);
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

    DSU roads(n);

    for (ll i = 0; i < m; ++i) {
        ll a, b;
        cin >> a >> b;

        a--;
        b--;

        roads.unite(a, b);
    }

    auto it = roads.roots.begin();
    auto jt = roads.roots.begin();

    it++;

    if (it == roads.roots.end()) {
        cout << 0 << nl;
        return 0;
    }
    cout << roads.clusters - 1 << nl;

    while (it != roads.roots.end()) {
        cout << jt->first + 1 << ' ' << it->first + 1 << nl;
        jt++;
        it++;
    }
}