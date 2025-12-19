#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

const int mod = 998244353;

bool is_leap_year(int y_mod400) {
    if (y_mod400 % 400 == 0) return true;
    if (y_mod400 % 100 == 0) return false;
    if (y_mod400 % 4 == 0) return true;
    return false;
}

int days_in_month(int m, bool leap) {
    if (m == 2) {
        return leap ? 29 : 28;
    }
    if (m == 4 || m == 6 || m == 9 || m == 11) {
        return 30;
    }
    return 31;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    long long ans = 0;

    // dp0: phase0 (not started)
    long long dp0 = 1;

    // dp1: phase1 (1 year digit), y1 in [0,9]
    vector<long long> dp1(10, 0);

    // dp2: phase2 (2 year digits), y2 in [0,99]
    vector<long long> dp2(100, 0);

    // dp3: phase3 (3 year digits), y3 in [0,999]
    vector<long long> dp3(1000, 0);

    // dp4: phase4 (year done), y_mod400 in [0,399]
    vector<long long> dp4(400, 0);

    // dp5: phase5 (1 month digit), [y_mod400][m1] where m1=0 or 1
    vector<vector<long long>> dp5(400, vector<long long>(2, 0));

    // dp6: phase6 (month done), [y_mod400][m] where m=1-12 (index 0-11 for m=1-12)
    vector<vector<long long>> dp6(400, vector<long long>(12, 0));

    // dp7: phase7 (1 date digit), [y_mod400][m_index][d1] where d1 in 0-3
    vector<vector<vector<long long>>> dp7(400, vector<vector<long long>>(12, vector<long long>(4, 0)));

    for (char c_char : s) {
        int d = c_char - '0';

        long long new_dp0 = 0;
        vector<long long> new_dp1(10, 0);
        vector<long long> new_dp2(100, 0);
        vector<long long> new_dp3(1000, 0);
        vector<long long> new_dp4(400, 0);
        vector<vector<long long>> new_dp5(400, vector<long long>(2, 0));
        vector<vector<long long>> new_dp6(400, vector<long long>(12, 0));
        vector<vector<vector<long long>>> new_dp7(400, vector<vector<long long>>(12, vector<long long>(4, 0)));

        // Skip current character for all phases
        new_dp0 = (new_dp0 + dp0) % mod;

        for (int y1 = 0; y1 < 10; y1++) {
            if (dp1[y1]) {
                new_dp1[y1] = (new_dp1[y1] + dp1[y1]) % mod;
            }
        }

        for (int y2 = 0; y2 < 100; y2++) {
            if (dp2[y2]) {
                new_dp2[y2] = (new_dp2[y2] + dp2[y2]) % mod;
            }
        }

        for (int y3 = 0; y3 < 1000; y3++) {
            if (dp3[y3]) {
                new_dp3[y3] = (new_dp3[y3] + dp3[y3]) % mod;
            }
        }

        for (int y_mod = 0; y_mod < 400; y_mod++) {
            if (dp4[y_mod]) {
                new_dp4[y_mod] = (new_dp4[y_mod] + dp4[y_mod]) % mod;
            }
        }

        for (int y_mod = 0; y_mod < 400; y_mod++) {
            for (int m1 = 0; m1 < 2; m1++) {
                if (dp5[y_mod][m1]) {
                    new_dp5[y_mod][m1] = (new_dp5[y_mod][m1] + dp5[y_mod][m1]) % mod;
                }
            }
        }

        for (int y_mod = 0; y_mod < 400; y_mod++) {
            for (int m_idx = 0; m_idx < 12; m_idx++) {
                if (dp6[y_mod][m_idx]) {
                    new_dp6[y_mod][m_idx] = (new_dp6[y_mod][m_idx] + dp6[y_mod][m_idx]) % mod;
                }
            }
        }

        for (int y_mod = 0; y_mod < 400; y_mod++) {
            for (int m_idx = 0; m_idx < 12; m_idx++) {
                for (int d1 = 0; d1 < 4; d1++) {
                    if (dp7[y_mod][m_idx][d1]) {
                        new_dp7[y_mod][m_idx][d1] = (new_dp7[y_mod][m_idx][d1] + dp7[y_mod][m_idx][d1]) % mod;
                    }
                }
            }
        }

        // Use current character to advance states
        // From phase0: start year, go to phase1 with y1 = d
        if (dp0) {
            new_dp1[d] = (new_dp1[d] + dp0) % mod;
        }

        // From phase1: add year digit, go to phase2 with y2 = 10*y1 + d
        for (int y1 = 0; y1 < 10; y1++) {
            if (dp1[y1]) {
                int y2 = 10 * y1 + d;
                if (y2 >= 0 && y2 < 100) {
                    new_dp2[y2] = (new_dp2[y2] + dp1[y1]) % mod;
                }
            }
        }

        // From phase2: add year digit, go to phase3 with y3 = 10*y2 + d
        for (int y2 = 0; y2 < 100; y2++) {
            if (dp2[y2]) {
                int y3 = 10 * y2 + d;
                if (y3 >= 0 && y3 < 1000) {
                    new_dp3[y3] = (new_dp3[y3] + dp2[y2]) % mod;
                }
            }
        }

        // From phase3: add year digit, compute Y = 10*y3 + d. If Y >=1, go to phase4 with y_mod400 = Y % 400
        for (int y3 = 0; y3 < 1000; y3++) {
            if (dp3[y3]) {
                int Y = 10 * y3 + d;
                if (Y >= 1) {
                    int y_mod400 = Y % 400;
                    new_dp4[y_mod400] = (new_dp4[y_mod400] + dp3[y3]) % mod;
                }
            }
        }

        // From phase4: start month if d is 0 or 1, go to phase5 with m1 = d
        for (int y_mod = 0; y_mod < 400; y_mod++) {
            if (dp4[y_mod]) {
                if (d == 0 || d == 1) {
                    new_dp5[y_mod][d] = (new_dp5[y_mod][d] + dp4[y_mod]) % mod;
                }
            }
        }

        // From phase5: add month digit, compute m = 10*m1 + d. If m in [1,12], go to phase6
        for (int y_mod = 0; y_mod < 400; y_mod++) {
            for (int m1 = 0; m1 < 2; m1++) {
                if (dp5[y_mod][m1]) {
                    int m_val = 10 * m1 + d;
                    if (m_val >= 1 && m_val <= 12) {
                        int m_idx = m_val - 1;
                        new_dp6[y_mod][m_idx] = (new_dp6[y_mod][m_idx] + dp5[y_mod][m1]) % mod;
                    }
                }
            }
        }

        // From phase6: start date if d is 0,1,2,3, go to phase7 with d1 = d
        for (int y_mod = 0; y_mod < 400; y_mod++) {
            for (int m_idx = 0; m_idx < 12; m_idx++) {
                if (dp6[y_mod][m_idx]) {
                    if (d >= 0 && d <= 3) {
                        new_dp7[y_mod][m_idx][d] = (new_dp7[y_mod][m_idx][d] + dp6[y_mod][m_idx]) % mod;
                    }
                }
            }
        }

        // From phase7: add date digit, compute full_d = 10*d1 + d, then check valid date (phase8)
        for (int y_mod = 0; y_mod < 400; y_mod++) {
            for (int m_idx = 0; m_idx < 12; m_idx++) {
                for (int d1 = 0; d1 < 4; d1++) {
                    if (dp7[y_mod][m_idx][d1]) {
                        int full_d = 10 * d1 + d;
                        int m_val = m_idx + 1;

                        // Check date validity
                        if (full_d < 1 || full_d > 31) continue;

                        int days;
                        if (m_val == 2) {
                            bool leap = is_leap_year(y_mod);
                            days = leap ? 29 : 28;
                        } else if (m_val == 4 || m_val == 6 || m_val == 9 || m_val == 11) {
                            days = 30;
                        } else {
                            days = 31;
                        }

                        if (full_d >= 1 && full_d <= days) {
                            ans = (ans + dp7[y_mod][m_idx][d1]) % mod;
                        }
                    }
                }
            }
        }

        // Update states for next character
        dp0 = new_dp0;
        dp1 = new_dp1;
        dp2 = new_dp2;
        dp3 = new_dp3;
        dp4 = new_dp4;
        dp5 = new_dp5;
        dp6 = new_dp6;
        dp7 = new_dp7;
    }

    cout << ans << endl;

    return 0;
}