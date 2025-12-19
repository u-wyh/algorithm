#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int n,p,v;
int f[MAXN];

signed main()
{
    cin>>n>>p>>v;
    f[0]=1;
    for(int i=1;i<=10000000;i++){
        for(int j=2;j<=(i-v)/p;j++){
            f[i]=max(f[i],f[i-v-p*j]*j);
        }
        if(f[i]>=n){
            cout<<i<<endl;
            return 0;
        }
    }
    return 0;
}