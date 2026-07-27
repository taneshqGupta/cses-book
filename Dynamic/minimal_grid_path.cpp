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
    ll n;
    cin >> n;
    vector<string> grid(n);
    for (auto &c : grid) cin >> c;

    string ans = "";
    ans += grid[0][0];

    vector<pair<ll, ll>> active;
    active.push_back({0, 0});

    vector<vector<bool>> vis(n, vector<bool>(n, false));
    vis[0][0] = true;

    for (ll step = 0; step < 2 * n - 2; ++step) {
        char min_char = 'Z' + 1;
        vector<pair<ll, ll>> candidates;

        for (auto [r, c] : active) {
            // check down
            if (r + 1 < n) {
                if (grid[r + 1][c] < min_char) {
                    min_char = grid[r + 1][c];
                    candidates.clear();
                    candidates.push_back({r + 1, c});
                } else if (grid[r + 1][c] == min_char) {
                    candidates.push_back({r + 1, c});
                }
            }
            // check right
            if (c + 1 < n) {
                if (grid[r][c + 1] < min_char) {
                    min_char = grid[r][c + 1];
                    candidates.clear();
                    candidates.push_back({r, c + 1});
                } else if (grid[r][c + 1] == min_char) {
                    candidates.push_back({r, c + 1});
                }
            }
        }
        ans += min_char;
        active.clear();

        for (auto [r, c] : candidates) {
            if (!vis[r][c]) {
                vis[r][c] = true;
                active.push_back({r, c});
            }
        }
    }

    cout << ans << nl;
}