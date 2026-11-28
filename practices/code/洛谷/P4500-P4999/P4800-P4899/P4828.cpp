// https://www.luogu.com.cn/problem/P4828
// 题意：给定长为 n 的序列 a，
// 每次操作把每个 a_i 变为 a_i + a_{(i mod n)+1}
// 有 Q 次询问第 x 次操作后位置 y
// 的元素值（对 998244353 取模）。
// 数据范围：1 <= n <= 10^6，1 <= a_i <= 10^9，
// 1 <= x <= 2000，1 <= Q <= 10^4。
// 难度评分：1800（洛谷分级换算）
// 算法标签：组合数学、递推
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
const int MAXM = 2005;
const int MAXN = 1e6+5;

int n,q;
int nums[MAXN];
int comb[MAXM][MAXM];

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

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    for(int i=0;i<=2001;i++){
        comb[i][0]=comb[i][i]=1;
        for(int j=1;j<i;j++){
            comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%MOD;
        }
    }
    q=read();
    while(q--){
        int x,y;
        x=read(),y=read();
        int ans=0;
        for(int i=0;i<=x;i++){
            ans=(ans+comb[x][i]*nums[(y+i-1)%n+1])%MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}