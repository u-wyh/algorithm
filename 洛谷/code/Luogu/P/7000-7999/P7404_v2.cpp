#include<bits/stdc++.h>
using namespace std;
const int N=200010;

int a[N],b[N];
long long x[N],y[N];

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i]-a[i-1];
    }
    for(int i=2,j=n;i<=n;i++,j--){
        x[i]=(b[i]<=0?x[i-1]-(b[i]-1):x[i-1]);
        y[j]=(b[j]>=0?y[j+1]+(b[j]+1):y[j+1]);
    }
    long long ans=LONG_LONG_MAX;
    for(int i=1;i<=n;i++)
        ans=min(ans,max(x[i],y[i+1]));
    cout<<ans;
    return 0;
}
