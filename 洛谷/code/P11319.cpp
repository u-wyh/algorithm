#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MOD = 1e9+7;

int n;
int nums[MAXN];
int help[MAXN];

long long fac[MAXN];

int tree[MAXN];

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

inline int lowbit(int x){
    return x&(-x);
}

void add(int x,int val){
    while(x<=n){
        tree[x]+=val;
        x+=lowbit(x);
    }
}

int sum(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int find(int val){
    int l=1,r=n,ans=n;
    while(l<=r){
        int mid=(l+r)/2;
        if(help[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
        help[i]=nums[i];
    }
    sort(help+1,help+n+1);
    for(int i=1;i<=n;i++){
        nums[i]=find(nums[i]);
        add(i,1);
    }
    fac[0]=1;
    for(int i=1;i<n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(nums[i]!=1){
            ans=(ans+1ll*fac[n-i]*sum(nums[i]-1))%MOD;
        }   
        add(nums[i],-1);
    }
    ans=(ans+1+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}