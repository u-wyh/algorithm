// https://www.luogu.com.cn/problem/P5839
// 题意：给定长为 N、字符集为前 M 个小写字母的串 S 及字符单点修改代价矩阵
// a_{ij}（允许中转多次修改）
// 求将 S 改为由若干长度至少为 K 的同字符连续段拼接而成的最小总代价。
// 输入 N, M, K、串 S 及代价矩阵 a；输出最小总天数。
// 数据范围：1 <= M <= 26，1 <= K <= N <= 10^5，
// 0 <= a_{ij} <= 1000。
// 难度评分：1800（洛谷分级换算）
// 算法标签：动态规划、Floyd、前缀和
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m,k;
char s[MAXN];
int nums[MAXN];
int dis[27][27];
int sum[MAXN][27];
int tmp[27];
int f[MAXN];

void floyd(){
    for(int k=1;k<=m;k++){
        for(int i=1;i<=m;i++){
            for(int j=1;j<=m;j++){
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }
}

int main()
{
    cin>>n>>m>>k;
    scanf("%s",s+1);
    for(int i=1;i<=n;i++){
        nums[i]=s[i]-'a'+1;
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            cin>>dis[i][j];
        }
    }
    floyd();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            sum[i][j]=sum[i-1][j]+dis[nums[i]][j];
        }
    }
    for(int i=1;i<=n;i++){
        f[i]=INT_MAX;
    }
    for(int i=1;i<=26;i++){
        tmp[i]=0;
    }

    for(int i=k;i<=n;i++){
        if(i>=2*k){
            for(int j=1;j<=m;j++){
                tmp[j]=min(tmp[j],f[i-k]-sum[i-k][j]);
            }
        }
        for(int j=1;j<=m;j++){
            f[i]=min(f[i],sum[i][j]+tmp[j]);
        }
    }

    cout<<f[n]<<endl;
    return 0;
}