// https://www.luogu.com.cn/problem/P10111
// 题意：有 N 轮，已知对手每轮出的牌 c[i]。
// 牌 1 赢 0、2 赢 1、0 赢 2，
// 第 i 轮赢、平、输分别得 2a[i]、a[i]、0 分。
// 若一共换牌 t 次，再扣前 t 个 b 的和。
// 求最高净得分。
// 数据范围：1 ≤ N ≤ 1000，
// 0 ≤ a[i], b[i] ≤ 10^6，c[i] 只能是 0、1、2。
// 算法标签：动态规划、前缀和

#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int max(int a,int b)
{
    return a>b?a:b;
}

long long ll_max(long long a,long long b)
{
    return a>b?a:b;
}

ll n;
ll a[1005];
ll sumb[1005];
//sumb是扣分项的前缀和  表示换了i次会扣多少分
ll d[1005];
ll f[1005][3][1005];
//动态规划  f[i][j][k]表示第i轮出j  且已经更改过k次最大得分

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    sumb[0] = 0;
    for (int i = 1; i < n; i++)
    {
        scanf("%lld", &sumb[i]);
        sumb[i] += sumb[i - 1];
    }
    for (int i = 1; i <= n; i++)
        scanf("%lld", &d[i]);

    for (int i = 1; i <= n; i++) {
        for (int k = 0; k < i; k++) {
            if (k == 0) {
                if (d[i] == 0) {
                    f[i][0][k] = f[i - 1][0][k] + a[i];
                    f[i][1][k] = f[i - 1][1][k] + 2 * a[i];
                    f[i][2][k] = f[i - 1][2][k];
                } else if (d[i] == 1) {
                    f[i][0][k] = f[i - 1][0][k];
                    f[i][1][k] = f[i - 1][1][k] + a[i];
                    f[i][2][k] = f[i - 1][2][k] + 2 * a[i];
                } else {
                    f[i][0][k] = f[i - 1][0][k] + 2 * a[i];
                    f[i][1][k] = f[i - 1][1][k];
                    f[i][2][k] = f[i - 1][2][k] + a[i];
                }
            } else {
                if (d[i] == 0) {
                    f[i][0][k] = ll_max(f[i - 1][0][k],
                        ll_max(f[i - 1][1][k - 1],
                        f[i - 1][2][k - 1])) + a[i];

                    f[i][1][k] = ll_max(f[i - 1][0][k - 1],
                        ll_max(f[i - 1][1][k],
                        f[i - 1][2][k - 1])) + 2 * a[i];

                    f[i][2][k] = ll_max(f[i - 1][0][k - 1],
                        ll_max(f[i - 1][1][k - 1],
                        f[i - 1][2][k]));
                } else if (d[i] == 1) {
                    f[i][0][k] = ll_max(f[i - 1][0][k],
                        ll_max(f[i - 1][1][k - 1],
                        f[i - 1][2][k - 1]));

                    f[i][1][k] = ll_max(f[i - 1][0][k - 1],
                        ll_max(f[i - 1][1][k],
                        f[i - 1][2][k - 1])) + a[i];

                    f[i][2][k] = ll_max(f[i - 1][0][k - 1],
                        ll_max(f[i - 1][1][k - 1],
                        f[i - 1][2][k])) + 2*a[i];
                }else
                {
                    f[i][0][k] = ll_max(f[i - 1][0][k],
                        ll_max(f[i - 1][1][k - 1],
                        f[i - 1][2][k-1])) + 2*a[i];

                    f[i][1][k] = ll_max(f[i - 1][0][k - 1],
                        ll_max(f[i - 1][1][k],
                        f[i - 1][2][k - 1])) ;

                    f[i][2][k] = ll_max(f[i - 1][0][k - 1],
                        ll_max(f[i - 1][1][k - 1],
                        f[i - 1][2][k]))+a[i];
                }
            }
        }
    }
    ll ans = 0;
	for (int k = 0; k < n; k ++) {
		for (int j = 0; j < 3; j ++) {
			ans = max(ans, f[n][j][k] - sumb[k]);
		}
	}
	printf("%lld\n",ans);
    return 0;
}
