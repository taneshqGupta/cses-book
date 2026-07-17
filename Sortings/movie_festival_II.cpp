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
    ll n, k;
    cin >> n >> k;
    vector<pair<ll, ll>> a(n);
    for (auto &c : a) cin >> c.second >> c.first;
    sort(all(a));

    ll ans_count = 0;

    set<pair<ll, ll>> busy_times;
    for (ll i = 0; i < k; i++) {
        busy_times.insert({0, i});
    }

    ll pointer = 0;

    while (pointer < n) {
        ll this_movies_end_time = a[pointer].first;
        ll this_movies_start_time = a[pointer].second;
        auto it = busy_times.upper_bound({this_movies_start_time, 1e18});
        if (it == busy_times.begin()) {
            pointer++;
            continue;
        }
        it--;
        ll optimal_guy = it->second;
        ll new_busy_time_for_guy = this_movies_end_time;
        busy_times.erase(it);
        busy_times.insert({new_busy_time_for_guy, optimal_guy});
        pointer++;
        ans_count++;
    }

    cout << ans_count << nl;
}