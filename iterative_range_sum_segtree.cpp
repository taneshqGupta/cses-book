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

const ll N = 1 << 18;
ll trex[2 * N];

void update(ll i, ll x) {
    i += N;
    trex[i] = x;
    while (i > 1) {
        i /= 2;
        trex[i] = trex[i * 2] + trex[i * 2 + 1];
    }
}

ll query(ll l, ll r) {
    ll res = 0;
    l += N;
    r += N;
    while (l <= r) {
        if (l % 2 == 1) res = res + trex[l++];
        if (r % 2 == 0) res = res + trex[r--];
        l /= 2;
        r /= 2;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll n, q;
    cin >> n >> q;

    for (ll i = 0; i < n; ++i) {
        ll a;
        cin >> a;
        update(i, a);
    }

    while (q--) {
        ll a, b, c;
        cin >> a >> b >> c;

        if (a == 1) {
            update(b - 1, c);
        } else {
            cout << query(b - 1, c - 1) << nl;
        }
    }
}