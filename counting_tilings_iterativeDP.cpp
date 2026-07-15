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

const int MOD = 1e9 + 7;

vector<int> next_masks(int mask, int m) {
    vector<int> res;
    struct State {
        int col;
        int next_mask;
    };
    stack<State> st;
    st.push({0, 0});

    while (!st.empty()) {
        auto [col, nm] = st.top();
        st.pop();

        if (col == m) {
            res.push_back(nm);
            continue;
        }

        if (mask & (1 << col)) {
            st.push({col + 1, nm});
        } else {
            st.push({col + 1, nm | (1 << col)});

            if (col + 1 < m && !(mask & (1 << (col + 1)))) {
                st.push({col + 2, nm});
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int n, m;
    cin >> m >> n;
    if (n < m) swap(n, m);
    if ((n * m) % 2 != 0) {
        cout << 0 << '\n';
        return 0;
    }

    // Precompute Transitions
    int total_masks = 1 << m;
    vector<vector<int>> trans(total_masks);
    for (int mask = 0; mask < total_masks; ++mask) {
        trans[mask] = next_masks(mask, m);
    }

    // DP
    vector<ll> dp(total_masks, 0);
    dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        vector<ll> ndp(total_masks, 0);
        for (int mask = 0; mask < total_masks; ++mask) {
            if (dp[mask] == 0) continue;
            for (int nm : trans[mask]) {
                ndp[nm] = (ndp[nm] + dp[mask]) % MOD;
            }
        }
        dp.swap(ndp);
    }

    cout << dp[0] << '\n';
    return 0;
}