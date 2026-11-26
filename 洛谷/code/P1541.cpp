// https://www.luogu.com.cn/problem/P1541
// 题意：棋子从第 1 格开始，得到起点分数。每张卡只用一次，数值代表往前走的格数，每次只拿落点的分数。选卡的顺序可变，求到第 N 格时的最大总分。
// 数据范围：1 ≤ N ≤ 350，1 ≤ M ≤ 120，每种 1 至 4 的卡至多 40 张，0 ≤ a[i] ≤ 100，保证卡全部用完恰好到终点。

#include<bits/stdc++.h>
using namespace std;

int n,m;
int nums[355];
int a,b,c,d;
int dp[41][41][41][41];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=1;i<=m;i++){
        int t;
        cin>>t;
        if(t==1){
            a++;
        }else if(t==2){
            b++;
        }else if(t==3){
            c++;
        }else if(t==4){
            d++;
        }
    }
    dp[0][0][0][0]=nums[1];
    for(int i=0;i<=a;i++){
        for(int j=0;j<=b;j++){
            for(int u=0;u<=c;u++){
                for(int v=0;v<=d;v++){
                    int now=1+i+j*2+u*3+v*4;
                    if(i)
                        dp[i][j][u][v]=max(dp[i][j][u][v],dp[i-1][j][u][v]+nums[now]);
                    if(j)
                        dp[i][j][u][v]=max(dp[i][j][u][v],dp[i][j-1][u][v]+nums[now]);
                    if(u)
                        dp[i][j][u][v]=max(dp[i][j][u][v],dp[i][j][u-1][v]+nums[now]);
                    if(v)
                        dp[i][j][u][v]=max(dp[i][j][u][v],dp[i][j][u][v-1]+nums[now]);

                }
            }
        }
    }
    cout<<dp[a][b][c][d]<<endl;
    return 0;
}
