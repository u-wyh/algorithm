// https://www.luogu.com.cn/problem/P3757
// 题意：输入按键数 n 和一个长为 n-1、仅含 '<' 和 '>' 的字符串。
// 用 1..n 的排列 h_1..h_n 表示按键高度
// 字符串第 i-1 位（i=2..n）分别约束 h_{floor(i/2)} < h_i 或 h_{floor(i/2)} > h_i
// 求满足所有高度关系的排列总数。
// 输出方案数对 10^9+7 取模的结果。
// 数据范围：由说明/提示图片（5095.png）知 100% 数据满足 n <= 100。
#include<bits/stdc++.h>
// 算法标签：树形动态规划、组合数学、前缀和
using namespace std;
#define int long long
const int MAXN = 105;
const int MOD = 1e9+7;

int n;
char s[MAXN];
int sz[MAXN];
int f[MAXN][MAXN];
int temp[MAXN][MAXN];
int pre[MAXN];
int suf[MAXN];
int comb[MAXN][MAXN];

void compute(int x,int y){
    pre[0]=0;
    for(int i=1;i<=sz[y];i++){
        pre[i]=(pre[i-1]+f[y][i])%MOD;
    }
    suf[sz[y]+1]=0;
    for(int i=sz[y];i>=1;i--){
        suf[i]=(suf[i+1]+f[y][i])%MOD;
    }
    for(int i=1;i<=sz[x]+sz[y];i++){
        temp[x][i]=0;
    }
    for(int i=1;i<=sz[x];i++){
        for(int j=0;j<=sz[y];j++){
            long long tmp;
            if(s[y]=='<'){
                tmp=pre[j];
            }
            else{
                tmp=suf[j+1];
            }
            tmp=(tmp*f[x][i])%MOD;
            tmp=(tmp*comb[i+j-1][i-1])%MOD;
            tmp=(tmp*comb[sz[x]+sz[y]-i-j][sz[x]-i])%MOD;
            temp[x][i+j]=(temp[x][i+j]+tmp)%MOD;
        }
    }
    sz[x]+=sz[y];
    for(int i=1;i<=sz[x]+sz[y];i++){
        f[x][i]=temp[x][i];
    }
}

void dfs(int u){
    sz[u]=1;
    f[u][1]=1;

    if(u*2<=n){
        dfs(u*2);
        compute(u,2*u);
    }
    if(u*2+1<=n){
        dfs(u*2+1);
        compute(u,2*u+1);
    }
}

signed main()
{
    scanf("%lld %s",&n,s+2);
    for(int i=0;i<=n;i++){
        comb[i][0]=1;
        for(int j=1;j<=i;j++){
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%MOD;
        }
    }
    dfs(1);
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=(ans+f[1][i])%MOD;
    }
    cout<<ans<<endl;
    return 0;
}