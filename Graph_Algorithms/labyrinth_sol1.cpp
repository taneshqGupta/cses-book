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
    vector<string> s(n);
    for (auto &c : s) cin >> c;

    queue<pair<ll, ll>> q;
    vector<vector<bool>> used(n, vector<bool>(m, false));
    vector<vector<ll>> d(n, vector<ll>(m, -1));
    vector<vector<char>> p(n, vector<char>(m));

    ll i = 0, j = 0, bi = 0, bj = 0;
    for (ll r = 0; r < n; ++r) {
        for (ll c = 0; c < m; ++c) {
            if (s[r][c] == 'A') {
                i = r;
                j = c;
            }
            if (s[r][c] == 'B') {
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
        if (r > 0) {
            if (!used[r - 1][c] && s[r - 1][c] != '#') {
                q.push({r - 1, c});
                used[r - 1][c] = true;
                d[r - 1][c] = d[r][c] + 1;
                p[r - 1][c] = 'U';
            }
        }
        if (c > 0) {
            if (!used[r][c - 1] && s[r][c - 1] != '#') {
                q.push({r, c - 1});
                used[r][c - 1] = true;
                d[r][c - 1] = d[r][c] + 1;
                p[r][c - 1] = 'L';
            }
        }
        if (r < n - 1) {
            if (!used[r + 1][c] && s[r + 1][c] != '#') {
                q.push({r + 1, c});
                used[r + 1][c] = true;
                d[r + 1][c] = d[r][c] + 1;
                p[r + 1][c] = 'D';
            }
        }
        if (c < m - 1) {
            if (!used[r][c + 1] && s[r][c + 1] != '#') {
                q.push({r, c + 1});
                used[r][c + 1] = true;
                d[r][c + 1] = d[r][c] + 1;
                p[r][c + 1] = 'R';
            }
        }
    }

    if (d[bi][bj] == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n" << d[bi][bj] << nl;
        vector<char> path;
        ll ci = bi, cj = bj;
        while (ci != i || cj != j) {
            char last_move = p[ci][cj];
            path.push_back(last_move);
            if (last_move == 'U') {
                ci += 1;
                continue;
            }
            if (last_move == 'D') {
                ci -= 1;
                continue;
            }
            if (last_move == 'L') {
                cj += 1;
                continue;
            }
            if (last_move == 'R') {
                cj -= 1;
                continue;
            }
        }
        reverse(all(path));
        for (auto c : path) {
            cout << c;
        }
        cout << nl;
    }
}