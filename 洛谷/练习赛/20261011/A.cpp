#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e5+5;
const int INF = 1e18;

int n,k;
int val[MAXN];
int sum[MAXN];

signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        val[i+n]=val[i];
    }
    for(int i=1;i<=2*n;i++){
        sum[i]=sum[i-1]+val[i];
    }

    int ans=-INF;
    int pos=0;
    for(int i=1;i<=n;i++){
        int res=sum[i+k-1]-sum[i-1];
        if(res>ans){
            ans=res;
            pos=i;
        }
    }
    cout<<ans<<endl<<pos<<endl;
    return 0;
}