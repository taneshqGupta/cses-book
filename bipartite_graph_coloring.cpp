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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, m;
    cin >> n >> m;
    vector<bool> ans(n, false);
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
    vector<ll> used(n, false);

    bool possible = true;

    for (ll i = 0; i < n; ++i) {
        if (!used[i]) {
            q.push(i);
            used[i] = true;

            while (!q.empty()) {
                ll mo = q.front();
                q.pop();

                for (ll co : adj[mo]) {
                    if (used[co] && ans[co] == ans[mo]) {
                        possible = false;
                        break;
                    }
                    if (!used[co]) {
                        used[co] = true;
                        q.push(co);
                        ans[co] = !ans[mo];
                    }
                }

                if (!possible) break;
            }
        }
        if (!possible) break;
    }

    if (!possible) cout << "IMPOSSIBLE" << nl;
    else {
        for (bool x : ans) {
            if (x) cout << 2 << ' ';
            else cout << 1 << ' ';
        }
        cout << nl;
    }
}