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

    sort(all(a));

    ll left = 0, right = n - 1;
    bool ys = false;
    while (!ys && left < n && right < n && right >= 0 && left != right) {
        ll sum = a[left].first + a[right].first;
        if (sum == x) {
            ys = true;
            break;
        }
        if (sum < x) {
            left++;
        }
        if (sum > x) {
            right--;
        }
    }
    if (!ys) cout << "IMPOSSIBLE" << nl;
    if (ys) cout << a[left].second << ' ' << a[right].second << nl;
}