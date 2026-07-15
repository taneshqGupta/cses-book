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
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> grid[i][j];
    }

    vector dp = grid;

    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(n));
    parent[0][0] = {-1, -1};
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            // cout << grid[i][j] << nl;
            if (i == 0 && j == 0) continue;
            if (i > 0 && j == 0) {
                parent[i][j] = {i - 1, j};
                dp[i][j] += dp[i - 1][j];
                continue;
            }
            if (i == 0 && j > 0) {
                parent[i][j] = {i, j - 1};
                dp[i][j] += dp[i][j - 1];
                continue;
            }
            if (dp[i - 1][j] > dp[i][j - 1]) {
                parent[i][j] = {i - 1, j};
                dp[i][j] += dp[i - 1][j];
            } else {
                parent[i][j] = {i, j - 1};
                dp[i][j] += dp[i][j - 1];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dp[i][j] << ' ';
        }
        cout << nl;
    }

    cout << nl;

    vector<int> path;

    pair<int, int> curr = {n - 1, n - 1};
    while (curr != make_pair(-1, -1)) {
        path.push_back(grid[curr.first][curr.second]);
        curr = parent[curr.first][curr.second];
    }
    reverse(all(path));
    for (auto x : path) {
        cout << x << ' ';
    }
    cout << nl;
}
