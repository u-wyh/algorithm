// https://www.luogu.com.cn/problem/P4139
// 题意：第一行输入数据组数 T，接下来 T 行每行输入一个正整数 p。
// 定义 a_0 = 1, a_n = 2^{a_{n-1}}，
// 求 b_n = a_n mod p 在充分大后收敛到的稳定值。
// 输出 T 行，每行一个正整数表示答案。
// 数据范围：T <= 10^3，p <= 10^7。
// 算法标签：扩展欧拉定理、欧拉筛、快速幂
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int phi[MAXN];
int pri[MAXN];
int len;
bool vis[MAXN];

void prepare(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            phi[i]=i-1;
            pri[++len]=i;
        }
        for(int j=1;j<=len&&(i*pri[j]<=n);j++){
            vis[i*pri[j]]=true;
            if(i%pri[j]==0){
                phi[i*pri[j]]=phi[i]*pri[j];
            }
            else{
                phi[i*pri[j]]=phi[i]*(pri[j]-1);
            }
        }
    }
}

int power(int a,int b,int p){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%p;
        }
        b>>=1;
        a=(a*a)%p;
    }
    return ans;
}

int solve(int p){
    if(p==1){
        return 0;
    }
    return power(2,solve(phi[p])+phi[p],p);
}

signed main()
{
    prepare(10000000);
    int T;
    cin>>T;
    while(T--){
        int p;
        cin>>p;
        cout<<solve(p)<<endl;
    }
    return 0;
}