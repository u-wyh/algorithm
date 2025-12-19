#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

long long power(long long a,int b){
    long long ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

int main()
{
    int a,b;
    cin>>a>>b;
    if(b>a){
        cout<<0;
        return 0;
    }
    if(a==b){
        cout<<1<<endl;
        return 0;
    }
    long long ans=power(2,a-b);
    long long tmp=1;
    for(int i=a-b+1;i<=a;i++){
        tmp=(tmp*i)%MOD;
    }
    ans=(ans*tmp)%MOD;
    tmp=1;
    for(int i=1;i<=b;i++){
        tmp=(tmp*i)%MOD;
    }
    ans=(ans*power(tmp,MOD-2)%MOD+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}