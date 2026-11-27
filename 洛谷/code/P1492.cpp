// https://www.luogu.com.cn/problem/P1492
// 题意：从矩形格网的左下角走到右上角，每一步只能沿格线向上或向右。求不同路径数，只输出十进制末尾 100 位，不足补前导零，并每行输出十位。
// 数据范围：m,n 均不超过 50000，输出固定为 10 行。
// 算法标签：组合数学、线性筛、快速幂

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

int prime[MAXN];
int cnt;
int num[MAXN];
int counts[MAXN];

void prepare(int n){
    for(int i=2;i<=n;i++){
        if(!num[i]){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&prime[j]*i<=n;j++){
            num[i*prime[j]]=prime[j];
            if(i%prime[j]==0){
                break;
            }
        }
    }
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans*=a;
        }
        b>>=1;
        a*=a;
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    prepare(n+m);
    if(n>m){
        swap(n,m);
    }
    for(int i=2;i<=n;i++){
        counts[i]=-1;
    }
    for(int i=n+m;i>m;i--){
        counts[i]=1;
    }
    for(int i=n+m;i>=2;i--){
        if(num[i]!=0){
            counts[num[i]]+=counts[i];
            counts[i/num[i]]+=counts[i];
            counts[i]=0;
        }
    }
    int ans=1;
    for(int i=1;i<=cnt;i++){
        ans=ans*power(prime[i],counts[prime[i]]);
    }
    cout<<ans<<endl;
    return 0;
}