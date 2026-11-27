// https://www.luogu.com.cn/problem/P2879
// 题意：N 头牛排成一排，已知最高牛位置 I 和身高 H，以及 R 条 A 能看到 B 的关系。
// A 能看到 B 表示 B 身高 >= A，且 A, B 之间所有牛身高严格小于 A。
// 输出 N 行，每行表示每头牛的最大可能身高。
// 数据范围：1 <= N <= 10000，1 <= H <= 10^6，0 <= R <= 10000。
#include<bits/stdc++.h>
// 算法标签：模拟、去重

using namespace std;

struct node {
    int first;
    int second;
}h[10005];
int kdl[10005][10005];//这个用于去重
int n, f[10005], hest, r, t, a, b, c, d;

int main()
{
    scanf("%d%d%d%d", &n, &t, &hest, &r);
    for (int i = 1; i <= n; i++) {
        f[i] = hest;
    }
    for (int i = 1; i <= r; i++) {
        scanf("%d%d", &a, &b);
        h[i].first = min(a, b);
        h[i].second = max(a, b);//让这二者中小的赋给first，大的赋给second
        if (kdl[a][b] == 1)
            continue;
        kdl[a][b] = 1;//如果已经算过一次就跳过，没算过就标记并运算
        for(int j=h[i].first+1;j<h[i].second;j++)
            f[j]--;
    }//把中间所有牛的高度减一
    for(int i=1;i<=n;i++)
        printf("%d\n",f[i]);
    return 0;
}
