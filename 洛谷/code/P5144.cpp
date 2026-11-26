// https://www.luogu.com.cn/problem/P5144
// 题意：给定长为 N 的正整数序列 W，将其分割为恰好 M 个非空连续段，使每段按位异或和的总和最大，输出最大总和。
// 数据范围：1 <= N <= 1000，1 <= M <= 100，1 <= W_i <= 2^30-1，保证答案在 2^30-1 内。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 105;

int dp[MAXN][MAXM];
int arr[MAXN];
int n,m;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}


int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        arr[i]^=arr[i-1];
        dp[i][1]=arr[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=2;j<=m;j++){
            for(int k=1;k<=i;k++){
                dp[i][j]=max(dp[i][j],dp[k][j-1]+(arr[i]^arr[k]));
            }
        }
    }
    cout<<dp[n][m]<<endl;
    return 0;
}
