// https://www.luogu.com.cn/problem/P2238
// 题意：H*W 网格（1~9 为价格，. 为未开张），从 (1,1) 只往东或南走到 (H,W)。
// 到达摊位若开张且未买过则买下，且其上下左右 r 个未买开张摊位中需买 r-1 个（不重复买）。
// 求最少花费的钱数。
// 数据范围：3 <= H, W <= 1000。
#include<bits/stdc++.h>
// 算法标签：状态压缩动态规划、动态规划
using namespace std;
const int MAXN = 1e3+5;
const int INF = 1e9;
const int LD = 1; // 左下
const int DN = 2; // 下
const int RT = 4; // 右
const int RU = 8; // 右上

int n,m;
int val[MAXN][MAXN];
int dp[MAXN][MAXN][16];
int bit[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
char s[MAXN];

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<16;k++){
                dp[i][j][k]=INF;
            }
        }
    }
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        for(int j=1;j<=m;j++){
            if(s[j]=='.'){
                val[i][j]=0;
            }
            else{
                val[i][j]=s[j]-'0';
            }
        }
    }

    dp[1][1][15]=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=0;k<16;k++){
                if(dp[i][j][k]==INF){
                    continue;
                }

                for(int k2=0;k2<16;k2++){
                    if(((k&RT)==0)!=((k2&RU)==0)){
                        continue;
                    }
                    if(!(k&DN)){
                        continue;
                    }
                    if(bit[k&LD]+bit[k2&(RT|DN)]<=1){
                        continue;
                    }
                    int cost=dp[i][j][k];
                    if(k2&LD){
                        cost+=val[i+2][j-1];
                    }
                    if(k2&DN){
                        cost+=val[i+2][j];
                    }
                    if(k2&RT){
                        cost+=val[i+1][j+1];
                    }
                    dp[i+1][j][k2]=min(dp[i+1][j][k2],cost);
                }

                for(int k2=0;k2<16;k2++){
                    if(((k&DN)==0)!=((k2&LD)==0)){
                        continue;
                    }
                    if(!(k&RT)){
                        continue;
                    }
                    if(bit[k&RU]+bit[k2&(RT|DN)]<=1){
                        continue;
                    }

                    int cost=dp[i][j][k];
                    if(k2&RU){
                        cost+=val[i-1][j+2];
                    }
                    if(k2&RT){
                        cost+=val[i][j+2];
                    }
                    if(k2&DN){
                        cost+=val[i+1][j+1];
                    }
                    dp[i][j+1][k2]=min(cost,dp[i][j+1][k2]);
                }
            }
        }
    }
    cout<<dp[n][m][15];
    return 0;
}