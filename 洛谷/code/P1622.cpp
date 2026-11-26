// https://www.luogu.com.cn/problem/P1622
// 题意：P 间牢房排成一列，开始都有人，给定 Q 人的释放名单。
// 每次释放一人，得给释放前与其处在同一连续占用区间的其他人各送一份，空牢房隔断区间。
// 任选释放顺序，求总份数的最小值。
// 数据范围：1 ≤ P ≤ 1000，1 ≤ Q ≤ min(P,100)，名单按房号递增给出。

#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[1000];
int f[1000][1000];

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+m+1); //排序，有序的才能转移状态
    a[0]=0;a[m+1]=n+1; //假设0和n+1号牢房有人，方便后面的状态转移
    for(int l=1;l<=m;l++)  //枚举区间长度
        for(int i=1;i+l-1<=m;i++) //区间左端点位置
        {
            int j=i+l-1;  //区间右端点位置
            f[i][j]=999999999;
            for(int k=i;k<=j;k++)  //枚举分界点
                f[i][j]=min(f[i][j],f[i][k-1]+f[k+1][j]+a[j+1]-a[i-1]-1-1); //状态转移
        }
    printf("%d",f[1][m]);
}
