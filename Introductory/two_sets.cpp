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
    ll n;
    cin >> n;
    if (n % 4 == 2 || n % 4 == 1) {
        cout << "NO" << nl;
        return 0;
    }

    if (n % 4 == 0) {
        bool side = true;
        vector<ll> a, b;
        ll l = 1, r = n;
        while (l < r) {
            if (side) {
                a.push_back(l);
                a.push_back(r);
                side = false;
                l++;
                r--;
            } else {
                b.push_back(l);
                b.push_back(r);
                side = true;
                l++;
                r--;
            }
        }
        cout << "YES" << nl;
        cout << a.size() << nl;
        for (ll c : a) cout << c << ' ';
        cout << nl << b.size() << nl;
        for (ll c : b) cout << c << ' ';
        cout << nl;
        return 0;
    }

    if (n % 4 == 3) {
        // the algo is simple, push the first two elements into one set
        // then push the next two elements into the second set
        // then the next two elements into the first set
        // and so on and so forth.
        // then the last element goes to the second set.
        vector<ll> a, b;
        ll i = 1;
        bool side = true;
        while (i <= n - 2) {
            if (side) {
                a.push_back(i);
                a.push_back(i + 1);
                side = false;
                i += 2;
            } else {
                b.push_back(i);
                b.push_back(i + 1);
                side = true;
                i += 2;
            }
        }
        b.push_back(n);
        cout << "YES" << nl;
        cout << a.size() << nl;
        for (ll c : a) cout << c << ' ';
        cout << nl << b.size() << nl;
        for (ll c : b) cout << c << ' ';
        cout << nl;
        return 0;
    }
}