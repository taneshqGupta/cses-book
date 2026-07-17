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
    ll M = 1e9 + 7;
    ll n, x;
    cin >> n >> x;
    vector<ll> c(n);
    for (ll &t : c) cin >> t;

    vector<ll> dp(x + 1, 0);
    dp[0] = 1;
    for (ll i = 1; i <= x; ++i) {
        for (ll coin = n - 1; coin >= 0; coin--) {
            if (i >= c[coin]) {
                dp[i] = (dp[i] + dp[i - c[coin]]) % M;
            }
        }
    }

    cout << dp[x] << nl;
}