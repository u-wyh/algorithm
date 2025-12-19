// https://www.luogu.com.cn/problem/P3807
//卢卡斯定理模板题
#include<bits/stdc++.h>
using namespace std;

long long n,m,p;

long long power(long long a,long long b){
    long long ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%p;
        }
        a=(a*a)%p;
        b>>=1;
    }
    return ans;
}

long long comb(long long n,long long m){
    if(n<m){
        return 0;
    }
    m=min(m,n-m);
    long long a=1,b=1;
    for(int i=1;i<=m;i++){
        a=(a*(n-i+1))%p;
        b=(b*i)%p;
    }
    return a*power(b,p-2)%p;
}

long long lucas(int n,int m){
    if(m==0){
        return 1;
    }
    else{
        return lucas(n/p,m/p)*comb(n%p,m%p)%p;
    }
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>p;
        cout<<lucas(n+m,m)<<endl;
    }
    return 0;
}