#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define nl '\n'
#define all(x) (x).begin(), (x).end()

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ll n, x;
    cin >> n >> x;

    unordered_map<ll, ll> mp;
    for (ll i = 0; i < n; i++) {
        ll a;
        cin >> a;
        if (a >= x) continue;
        if (mp[x - a]) {
            cout << mp[x - a] << " " << i + 1 << nl;
            return 0;
        }
        mp[a] = i + 1;
    }
    cout << "IMPOSSIBLE" << nl;
}