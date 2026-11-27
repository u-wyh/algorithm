// https://www.luogu.com.cn/problem/P4140
// 题意：共 100000 个国家银行，初始存款均为 3；
// 第一行输入操作数 x，接下来 x 行每行三个整数 a_i, b_i, c_i。
// a_i = 0 时
// 求区间 [b_i, c_i] 各银行存款乘积 product 在
// [1, product]
// 中与其互质的整数个数（即欧拉函数 phi(product)）；
// a_i = 1 时将银行 b_i 的存款改为
// c_i（保证只含前 60 个质数的乘积）。
// 对每个 a_i = 0 的询问输出一行结果，对 19961993 取模。
// 数据范围：1 <= x <= 10^5，
// 0 <= c_i - b_i <= 10^5，
// 任意时刻单家银行存款 <= 10^6
// 仅含前 60 个素因子（2..281）。
// 算法标签：树状数组、欧拉函数、快速幂
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 19961993;
const int MAXN = 1e5+5;

int n,m;

int tree[61][MAXN];
// int p[61][61];
int prime[61]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,
            139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281};
int val[MAXN];

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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int y,int v){
    while(y<=n){
        tree[x][y]+=v;
        y+=lowbit(y);
    }
}

int sum(int x,int y){
    int ans=0;
    while(y){
        ans+=tree[x][y];
        y-=lowbit(y);
    }
    return ans;
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        a=(a*a)%MOD;
        b>>=1;
    }
    return ans;
}

signed main()
{
    n=100000;
    m=read();
    for(int i=1;i<=n;i++){
        val[i]=3;
        add(2,i,1);
    }
    // for(int i=1;i<=60;i++){
    //     p[i][0]=p[i][1]=1;
    //     for(int j=2;j<=60;j++){
    //         p[i][j]=(p[i][j-1]*prime[i])%MOD;
    //     }
    //     for(int j=1;j<=60;j++){
    //         p[i][j]=(p[i][j]*(prime[i]-1))%MOD;
    //     }
    // }
    while(m--){
        int op,u,v;
        op=read(),u=read(),v=read();
        if(op==0){
            int ans=1;
            for(int i=1;i<=60;i++){
                int k=sum(i,v)-sum(i,u-1);
                if(k>0)
                    ans=(ans*power(prime[i],k-1)%MOD*(prime[i]-1))%MOD;
            }
            cout<<ans<<endl;
        }
        else{
            int tmp=val[u];
            for(int i=1;i<=60;i++){
                int k=0;
                while(tmp%prime[i]==0){
                    k++;
                    tmp/=prime[i];
                }
                if(k){
                    add(i,u,-k);
                }
            }
            val[u]=v;
            for(int i=1;i<=60;i++){
                int k=0;
                while(v%prime[i]==0){
                    k++;
                    v/=prime[i];
                }
                if(k){
                    add(i,u,k);
                }
            }
        }
    }
    return 0;
}