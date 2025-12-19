#include<bits/stdc++.h>
using namespace std;

int n,sum,ans;
int arr[20005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        sum+=arr[i];
        ans=max(arr[i]+arr[i-1],ans);
    }
    if(n==1){
        cout<<arr[1]<<endl;
        return 0;
    }
    ans=max(ans,arr[1]+arr[n]);
    ans=max(ans,(sum+n/2-1)/(n/2));
    cout<<ans<<endl;
    return 0;
}
