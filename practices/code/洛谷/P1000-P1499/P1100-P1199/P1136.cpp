// https://www.luogu.com.cn/problem/P1136
// 题意：给只含 j 和 z 的字符串。至多交换 K 次，每次可交换任意两处。
// 求最终相邻子串 jz 的最多出现次数。
// 数据范围：1 ≤ N ≤ 500，1 ≤ K ≤ 100。
// 难度评分：1800（洛谷分级换算）
// 算法标签：动态规划

#include<bits/stdc++.h>
using namespace std;
const int maxn=505,maxk=105;
int n,m,f[maxn][maxk][maxk][3];
char s[maxn];
int main(){
    scanf("%d%d%s",&n,&m,s+1);
    memset(f,128,sizeof(f));
    f[0][0][0][1]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=m;k++){
                if(s[i]=='z'){
                    f[i][j][k][1]=max(f[i-1][j][k][0]+1,f[i-1][j][k][1]);
                    if(k) f[i][j][k][0]=max(f[i-1][j][k-1][0],f[i-1][j][k-1][1]);
                } else {
                    f[i][j][k][0]=max(f[i-1][j][k][0],f[i-1][j][k][1]);
                    if(j) f[i][j][k][1]=max(f[i-1][j-1][k][0]+1,f[i-1][j-1][k][1]);
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<=m;i++){
        ans=max(ans,max(f[n][i][i][1],f[n][i][i][0]));
    }
    printf("%d\n",ans);
    return 0;
}

