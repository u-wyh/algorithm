#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n,mod;
int arr[MAXN];
int f[MAXN];
int score[MAXN];
int ans=INT_MIN;

signed main()
{
    cin>>n>>mod;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    if(n==1){
        cout<<arr[1]<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++){
        f[i]=max(f[i-1],(long long)0)+arr[i];
    }
    for(int i=2;i<=n;i++){
        f[i]=max(f[i],f[i-1]);
    }
    score[1]=f[1];
    ans=score[1]+f[1];
    //cout<<score[1]<<' '<<ans<<endl;
    for(int i=2;i<n;i++){
        score[i]=ans;
        ans=max(score[i]+f[i],ans);
        //cout<<score[i]<<' '<<ans<<endl;
    }
    //cout<<endl;
    ans=max(ans,score[1]);
    int flag=1;
    if(ans<0){
        flag=-1;
        ans=abs(ans);
    }
    ans=((ans%mod)+mod)%mod;
    ans*=flag;
    cout<<ans<<endl;
    return 0;
}
