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
    vector<string> a(n);
    for (auto &s : a) cin >> s;

    const int M = 1e9 + 7;
    vector<vector<ll>> ans(n, vector<ll>(n, 0));

    if (a[0][0] == '.') {
        ans[0][0] = 1;
    } else {
        cout << 0 << nl;
        return 0;
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; ++j) {
            if (a[i][j] == '*') {
                ans[i][j] = 0;
                continue;
            }
            if (i > 0) {
                ans[i][j] = (ans[i][j] + ans[i - 1][j]) % M;
            }
            if (j > 0) {
                ans[i][j] = (ans[i][j] + ans[i][j - 1]) % M;
            }
        }
    }

    cout << ans[n - 1][n - 1] << nl;
}