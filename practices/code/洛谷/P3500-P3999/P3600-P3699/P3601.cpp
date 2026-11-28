// https://www.luogu.com.cn/problem/P3601
// 题意：输入两个正整数 l 和 r。
// 定义 qiandao(x) 为 1 到 x 中与 x 不互质的整数个数
// 求 sum_{i=l..r} qiandao(i) 对 666623333
// 取模的值。
// 输出一行一个整数表示答案。
// 数据范围：1 <= l <= r <= 10^12，r - l <= 10^6。
// 难度评分：1800（洛谷分级换算）
// 算法标签：欧拉函数、线性筛、区间筛
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 666623333;
const int MAXN = 1e6+5;

int l,r;

int cnt;
int prime[MAXN];
bool vis[MAXN];

int phi[MAXN];
int val[MAXN];

void prepare(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&prime[j]*i<=n;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

signed main()
{
    cin>>l>>r;
    int n=ceil(sqrt(r));
    int len=r-l+1;
    prepare(n);
    for(int i=1;i<=len;i++){
        val[i]=i+l-1;
        phi[i]=i+l-1;
    }

    for(int i=1;i<=cnt;i++){
        int p=prime[i];
        int st=(l+p-1)/p*p;
        for(int j=st;j<=r;j+=p){
            int pos=j-l+1;
            val[pos]/=p;
            while(val[pos]%p==0){
                val[pos]/=p;
            }
            phi[pos]=phi[pos]/p*(p-1);
        }
    }
    for(int i=1;i<=len;i++){
        if(val[i]>1){
            phi[i]=phi[i]/val[i]*(val[i]-1);
        }
        phi[i]%=MOD;
    }
    int ans=0;
    for(int i=1;i<=len;i++){
        ans=(ans+i+l-1-phi[i])%MOD;
    }
    ans=(ans+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}