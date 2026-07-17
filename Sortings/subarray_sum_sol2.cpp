#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define nl '\n'

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n, x;
    if (!(cin >> n >> x)) return 0;

    vector<ll> a(n);
    for (ll &c : a) cin >> c;

    ll left = 0, right = 0;
    ll current_sum = 0;
    bool ys = false;

    while (right < n) {
        // Expand the window by adding the right element
        current_sum += a[right];

        // Shrink the window from the left if the sum exceeds the target
        while (current_sum > x && left <= right) {
            current_sum -= a[left];
            left++;
        }

        // Check if the target is found
        if (current_sum == x) {
            ys = true;
            break;
        }

        right++;
    }

    if (ys) {
        cout << 1 << ' ' << right << ' ' << left << ' ' << current_sum << nl;
    } else {
        cout << 0 << nl;
    }

    return 0;
}