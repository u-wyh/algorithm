// https://www.luogu.com.cn/problem/P7976
// 题意：定义 F(x) = ((x + 1) mod 3) - 1。
// 多组询问，每次给定 n，求 ∑_{l=0}^n ∑_{r=l}^n F(C_r^l) 对 1732073999 取模的结果（其中 C_r^l 为组合数）。
// 第一行输入 t, maxn（询问组数与询问的最大可能值），接下来 t 行每行一个正整数 n。
// 输出 t 行每行一个整数。
// 数据范围：1 <= t <= 3*10^4，1 <= n <= maxn <= 2*10^{16}。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1732073999;
const int MAXL = 40;

int n;
int p[MAXL];
int f[MAXL][MAXL][2];
int nums[MAXL];
int len;

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

int dfs(int x,int now,int free){
    if(x==0){
        return p[now];
    }
    if(f[x][now][free]!=-1){
        return f[x][now][free];
    }
    int ans=0;
    int up=free?2:nums[x];
    for(int d=0;d<=up;d++){
        ans=(ans+dfs(x-1,now+(d==1),free||(d<nums[x])))%MOD;
    }
    f[x][now][free]=ans;
    return ans;
}

signed main()
{
    int T;
    T=read(),n=read();
    p[0]=1;
    for(int i=1;i<MAXL;i++){
        p[i]=(p[i-1]*2)%MOD;
    }
    while(T--){
        n=read();
        len=0;
        int m=n;
        while(m){
            nums[++len]=m%3;
            m/=3;
        }
        for(int i=1;i<=len;i++){
            for(int j=0;j<=len;j++){
                f[i][j][0]=-1;
                f[i][j][1]=-1;
            }
        }
        cout<<dfs(len,0,0)<<endl;
    }
    return 0;
}