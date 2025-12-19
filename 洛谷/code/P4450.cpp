#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int f[MAXN];

signed main()
{
    int a,b,d;
    cin>>a>>b>>d;
    if(d>min(a,b)){
        cout<<0<<endl;
        return 0;
    }
    a=(a/d),b=(b/d);
    int k=min(a,b);
    for(int i=k;i>=1;i--){
        f[i]=(a/i)*(b/i);
        for(int j=2;j<=k/i;j++){
            f[i]-=f[j*i];
        }
    }
    cout<<f[1]<<endl;
    return 0;
}