#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define nl '\n'
#define all(x) (x).begin(), (x).end()

ll range_sum(const vector<ll> &pref, ll left, ll right) {
    left++;
    right++;
    return pref[right] - pref[left - 1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ll n, x;
    cin >> n >> x;

    vector<ll> a(n);
    for (ll &c : a) cin >> c;

    vector<ll> pref(n + 1, 0);
    for (ll i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
    for (ll c : pref) cout << c << ' ';
    cout << nl;

    ll left = 0, right = 0;

    bool ys = false;

    while (!ys && left < n && right < n) {
        while (right < n - 1 && range_sum(pref, left, right) < x) {
            right++;
            if (range_sum(pref, left, right) == x) {
                ys = true;
                break;
            }
        }
        if (range_sum(pref, left, right) == x) {
            ys = true;
            break;
        }
        left += 1;
    }
    cout << ys << ' ' << right << ' ' << left << ' '
         << range_sum(pref, left, right) << nl;
}