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

// DIRECTION ARRAYS
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};
const char dch[] = {'U', 'D', 'L', 'R'};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (auto &c : s) cin >> c;

    queue<pair<ll, ll>> q;
    vector<vector<bool>> used(n, vector<bool>(m, false));
    vector<vector<ll>> d(n, vector<ll>(m, -1));
    // p stores the index (0-3) of the direction taken to reach a cell
    vector<vector<int>> p(n, vector<int>(m, -1));

    ll i = 0, j = 0, bi = 0, bj = 0;
    for (ll r = 0; r < n; ++r) {
        for (ll c = 0; c < m; ++c) {
            if (s[r][c] == 'A') {
                i = r;
                j = c;
            } else if (s[r][c] == 'B') {
                bi = r;
                bj = c;
            }
        }
    }

    used[i][j] = true;
    d[i][j] = 0;
    q.push({i, j});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int k = 0; k < 4; ++k) {
            ll nr = r + dr[k];
            ll nc = c + dc[k];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m && !used[nr][nc] &&
                s[nr][nc] != '#') {

                used[nr][nc] = true;
                d[nr][nc] = d[r][c] + 1;
                p[nr][nc] = k;
                q.push({nr, nc});
            }
        }
    }

    if (d[bi][bj] == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n" << d[bi][bj] << nl;
        string path = "";
        ll ci = bi, cj = bj;

        while (ci != i || cj != j) {
            int k = p[ci][cj];
            path += dch[k];
            ci -= dr[k];
            cj -= dc[k];
        }
        reverse(all(path));
        cout << path << nl;
    }
}