#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MOD = 998244353;
const int MAXN = 51;

int n;
int cnt,m;
int nums[MAXN*3];
int l[MAXN];
int r[MAXN];
int f[MAXN][MAXN*3];
int comb[MAXN];
int inv[MAXN];

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
    int all=1;
    for(int i=n;i>=1;i--){
        cin>>l[i]>>r[i];
        nums[++cnt]=l[i];
        nums[++cnt]=r[i];
        nums[++cnt]=r[i]+1;
        all=(all*(r[i]-l[i]+1))%MOD;
    }
    all=power(all,MOD-2);

    sort(nums+1,nums+cnt+1);
    m=1;
    for(int i=2;i<=cnt;i++){
        if(nums[i]!=nums[i-1]){
            nums[++m]=nums[i];
        }
    }

    for(int i=1;i<=n;i++){
        l[i]=find(l[i]);
        r[i]=find(r[i]);
    }
    
    inv[1]=1;
    for(int i=2;i<=n;i++){
        inv[i]=(MOD-inv[MOD%i]*(MOD/i)%MOD+MOD)%MOD;
    }

    f[0][0]=1;
    for(int j=1;j<m;j++){

        int len=nums[j+1]-nums[j];
        comb[0]=1;
        for(int i=1;i<=n;i++){
            comb[i]=((comb[i-1]*inv[i])%MOD)*(len+i-1)%MOD;
        }

        for(int i=n;i>=1;i--){
            if(j>=l[i]&&j<=r[i]){
                for(int p=i-1;p>=0;p--){
                    for(int k=0;k<=j-1;k++){
                        f[i][j]=(f[i][j]+f[p][k]*comb[i-p])%MOD;
                    }
                    if(l[p]>j||r[p]<j){
                        break;
                    }
                }
            }
        }
    }

    int ans=0;
    for(int i=l[n];i<=r[n];i++){
        ans=(ans+f[n][i])%MOD;
    }
    ans=(ans*all)%MOD;
    cout<<ans<<endl;
    return 0;
}