// https://www.luogu.com.cn/problem/P3118
// 题意：输入电影部数 N、目标总时长 L，以及每部电影的片长 D、场次数 C 和各场次的开始时间（放映区间 [t, t+D]）。
// 贝西可以在放映期间随时入场或离场，但每部电影最多看一场且全程时间 [0, L] 不能有空档。
// 求覆盖 [0, L] 最少需要看几部电影；若无法全程覆盖则输出 -1。
// 输出一个整数表示最少电影数或 -1。
// 数据范围：1 <= N <= 20，1 <= L <= 10^8，1 <= D <= L，1 <= C <= 1000
// 开始时间在 [0, L] 内且升序互异。
#include <bits/stdc++.h>
// 算法标签：状态压缩动态规划、二分查找
using namespace std;

int n, m, d[25], a[25][1005];
int cnt[1<<20], f[1 << 20];

int main()
{
    cin>>n>>m;
    for (int i = 0; i < n; i++){
        cin>>d[i]>>a[i][0];
        for (int j = 1; j <= a[i][0]; j++)
            cin>>a[i][j];
    }

    cnt[0]=0;
    for(int i=1;i<(1<<n);i++){
        int k=i&-i;
        cnt[i]=cnt[i^k]+1;
    }

    int ans = 1e9;
    memset(f,-1,sizeof(f));
    f[0] = 0;
    for (int i = 0; i < (1<<n); i++){
        for (int j = 0; j < n; j++){
            if (i & (1 << j))
                continue;
            int p = upper_bound(a[j] + 1, a[j] + a[j][0] + 1, f[i]) - a[j];
            if (p > 1)
                f[i | (1 << j)] = max(f[i | (1 << j)], a[j][p - 1] + d[j]);
            else
                f[i | (1 << j)] = f[i];
        }
        if (f[i] >= m)
            ans = min(ans, cnt[i]);
    }
    if (ans == 1e9)
        printf("-1");
    else
        printf("%d", ans);
    return 0;
}
