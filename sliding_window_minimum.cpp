#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define nl '\n'
#define all(x) (x).begin(), (x).end()

ll range_sum(const vector<ll> &rolling, ll l, ll r) {
    if (l == 0) {
        return rolling[r];
    }
    return rolling[r] - rolling[l - 1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ll n, a, b;
    cin >> n >> a >> b;
    vector<ll> inp(n);
    for (ll &x : inp) cin >> x;

    vector<ll> pref(n + 1, 0);
    for (ll i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + inp[i];
    }

    deque<ll> dq;
    ll max_sum = -1e18;

    for (ll i = a; i <= n; i++) {
        ll j = i - a;
        while (!dq.empty() && pref[dq.back()] >= pref[j]) {
            dq.pop_back();
        }
        dq.push_back(j);
        if (dq.front() < i - b) {
            dq.pop_front();
        }
        max_sum = max(max_sum, pref[i] - pref[dq.front()]);
    }

    cout << max_sum << nl;
}