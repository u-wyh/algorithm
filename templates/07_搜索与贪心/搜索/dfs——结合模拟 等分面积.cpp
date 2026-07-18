//P4160
//首先我们假设当前的矩形长为x，宽为y，要分出k块，
//那么不难想到分出的一块的长mx最短为x/k，宽my最短为y/k，
//而且每次切的长度一定是mx的倍数或my的倍数
//因为每次只能和边沿平行的切  还要切成两块  所以
#include<bits/stdc++.h>
using namespace std;

int n;
double x, y;

double dfs(double x, double y, int k) {
    //目前的蛋糕 长为x 宽为y 要分成k份
    if (k == 1) {
        //一块蛋糕 不用再切
        return max(x, y) / min(x, y);
    }
    double ans = 1e9, mx = x * 1.0 / k, my = y * 1.0 / k, t1, t2;//mx my是最小长  最小宽
    for (int i = 1; i <= k / 2; i++) {
        t1 = max(dfs(mx * i, y, i), dfs(x - mx * i, y, k - i));
        t2 = max(dfs(x, my * i, i), dfs(x, y - my * i, k - i));
        ans = min(ans, min(t1, t2));
    }
    return ans;
}

int main() {
    cin >> x >> y >> n;
    // 设置输出精度为6位小数
    cout << fixed << setprecision(6) << dfs(x, y, n) << endl;
    return 0;
}

