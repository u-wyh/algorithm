#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MOD = 998244353;

int n,m;
int inv,p;
int nums[MAXN];
bool vis[MAXN];
int ans=0;

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

int compute1(){
    for(int i=1;i<=n;i++){
        vis[i]=false;
    }
    int res=0;
    vis[1]=true;
    int pos=3;
    for(int i=3;i<=n;i++){
        if(((nums[i]-nums[i-1])<(nums[pos]-nums[pos-1]))||((nums[i]-nums[i-1])==(nums[pos]-nums[pos-1])&&(abs(i-n/2-2)<abs(pos-n/2-2)))){
            pos=i;
        }
    }
    vis[pos]=true,vis[pos-1]=true;
    p=power(m,n/2-1);
    res=(res+p*(nums[pos]-nums[pos-1])%MOD)%MOD;
    p=(p*inv)%MOD;
    int l=2,r=n;
    for(int i=1;i<=n/2-1;i++){
        while(vis[l]){
            l++;
        }
        while(vis[r]){
            r--;
        }
        vis[l]=true,vis[r]=true;
        res=((res-p*(nums[r]-nums[l])%MOD)%MOD+MOD)%MOD;
        l++,r--;
        p=p*inv%MOD;
    }
    res=(res%MOD+MOD)%MOD;
    return res;
}

int compute2(){
    for(int i=1;i<=n;i++){
        vis[i]=false;
    }
    int res=0;
    vis[2]=true;
    p=power(m,n/2);
    res=p*nums[2]%MOD;
    p=(p*inv)%MOD;
    int l=1,r=n;
    for(int i=1;i<=n/2;i++){
        while(vis[l]){
            l++;
        }
        while(vis[r]){
            r--;
        }
        vis[l]=true,vis[r]=true;
        res=((res-p*(nums[r]-nums[l])%MOD)%MOD+MOD)%MOD;
        l++,r--;
        p=p*inv%MOD;
    }
    res=(res%MOD+MOD)%MOD;
    return res;
}

signed main()
{
    int T=read();
    while(T--){
        n=read(),m=read();
        ans=0;
        inv=power(m,MOD-2);
        for(int i=1;i<=n;i++){
            nums[i]=read();
            vis[i]=false;
        }
        sort(nums+1,nums+n+1);
        if(nums[1]==0&&n%2==1){
            // cout<<compute1()<<' '<<compute2()<<endl;
            if(n==1){
                ans=0;
            }
            else{
                ans=min(compute1(),compute2());
            }
        }
        else if(n%2==0){
            p=power(m,n/2-1);
            int pos=2;
            for(int i=2;i<=n;i++){
                if(((nums[i]-nums[i-1])<(nums[pos]-nums[pos-1]))||((nums[i]-nums[i-1])==(nums[pos]-nums[pos-1])&&(abs(i-n/2-1)<abs(pos-n/2-1)))){
                    pos=i;
                }
            }
            vis[pos]=true,vis[pos-1]=true;
            ans=(ans+p*(nums[pos]-nums[pos-1])%MOD)%MOD;
            p=(p*inv)%MOD;
            int l=1,r=n;
            for(int i=1;i<=n/2-1;i++){
                while(vis[l]){
                    l++;
                }
                while(vis[r]){
                    r--;
                }
                vis[l]=true,vis[r]=true;
                ans=((ans-p*(nums[r]-nums[l])%MOD)%MOD+MOD)%MOD;
                l++,r--;
                p=p*inv%MOD;
            }
        }
        else{
            p=power(m,n/2);
            ans=p*nums[1]%MOD;
            int l=2,r=n;
            for(int i=1;i<=n/2;i++){
                while(vis[l]){
                    l++;
                }
                while(vis[r]){
                    r--;
                }
                vis[l]=true,vis[r]=true;
                p=p*inv%MOD;
                ans=((ans-p*(nums[r]-nums[l])%MOD)%MOD+MOD)%MOD;
                l++,r--;
            }
        }
        ans=(ans%MOD+MOD)%MOD;
        cout<<ans<<endl;
    }
    return 0;
}