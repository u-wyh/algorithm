#include<bits/stdc++.h>
using namespace std;

long long power(long long a,long long b,int mod){
    long long ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%mod;
        }
        a=(a*a)%mod;
        b>>=1;
    }
    return ans;
}

int geteuler(int tmp){
    int n=1;
    for(int i=2;i*i<=tmp;i++){
        if(tmp%i){
            continue;
        }
        n*=(i-1);
        tmp/=i;
        while(tmp%i==0){
            tmp/=i;
            n*=i;
        }
    }
    if(tmp>1){
        n*=(tmp-1);
    }
    return n;
}

int compute(int u,int mod){
    if(u==2023){
        return u;
    }
    return power(u,compute(u+1,geteuler(mod))+geteuler(mod),mod);
}

int main()
{
    cout<<compute(2,2023);
    return 0;
}