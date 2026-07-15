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
    vector<pair<ll, ll>> a(n);
    for (ll i = 0; i < n; i++) {
        ll num;
        cin >> num;
        a[i] = {num, i + 1};
    }

    if (n < 3) {
        cout << "IMPOSSIBLE" << nl;
        return 0;
    }
    sort(all(a));

    bool ys = false;
    tuple<ll, ll, ll> ans = {-1, -1, -1};
    for (ll i = 2; i < n && !ys; i++) {
        if (a[i].first >= (x - 1)) {
            continue;
        }
        ll target = x - a[i].first;
        ll left = 0, right = i - 1;
        while (!ys && left < i && right < i && right >= 0 && left != right) {
            ll sum = a[left].first + a[right].first;
            if (sum == target) {
                ys = true;
                ans = {a[i].second, a[left].second, a[right].second};
                break;
            }
            if (sum < target) {
                left++;
            }
            if (sum > target) {
                right--;
            }
        }
    }
    if (ys) {
        cout << get<0>(ans) << ' ' << get<1>(ans) << ' ' << get<2>(ans) << nl;
    } else {
        cout << "IMPOSSIBLE" << nl;
    }
}