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
    ll n, x;
    cin >> n >> x;
    vector<ll> p(n);
    for (ll &c : p) cin >> c;
    vector<ll> pg(n);
    for (ll &c : pg) cin >> c;

    vector<ll> dp(x + 1, 0);
    // vector<vector<bool>> choice(n, vector<bool>(x + 1, false));

    dp[0] = 0;

    for (ll i = 0; i < n; ++i) {
        for (ll j = x; j >= p[i]; --j) {
            dp[j] = max(dp[j], dp[j - p[i]] + pg[i]);
            // ll take = dp[j - p[i]] + pg[i];
            // if (take > dp[j]) {
            //     dp[j] = take;
            //     choice[i][j] = true;
            // }
        }
    }

    cout << dp[x] << nl;

    // ll current_weight = x;
    // vector<ll> picked_items;

    // for (ll i = n - 1; i >= 0; --i) {
    //     if (choice[i][current_weight]) {
    //         picked_items.push_back(i);
    //         current_weight -= p[i];
    //     }
    // }

    // for (ll &i : picked_items) {
    //     cout << i + 1 << ' ';
    // }
    // cout << nl;
}