// https://www.luogu.com.cn/problem/P1419
// 题意：给 n 个整数，选一段连续区间，要求长度在 [S,T]。求区间平均值的最大值，输出保留三位小数。
// 数据范围：1 ≤ S ≤ T ≤ n ≤ 10^5，-10000 ≤ a[i] ≤ 10000。
// 算法标签：二分答案、单调队列、前缀和

#include <bits/stdc++.h>
#define maxn 100010

using namespace std;

int n, s, t, i;
double l, r, mid, ans;
double a[maxn];
int b[maxn];
double sum[maxn];
int q[maxn];

bool check(double x) {
    int i, l = 1, r = 0;
    for (i = 1; i <= n; i++)
        a[i] = (double)b[i] - x;
    sum[0] = 0;
    for (i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + a[i];
    for (i = 1; i <= n; i++) {
        if (i >= s) {
            while (r >= l && sum[i - s] < sum[q[r]])
                r--;
            q[++r] = i - s;
        }
        if (l <= r && q[l] < i - t)
            l++;
        if (l <= r && sum[i] - sum[q[l]] >= 0)
            return true;
    }
    return false;
}

int main()
{
    cin>>n>>s>>t;
    for (i = 1; i <= n; i++)
        cin>>b[i];
    ans = l = -10000;
    r = 10000;
    while (r - l > 1e-5) {
        mid = (l + r) / 2;
        if (check(mid))
            ans = l = mid;
        else
            r = mid;
    }

    printf("%.3lf\n", ans);
    return 0;
}

