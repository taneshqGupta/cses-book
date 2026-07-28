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
    ll n, m;
    cin >> n >> m;
    map<ll, ll> t_prices;
    for (ll i = 0; i < n; ++i) {
        ll num;
        cin >> num;
        t_prices[num]++;
    }
    vector<ll> m_price(m);
    for (ll &c : m_price) cin >> c;

    vector<ll> ans(m, -1);

    for (ll i = 0; i < m; ++i) {
        auto it = t_prices.upper_bound(m_price[i]);
        if (it == t_prices.begin()) {
            continue;
        }
        it--;
        auto ita = *it;
        t_prices[ita.first]--;
        if (t_prices[ita.first] == 0) {
            t_prices.erase(ita.first);
        }
        ans[i] = ita.first;
    }

    for (ll &c : ans) {
        cout << c << nl;
    }
}