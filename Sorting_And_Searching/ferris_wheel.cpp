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
    ll n, x;
    cin >> n >> x;
    map<ll, ll> w;
    for (ll i = 0; i < n; ++i) {
        ll num;
        cin >> num;
        w[num]++;
    }
    ll count = 0;

    ll i = 0;

    while (i < n) {
        auto it = w.begin();
        auto a = *it;
        w[a.first]--;
        if (w[a.first] == 0) {
            w.erase(a.first);
        }
        auto co = w.upper_bound(x - a.first);
        if (co != w.begin()) {
            co--;
            i += 2;
            count++;
            auto coa = *co;
            w[coa.first]--;
            if (w[coa.first] == 0) {
                w.erase(coa.first);
            }
            continue;
        }
        if (a.first <= x) {
            i++;
            count++;
            continue;
        }
        break;
    }

    cout << count << nl;
}