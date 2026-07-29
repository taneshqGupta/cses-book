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

const ll dr[] = {-1, 1, 0, 0};
const ll dc[] = {0, 0, -1, 1};
const char dch[] = {'U', 'D', 'L', 'R'};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ll n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (auto &c : s) cin >> c;

    vector<pair<ll, ll>> monsters;
    ll si = 0, sj = 0;

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            char curr = s[i][j];
            if (curr == 'M') {
                monsters.push_back({i, j});
                continue;
            }
            if (curr == 'A' && (i == n - 1 || j == m - 1 || i == 0 || j == 0)) {
                cout << "YES\n0\n";
                return 0;
            }
            if (curr == 'A') {
                si = i;
                sj = j;
                continue;
            }
        }
    }

    queue<pair<ll, ll>> q;
    vector<vector<ll>> dm(n, vector<ll>(m, 1e18));
    vector<vector<bool>> usedm(n, vector<bool>(m, false));

    for (auto [mi, mj] : monsters) {
        q.push({mi, mj});
        usedm[mi][mj] = true;
        dm[mi][mj] = 0;
    }

    while (!q.empty()) {
        auto [ci, cj] = q.front();
        q.pop();

        for (ll k = 0; k < 4; ++k) {
            ll ni = ci + dr[k];
            ll nj = cj + dc[k];

            if (ni >= 0 && nj >= 0 && ni < n && nj < m && !usedm[ni][nj] &&
                s[ni][nj] != '#') {

                usedm[ni][nj] = true;
                dm[ni][nj] = min(dm[ni][nj], dm[ci][cj] + 1);
                q.push({ni, nj});
            }
        }
    }

    q = queue<pair<ll, ll>>();

    vector<vector<bool>> used(n, vector<bool>(m, false));
    vector<vector<ll>> d(n, vector<ll>(m, -1)), p(n, vector<ll>(m, -1));
    q.push({si, sj});
    d[si][sj] = 0;
    used[si][sj] = true;

    bool found = false;
    ll li = -1, lj = -1;
    while (!q.empty()) {
        auto [ci, cj] = q.front();
        q.pop();

        for (ll k = 0; k < 4; ++k) {
            ll ni = ci + dr[k];
            ll nj = cj + dc[k];

            if (ni < n && nj < m && ni >= 0 && nj >= 0 && s[ni][nj] != '#' &&
                !used[ni][nj]) {

                ll new_d = d[ci][cj] + 1;

                if (new_d < dm[ni][nj]) {
                    used[ni][nj] = true;
                    q.push({ni, nj});
                    d[ni][nj] = new_d;
                    p[ni][nj] = k;

                    if ((ni == n - 1 || nj == m - 1 || ni == 0 || nj == 0)) {
                        li = ni;
                        lj = nj;
                        found = true;
                        break;
                    }
                }
            }
        }

        if (found) break;
    }

    if (!found) {

        cout << "NO\n";

    } else {

        cout << "YES\n";

        vector<char> path;

        ll ci = li, cj = lj;

        while (ci != si || cj != sj) {
            ll k = p[ci][cj];
            path.push_back(dch[k]);
            ci = ci - dr[k];
            cj = cj - dc[k];
        }

        reverse(all(path));

        cout << path.size() << nl;

        for (char ch : path) {
            cout << ch;
        }
        cout << nl;
    }
}