#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,k;
int nums[MAXN];
int sum[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

bool check(int val){
    if(sum[n]-val<=k){
        return true;
    }
    int l=0,r=min(val,n-1);
    for(int i=l;i<=r;i++){
        if((k-(sum[n-i]-nums[1]))>=(nums[1]-(val-i))*(i+1)){
            return true;
        }
    }
    return false;
}

signed main()
{
    int T=read();
    while(T--){
        n=read(),k=read();
        for(int i=1;i<=n;i++){
            nums[i]=read();
        }
        sort(nums+1,nums+n+1);
        for(int i=1;i<=n;i++){
            sum[i]=sum[i-1]+nums[i];
        }
        if(sum[n]<=k){
            cout<<0<<endl;
            continue;
        }
        int l=1,r=1e9+2e5+5,ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)){
                ans=mid;
                r=mid-1;
            }
            else{
                l=mid+1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}