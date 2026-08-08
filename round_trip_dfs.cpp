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

ll n, m;
vector<ll> parent;
vector<vector<ll>> adj;
vector<ll> used;
vector<ll> path;
bool cycle = false;

void dfs(ll v, ll p = -1) {
    used[v] = true;
    parent[v] = p;

    for (ll u : adj[v]) {
        if (cycle) return;
        if (!used[u]) {
            dfs(u, v);
        } else {
            if (u != p) {
                cycle = true;
                path.push_back(u);
                ll curr = v;
                while (curr != u) {
                    path.push_back(curr);
                    curr = parent[curr];
                }
                path.push_back(curr);
                return;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin >> n >> m;
    used.assign(n, false);
    adj.resize(n);
    parent.assign(n, -1);

    // DFS for cycle detection.
    // If you reach an already visited node that is not the direct parent of
    // your current node, you have found a cycle.

    for (ll i = 0; i < m; ++i) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (ll i = 0; i < n; ++i) {
        if (!used[i] && !cycle) {
            dfs(i);
        }
    }
    if (!cycle) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << path.size() << nl;
        for (ll p : path) {
            cout << p + 1 << ' ';
        }
    }
    cout << nl;
}