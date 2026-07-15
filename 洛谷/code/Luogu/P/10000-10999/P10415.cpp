#include<bits/stdc++.h>
using namespace std;

int gcd(int a,int b){
    return (b==0)?a:gcd(b,a%b);
}

int isprime(int val){
    if(val==2){
        return 2;
    }
    for(int i=2;i*i<=val;i++){
        if(val%i==0){
            return i;
        }
    }
    return val;
}

int main()
{
    int a,b;
    cin>>a>>b;
    int c=gcd(a,b);
    if(c==1){
        if(a==b&&a!=1){
            cout<<1<<endl;
        }
        else{
            cout<<0<<endl;
        }
        return 0;
    }
    int d=isprime(c);
    long long ans=1ll*a*b/d/d;
    cout<<ans<<endl;

    return 0;
}