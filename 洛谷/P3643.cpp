#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 505;

int n;
int cnt,m;
int nums[MAXN*3];
int inv[MAXN];
int comb[MAXN];
int l[MAXN];
int r[MAXN];
int g[MAXN*3];

int find(int val){
    int l=1,r=m,ans=1;
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

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>l[i]>>r[i];
        nums[++cnt]=l[i];
        nums[++cnt]=r[i];
        nums[++cnt]=r[i]+1;
    }
    sort(nums+1,nums+cnt+1);
    m=1;
    for(int i=2;i<=cnt;i++){
        if(nums[i]!=nums[i-1]){
            nums[++m]=nums[i];
        }
    }

    inv[1]=1;
    for(int i=2;i<=n;i++){
        inv[i]=(MOD-inv[MOD%i]*(MOD/i)%MOD+MOD)%MOD;
    }

    for(int i=1;i<=n;i++){
        l[i]=find(l[i]);
        r[i]=find(r[i]);
    }

    g[0]=1;
    for(int j=1;j<m;j++){

        int len=nums[j+1]-nums[j];
        comb[0]=1;
        for(int i=1;i<=n;i++){
            comb[i]=((comb[i-1]*inv[i])%MOD)*(len+i-1)%MOD;
        }

        for(int i=n;i>=1;i--){
            if(j>=l[i]&&j<=r[i]){
                int f=0,m=1,c=comb[1];
                for(int p=i-1;p>=0;p--){
                    f=(f+c*g[p]%MOD)%MOD;
                    if(l[p]<=j&&r[p]>=j){
                        c=comb[++m];
                    }
                }
                g[i]=(g[i]+f)%MOD;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=(ans+g[i])%MOD;
    }
    cout<<ans<<endl;
    return 0;
}