// https://www.luogu.com.cn/problem/P3147
// 题意：输入序列长度 N，以及 N 个正整数（2048 类一维合并，同 P3146 加强版）。
// 每次可选择两个相邻且相等的数，将其合并为一个比原数大 1 的数。
// 不断操作，求序列中能生成的最大整数。
// 输出一个整数表示最大整数。
// 数据范围：2 <= N <= 262144，初始每个数在 [1, 40] 之间。
#include<bits/stdc++.h>
// 算法标签：倍增、动态规划
using namespace std;
const int MAXN = 60;
const int MAXM = 262150;

int n;
int f[MAXN][MAXM];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
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
    n=read();
    for(int i=1;i<=n;i++){
        int u;
        u=read();
        f[u][i]=i+1;
    }
    int ans=0;
    for(int i=2;i<=log2(n)+40;i++){
        for(int j=1;j<=n;j++){
            if(!f[i][j]){
                f[i][j]=f[i-1][f[i-1][j]];
            }
            if(f[i][j]){
                ans=i;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
