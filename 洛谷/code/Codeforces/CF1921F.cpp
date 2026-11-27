// https://codeforces.com/problemset/problem/1921/F
// 题意：每组给长为 n 的序列 a 和 q 次询问。
// 每次从下标 s 起间隔 d 取 k 项，依次乘 1 到 k。
// 输出：每组一行，按询问顺序输出各次加权和。
// 数据范围：1 <= t <= 10^4，1 <= n <= 10^5，
// 1 <= q <= 2*10^5，-10^8 <= a_i <= 10^8。
// 1 <= s, d, k <= n，s+d*(k-1) <= n。
// 所有组的 n 之和至多 10^5，q 之和至多 2*10^5。
// 算法标签：根号分治、前缀和
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 405;

int n,q;
int blen;
int nums[MAXN];
long long f[MAXB][MAXN];
long long g[MAXB][MAXN];

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

void prepare(){
    blen=sqrt(n);
    for(int d=1;d<=blen;d++){
        for(int i=n;i>=1;i--){
            f[d][i]=(i+d>n?0:f[d][i+d])+nums[i];
        }
    }
    for(int d=1;d<=blen;d++){
        for(int i=n;i>=1;i--){
            g[d][i]=(i+d>n?0:g[d][i+d])+f[d][i];
        }
    }
}

long long query(int s,int d,int k){
    long long ans=0;
    if(d>blen){
        for(int i=1;i<=k;i++){
            ans+=1ll*nums[s+(i-1)*d]*i;
        }
    }
    else{
        ans=g[d][s];
        if(s+d*k<=n)
            ans-=g[d][s+d*k]+f[d][s+d*k]*k;
    }
    return ans;
}

int main()
{
    int T=read();
    while(T--){
        n=read(),q=read();
        for(int i=1;i<=n;i++){
            nums[i]=read();
        }
        prepare();
        while(q--){
            int s,d,k;
            s=read(),d=read(),k=read();
            cout<<query(s,d,k)<<endl;
        }
    }
    return 0;
}