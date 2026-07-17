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

    vector<ll> dp(n + 1, 1e18);
    dp[0] = 0;

    // vector<ll> last(n + 1);
    vector<ll> digits;
    for (ll i = 1; i <= n; ++i) {
        digits.clear();
        ll nn = i;
        while (nn > 0) {
            digits.push_back(nn % 10);
            nn /= 10;
        }
        ll x = digits.size();

        for (ll c = 0; c < x; ++c) {
            if (i >= digits[c]) {
                if (dp[i - digits[c]] + 1 < dp[i]) {
                    dp[i] = dp[i - digits[c]] + 1;
                    // last[i] = i - digits[c];
                }
            }
        }
    }

    cout << dp[n] << nl;
    // while (n > 0) {
    //     cout << last[n] << ' ';
    //     n = last[n];
    // }
}