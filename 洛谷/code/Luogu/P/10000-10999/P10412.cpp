#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;

int arr[MAXN];
int n,p,q,r;
int sum=0;

signed main()
{
    cin>>n>>p>>q>>r;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        sum+=arr[i];
    }
    //cout<<sum<<endl;
    if(sum>=0){
        cout<<0<<endl;
        return 0;
    }
    sort(arr+1,arr+n+1);
    int ans=0,cnt=1,used=0;
    while(sum<0){
        if(sum-arr[cnt]<0&&used<n-1){
            //说明还是不行
            if(q<(-arr[cnt])*p){
                used++;
            }
            ans+=min(q,(-arr[cnt])*p);
            sum-=arr[cnt];
            cnt++;
        }
        else if(used<n-1){
            if(q<(-sum)*p){
                used++;
            }
            ans+=min(q,(-sum)*p);
            sum=0;
        }
        else{
            ans+=p*(-sum);
            sum=0;
        }
    }
    cout<<ans<<endl;
    return 0;
}
