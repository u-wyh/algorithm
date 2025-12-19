#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll simulate(bool start_left, const vector<pair<ll, int>>& L, const vector<pair<ll, int>>& R, ll k, vector<tuple<ll, int, int>>& sch, int n, int m) {
    int l_ptr = 0, r_ptr = 0;
    bool cur_left = start_left;
    ll cur_time = 0;
    ll max_finish = 0;
    sch.clear();
    while (l_ptr < n || r_ptr < m) {
        ll board = -1;
        int tpi = -1;
        int idi = -1;
        if (cur_left) {
            if (l_ptr >= n) {
                cur_time += k;
                cur_left = false;
                continue;
            }
            auto [arr, idx] = L[l_ptr];
            board = max(cur_time, arr);
            tpi = 0;
            idi = idx;
            l_ptr++;
            cur_time = board + k;
            cur_left = false;
            max_finish = max(max_finish, board + k);
        } else {
            if (r_ptr >= m) {
                cur_time += k;
                cur_left = true;
                continue;
            }
            auto [arr, idx] = R[r_ptr];
            board = max(cur_time, arr);
            tpi = 1;
            idi = idx;
            r_ptr++;
            cur_time = board + k;
            cur_left = true;
            max_finish = max(max_finish, board + k);
        }
        if (board != -1) {
            sch.emplace_back(board, tpi, idi);
        }
    }
    return max_finish;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    ll k;
    cin >> n >> m >> k;
    vector<pair<ll, int>> left(n), right(m);
    for (int i = 0; i < n; i++) {
        cin >> left[i].first;
        left[i].second = i + 1;
    }
    sort(left.begin(), left.end());
    for (int i = 0; i < m; i++) {
        cin >> right[i].first;
        right[i].second = i + 1;
    }
    sort(right.begin(), right.end());
    vector<tuple<ll, int, int>> sch1, sch2;
    ll T1 = simulate(true, left, right, k, sch1, n, m);
    ll T2 = simulate(false, left, right, k, sch2, n, m);
    ll T = min(T1, T2);
    auto& sch = (T1 < T2 ? sch1 : (T2 < T1 ? sch2 : sch1));
    cout << T << '\n';
    for (auto [ti, tpi, idi] : sch) {
        cout << ti << ' ' << tpi << ' ' << idi << '\n';
    }
    return 0;
}
/*
5 5 2
 2 1 13 19 11
 12 18 19 7 8
 */