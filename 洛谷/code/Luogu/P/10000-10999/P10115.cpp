#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+5,inf=1e18;
int n,a[N],lst[N],r;
int f[N],st[N],c[N];
bool b[N];
string S;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>S;
    for(int i=1; i<=n; ++i)
        cin>>a[i],b[i]=(S[i-1]=='(');
    for(int i=1; i<=n; ++i)
        if(!b[i]&&r)lst[i]=st[r--];
        else if(b[i])st[++r]=i;
    for(int i=0; i<=n; ++i)
        f[i]=c[i]=-inf;f[0]=0;
    for(int i=1; i<=n; ++i){
        f[i]=f[i-1];
        if(lst[i]){
            c[i]=max(c[lst[i]-1],f[lst[i]-1]-a[lst[i]]);
            f[i]=max(c[i]+a[i],f[i]);
        }
    }cout<<f[n];
    return 0;
}
