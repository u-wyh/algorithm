#include<bits/stdc++.h>
using namespace std;
#define int long long 

int n,k,l,r;
int ans;
int nums[1005];

bool vis[61];
int val[61];
int cnt[62];
int p[62];

// 这个数位dp我的思路是到了这个位置 前面的限制值是完全一样的
// 如果有的位置是有限制的 即和一些高位保持一致 那么到了当前的位置  可能填的数字是小于必要的数字
// 那么这种情况直接结算  否则继续递归
// 来到一个位置 可能后面的某些位置已经填了（和前面的某些位保持一致） 但是首先已经填了的值是小于limit的
// 也就是说这个位置上填0  肯定不会违法  但是填1的话
void dfs(int x,int now,int limit){
    // cout<<ans<<' '<<x<<' '<<now<<' '<<limit<<endl;
    if(x<0){
        ans++;
        return ;
    }
    int v=(limit>>x)&1ll;
    // cout<<v<<endl;
    if(!vis[x]){
        int u=(now>>x)&1ll;
        if(u<v){
            ans+=p[cnt[x]];
            return ;
        }
        dfs(x-1,now,limit);
        return ;
    }
    if(v==0){
        dfs(x-1,now,limit);
    }
    else{
        ans+=p[cnt[x]];
        if(now+val[x]<=limit){
            dfs(x-1,now+val[x],limit);
        }
    }
}

signed main()
{
    cin>>n>>k>>l>>r;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=0;i<k;i++){
        vis[i]=true;
        val[i]=(1ll<<i);
    }
    p[0]=1;
    for(int i=1;i<=k;i++){
        p[i]=p[i-1]*2;
    }
    for(int i=k-1;i>=0;i--){
        if(!vis[i]){
            continue;
        }
        for(int j=i-1;j>=0;j--){
            if(!vis[j]){
                continue;
            }
            bool flag=false;
            for(int k=1;k<=n;k++){
                if(((nums[k]>>i)&1ll)!=((nums[k]>>j)&1ll)){
                    flag=true;
                    break;
                }
            }
            if(!flag){
                vis[j]=false;
                val[i]+=val[j];
            }
        }
    }
    cnt[0]=0;
    for(int i=1;i<=k;i++){
        cnt[i]=cnt[i-1];
        if(vis[i-1]){
            cnt[i]++;
        }
    }
    // for(int i=0;i<k;i++){
    //     cout<<i<<":  "<<vis[i]<<' '<<val[i]<<' '<<cnt[i]<<endl;
    // }
    // cout<<endl;
    ans=0;
    dfs(k-1,0,r);
    // cout<<ans<<endl;
    int res=ans;
    if(l!=0){
        ans=0;
        dfs(k-1,0,l-1);
        // cout<<ans<<endl;
        res-=ans;
    }
    cout<<res<<endl;
    return 0;
}