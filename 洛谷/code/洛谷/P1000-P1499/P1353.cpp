// https://www.luogu.com.cn/problem/P1353
// 题意：共 n 分钟，第 i 分钟跑步可前进 d[i] 米并增加 1 疲劳。
// 休息每分钟降 1，开始休息后必须降到 0 才能继续跑。
// 疲劳不能超过 m，起止时均为 0。
// 输出最远跑步距离。
// 数据范围：1 ≤ n ≤ 10^4，1 ≤ m ≤ 500，
// 1 ≤ d[i] ≤ 1000。
// 算法标签：动态规划

#include<iostream>
#include<cstdio>
using namespace std;

int f[10510][510], n, m, d[10010];

int main() {
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; ++i) {
        scanf("%d", &d[i]);
    }
    f[1][1]=d[1];
    for(int i=1; i<=n; ++i) {
        for(int j=0; j<=min(i, m); ++j) {
            if(j==0)
                f[i][0]=max(f[i-1][0], f[i][0]);
            else
                f[i+j][0]=max(f[i+j][0], f[i][j]);
            f[i+1][j+1]=max(f[i+1][j+1], f[i][j]+d[i+1]);
        }
    }
    printf("%d", f[n][0]);
    return 0;
}
