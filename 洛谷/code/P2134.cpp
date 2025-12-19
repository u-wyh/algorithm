#include<bits/stdc++.h>
using namespace std;

int n,p,q;
long long ans=LLONG_MAX;

long long compute(int a,int b){
    int x=a/b;
    int y=a%b;
    return 1ll*(b-y)*p*x*x+1ll*p*y*(x+1)*(x+1);
    //一定会有y次是x+1天连续的
}

int main()
{
    cin>>n>>p>>q;
    for(int i=0;i<=n;i++){
        ans=min(ans,1ll*i*q+compute(n-i,i+1));
    }
    cout<<ans<<endl;
    return 0;
}
