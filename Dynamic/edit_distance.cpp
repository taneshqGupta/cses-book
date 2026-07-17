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
    string x, y;
    cin >> x >> y;

    ll a = x.size(), b = y.size();

    vector<vector<ll>> grid(a + 1, vector<ll>(b + 1));

    grid[0][0] = 0;

    // Initialize first row and column properly
    for (ll i = 0; i <= a; i++) grid[i][0] = i; // deleting all chars from x
    for (ll j = 0; j <= b; j++) grid[0][j] = j; // inserting all chars of y

    // Start loops from 1
    for (ll i = 1; i <= a; i++) {
        for (ll j = 1; j <= b; j++) {
            ll op1 = grid[i - 1][j] + 1; // deletion
            ll op2 = grid[i][j - 1] + 1; // insertion
            ll op3 =
                grid[i - 1][j - 1] + (x[i - 1] != y[j - 1]); // substitution
            grid[i][j] = min({op1, op2, op3});
        }
    }

    for (ll i = 0; i <= a; i++) {
        for (ll j = 0; j <= b; j++) {
            cout << grid[i][j] << ' ';
        }
        cout << nl;
    }

    // cout << grid[a][b] << nl;
}