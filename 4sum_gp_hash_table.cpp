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
    vector<ll> a(n);
    for (ll &c : a) cin >> c;
    if (n < 4) {
        cout << "IMPOSSIBLE" << nl;
        return 0;
    }

    bool ys = false;
    gp_hash_table<ll, pair<ll, ll>, custom_hash> sums;
    sums[a[0] + a[1]] = {2, 1};

    for (ll i = 2; i < n - 1 && !ys; i++) {
        for (ll j = i + 1; j < n && !ys; j++) {
            ll target = x - a[i] - a[j];
            auto it = sums.find(target);
            if (it != sums.end()) {
                ys = true;
                cout << j + 1 << ' ' << i + 1 << ' ';
                cout << it->second.first << ' ' << it->second.second;
                cout << nl;
                break;
            }
        }
        for (ll j = i - 1; j >= 0; j--) {
            sums[a[i] + a[j]] = {i + 1, j + 1};
        }
    }

    if (!ys) cout << "IMPOSSIBLE" << nl;
}
