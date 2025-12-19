#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int n,k,t;
int arr[MAXN];
int tmp[MAXN];

bool check(int m){
    for(int i=1;i<=m;i++){
        tmp[i]=arr[i];
    }
    sort(tmp+1,tmp+m+1);
    int sum=0;
    int squ=0;
    for(int i=1;i<k;i++){
        sum+=tmp[i];
        squ+=(tmp[i]*tmp[i]);
    }
    for(int i=k;i<=m;i++){
        sum+=tmp[i],sum-=tmp[i-k];
        squ+=(tmp[i]*tmp[i]),squ-=(tmp[i-k]*tmp[i-k]);
        if((1.0*squ)<=(t+(sum*1.0)*(sum*1.0)/k))
            return true;
    }
    return false;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>k>>t;
    t*=k;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    int l=k,r=n,ans=-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}