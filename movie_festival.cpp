#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) (x).begin(), (x).end()

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    vector<tuple<int, int, int>> mov(n);
    for (int i = 0; i < n; i++) {
        int start, end;
        cin >> start >> end;
        mov[i] = {end, start, i};
    }
    sort(all(mov));

    int pointer = 0;
    int count = 0;
    while (pointer < n) {
        count++;
        int current_end_time = get<0>(mov[pointer]);
        while (true) {
            pointer++;
            if (pointer == n) break;
            int current_start_time = get<1>(mov[pointer]);
            if (current_start_time >= current_end_time) break;
        }
    }
    cout << count << '\n';
}