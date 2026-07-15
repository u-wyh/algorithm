#include<bits/stdc++.h>
using namespace std;
#define int long long

int n,a,b,c,d,mod;
int a1,a2,a3;

int f(int x){
    int ans=((((a*x%mod*x%mod*x%mod+b*x%mod*x%mod)%mod+c*x%mod)%mod+d)%mod+mod)%mod;
    return ans;
}

signed main()
{
    cin>>n>>a>>b>>c>>d>>a2>>mod;
    a1=0;
    int maxx=a2;
    int ans=0;
    n--;
    while(n--){
        a3=((f(a1)+f(a2))%mod+mod)%mod;
        if(maxx>a3){
            ans=max(ans,maxx-a3);
        }
        else{
            maxx=a3;
        }
        a1=a2;
        a2=a3;
    }
    cout<<(ans+1)/2<<endl;
    return 0;
}