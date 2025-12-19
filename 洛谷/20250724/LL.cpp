#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 2e5+5;

int n,m;
int p[MAXN];
int inv[MAXN];
int f[MAXN];
int nums[MAXN];

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

int find(int val){
    int l=1,r=n,ans=n+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(nums[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    p[0]=1;
    for(int i=1;i<=n+1;i++){
        p[i]=(p[i-1]*2)%MOD;
    }
    inv[n+1]=power(p[n+1],MOD-2);
    for(int i=n;i>=1;i--){
        inv[i]=(inv[i+1]*2)%MOD;
    }
    for(int i=1;i<=n;i++){
        f[i]=(nums[i]*p[i])%MOD;
        f[i]=(f[i-1]+f[i])%MOD;
    }
    // for(int i=1;i<=n;i++){
    //     cout<<f[i]<<' ';
    // }
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<p[i]<<' ';
    // }
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<inv[i]<<' ';
    // }
    // cout<<endl;

    while(m--){
        int x,y;
        x=read(),y=read();
        y=n-y+1;
        int rk=find(x);
        cout<<x<<":  "<<rk<<' '<<y<<endl;
        if(rk>y){
            cout<<0<<endl;
            continue;
        }
        // cout<<m<<":   "<<rk<<' '<<y<<endl;
        int ans=(inv[y+1]*((((f[y]-f[rk-1])%MOD+MOD)%MOD+p[y+1]-p[rk]+x*p[rk]%MOD)%MOD+MOD)%MOD)%MOD;
        cout<<(ans-x)<<endl;
    }
    return 0;
}