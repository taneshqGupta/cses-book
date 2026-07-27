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
    vector<ll> a(n), b(m);
    for (ll &c : a) cin >> c;
    for (ll &c : b) cin >> c;

    vector<vector<ll>> grid(n + 1, vector<ll>(m + 1, 0));

    for (ll i = 1; i <= n; ++i) {
        for (ll j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) {
                grid[i][j] = grid[i - 1][j - 1] + 1;
            } else {
                grid[i][j] = max(grid[i - 1][j], grid[i][j - 1]);
            }
        }
    }

    vector<ll> lcs;

    ll i = n, j = m;

    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            lcs.push_back(a[i - 1]);
            i--;
            j--;
        } else if (grid[i - 1][j] > grid[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(all(lcs));

    cout << grid[n][m] << nl;
    for (ll &c : lcs) cout << c << ' ';
    cout << nl;
}