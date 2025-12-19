#include <iostream>
#include <algorithm>
using namespace std;

#define int long long
int a[8];

bool check(int x) {
    int xxx = x - a[1];
    int A = a[1], B = a[2], C = a[4];
    int xx = a[3], yy = a[5], sum = a[6] + a[7];
    int z = a[7];

    if (B < C) {
        swap(B, C);
        swap(xx, yy);
    }
    int d = B - C;

    if (A >= x) {
        B += xx;
        C += yy;
        if (B < C) swap(B, C);
        d = B - C;
        if (d >= sum) {
            C += sum;
        } else {
            C += d;
            sum -= d;
            C += sum / 2;
            B += sum - sum / 2;
        }
        return B >= x && C >= x;
    } else {
        if (yy >= d) {
            if (xx < yy - d) {
                int cha = yy - xx - d;
                yy = xx + d;
                if (cha >= xxx) {
                    cha -= xxx;
                    yy += cha;
                } else {
                    xxx -= cha;
                    if (xx * 2 >= xxx) {
                        xx -= xxx / 2;
                        yy -= xxx - xxx / 2;
                    } else {
                        xxx -= xx * 2;
                        xx = 0;
                        yy = d;
                        if (xxx < z) {
                            z -= xxx;
                        } else {
                            xxx -= z;
                            z=0;//aaaaa
                            if (yy < xxx) return false;
                            yy -= xxx;
                        }
                    }
                }
            } else {
                int cha = xx - yy + d;
                xx = yy - d;
                if (cha >= xxx) {
                    cha -= xxx;
                    xx += cha;
                } else {
                    xxx -= cha;
                    if (xx * 2 >= xxx) {
                        xx -= xxx / 2;
                        yy -= xxx - xxx / 2;
                    } else {
                        xxx -= xx * 2;
                        xx = 0;
                        yy = d;
                        if (xxx < z) {
                            z -= xxx;
                        } else {
                            xxx -= z;
                            z=0;//aaaaa
                            if (yy < xxx) return false;
                            yy -= xxx;
                        }
                    }
                }
            }
        } else {
            if (xx >= xxx) {
                xx -= xxx;
            } else {
                xxx -= xx;
                xx = 0;
                if (xxx <= z) {
                    z -= xxx;
                } else {
                    xxx -= z;
                    z = 0;
                    if (yy < xxx) return false;
                    yy -= xxx;
                }
            }
        }

        B += xx;
        C += yy;
        sum = a[6] + z;
        if (B < C) swap(B, C);
        d = B - C;
        if (d >= sum) {
            C += sum;
        } else {
            C += d;
            sum -= d;
            C += sum / 2;
            B += sum - sum / 2;
        }
        return B >= x && C >= x;
    }
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= 7; i++) {
        cin >> a[i];
    }
    int l = min({a[1], a[2], a[4]});
    int r = min({a[1]+a[3]+a[5]+a[7],a[2]+a[3]+a[6]+a[7],a[4]+a[5]+a[6]+a[7],n/3}), ans = 0;
    

    // cout<<check(6188199);
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
/*
1
21222968
328927 9194079 1436492 2096116 7531954 287891 347509
*/