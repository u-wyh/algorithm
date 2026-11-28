// https://www.luogu.com.cn/problem/P2516
// 题意：给定两个以 . 结尾的大写字母序列。
// 第一行输出它们的最长公共子序列长度。
// 第二行输出最长公共子序列的个数对 10^8 取模的结果。
// 数据范围：每个序列大写字母个数 <= 5000。
// 难度评分：1700（洛谷分级换算）
// 算法标签：动态规划、滚动数组、容斥原理
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e8;
const int MAXN = 5005;

int n,m;
char s1[MAXN],s2[MAXN];
int f[MAXN][2],g[MAXN][2];

signed main()
{
    scanf("%s",s1+1);
    scanf("%s",s2+1);
    n=strlen(s1+1)-1,m=strlen(s2+1)-1;
    for(int i=0;i<=m;i++){
        f[i][0]=0;
        g[i][0]=1;
    }
    for(int i=1;i<=n;i++){
        int now=i%2;
        f[0][now]=0,g[0][now]=1;
        for(int j=1;j<=m;j++){
            if(s1[i]==s2[j]){
                f[j][now]=f[j-1][now^1]+1;
                g[j][now]=g[j-1][now^1];

                if(f[j][now]==f[j-1][now]){
                    g[j][now]+=g[j-1][now];
                }
                if(f[j][now]==f[j][now^1]){
                    g[j][now]+=g[j][now^1];
                }
            }
            else{
                f[j][now]=max(f[j-1][now],f[j][now^1]);
                g[j][now]=0;

                if(f[j][now]==f[j-1][now]){
                    g[j][now]+=g[j-1][now];
                }
                if(f[j][now]==f[j][now^1]){
                    g[j][now]+=g[j][now^1];
                }

                if(f[j][now]==f[j-1][now^1]){
                    g[j][now]-=g[j-1][now^1];
                }
                g[j][now]=(g[j][now]%MOD+MOD)%MOD;
            }
            
        }
    }
    cout<<f[m][n%2]<<endl<<g[m][n%2]<<endl;
    return 0;
}