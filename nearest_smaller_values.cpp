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
    vector<ll> a(n);
    for (ll &c : a) cin >> c;

    stack<pair<ll, ll>> st;
    vector<ll> res(n);

    res[0] = 0;
    st.push({a[0], 1});

    for (ll i = 1; i < n; ++i) {
        while (!st.empty() && st.top().first >= a[i]) {
            st.pop();
        }
        if (st.empty()) {
            res[i] = 0;
        } else {
            res[i] = st.top().second;
        }
        st.push({a[i], i + 1});
    }

    for (ll &c : res) cout << c << ' ';
    cout << nl;
}