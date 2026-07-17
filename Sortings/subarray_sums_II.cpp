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

ll n, x;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    cin >> n >> x;
    vector<ll> a(n);
    for (ll &c : a) cin >> c;

    vector<ll> pref(n + 1, 0);
    for (ll i = 1; i <= n; ++i) pref[i] = pref[i - 1] + a[i - 1];

    gp_hash_table<ll, ll, custom_hash> f;
    f[0] = 1;

    ll count = 0;

    for (ll i = 0; i < n; ++i) {
        ll curr = pref[i + 1];
        ll target = curr - x;
        if (f.find(target) != f.end()) {
            count += f[target];
        }
        f[pref[i + 1]]++;
    }

    cout << count << nl;
}