#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 205;

int n;
int val[MAXN];

int ask(int x){
    cout<<"? "<<x<<endl;
    int v;
    cin>>v;
    return v;
}

signed main()
{
    cin>>n;
    int len=n;
    int l=0,r=1000000000000000000ll,ans=1000000000000000001ll;
    while(n){
        l=0,r=ans-1,ans=0;
        while(l<=r){
            int mid=(l+r)>>1ll;
            int v=ask(mid);
            if(v==n){
                ans=mid;
                r=mid-1;
            }
            else{
                l=mid+1;
            }
        }
        
        int t=n;
        if(ans!=0)
            t=n-ask(ans-1);
        for(int i=n;i>n-t;i--){
            val[i]=ans;
        }
        n-=t;
    }
    cout<<"! ";
    for(int i=1;i<=len;i++){
        cout<<val[i]<<' ';
    }
    cout<<endl;
    return 0;
}