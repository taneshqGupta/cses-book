#include <bits/stdc++.h>
using namespace std;

vector<int> lis(const vector<int> &a) {
    int n = a.size();
    const int INF = 1e9;
    vector<int> d(n + 1, INF);
    vector<int> pos(n + 1, -1);
    vector<int> parent(n, -1);

    d[0] = -INF;

    for (int i = 0; i < n; ++i) {
        int l = upper_bound(d.begin(), d.end(), a[i]) - d.begin();

        if (d[l - 1] < a[i]) {
            d[l] = a[i];
            pos[l] = i;
            parent[i] = pos[l - 1];
        }
    }

    int L = n;
    while (L > 0 && d[L] == INF) --L;

    vector<int> subseq;
    int cur = pos[L];
    while (cur != -1) {
        subseq.push_back(a[cur]);
        cur = parent[cur];
    }
    reverse(subseq.begin(), subseq.end());
    return subseq;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    vector<int> inp(n);
    for (int i = 0; i < n; i++) cin >> inp[i];

    vector<int> out = lis(inp);
    for (int x : out) cout << x << ' ';
    cout << '\n';
    return 0;
}