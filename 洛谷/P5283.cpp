#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;
const int MAXT = 100*MAXN;
const int high = 32;

int n,k;
long long nums[MAXN];
long long ans1;
long long ans2;

int cnt=1;
int root[MAXN];
int pass[MAXT];
int tree[MAXT][2];

inline long long read(){
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

int add(long long num,int i){
    int rt=++cnt;
    tree[rt][0]=tree[i][0];
    tree[rt][1]=tree[i][1];
    pass[rt]=pass[i]+1;
    for (int b = high, path, pre = rt, cur; b >= 0; b--, pre = cur) {
        path = (num >> b) & 1;
        i = tree[i][path];
        cur = ++cnt;
        tree[cur][0] = tree[i][0];
        tree[cur][1] = tree[i][1];
        pass[cur] = pass[i] + 1;
        tree[pre][path] = cur;
    }
    return rt;
}

int query(long long val,long long num,int cur){
    int ans=0;
    int path=0,way=0;
    for(int i=high;i>=0;i--){
        path=(val>>i)&1;
        way=(num>>i)&1;
        if(way==1){
            cur=tree[cur][path^1];
        }
        else{
            ans+=pass[tree[cur][path^1]];
            cur=tree[cur][path];
        }
    }
    ans+=pass[cur];
    return ans;
}

long long check(long long val){
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=query(nums[i],val,root[i-1]);
    }
    return ans;
}

long long dfs(int cur,int u,long long val,int op){
    if(cur==0||u==-1){
        return 0;
    }
    long long ans=0;
    ans+=(op^((val>>u)&1))*pass[cur]*(1<<u);
    ans+=dfs(tree[cur][0],u-1,val,0);
    ans+=dfs(tree[cur][1],u-1,val,1);
    return ans;
}

long long fun(long long val,long long num,int cur){
    long long ans=0;
    int path=0;
    int way=0;
    long long sum=0;
    for(int i=high;i>=0;i--){
        path=(val>>i)&1;
        way=(num>>i)&1;
        if(way==1){
            cur=tree[cur][path^1];
        }
        else{
            ans+=sum*pass[tree[cur][path^1]];
            ans+=dfs(tree[cur][path^1],i,val,path^1);
            cur=tree[cur][path];
        }
        sum+=way*(1ll<<i);
        if(cur==0){
            break;
        }
    }
    ans+=num*pass[cur];
    return ans;
}

long long compute(){
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans+=fun(nums[i],ans1,root[i-1]);
    }
    return ans;
}

signed main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
        nums[i]^=nums[i-1];
    }
    root[0]=add(0,0);
    for(int i=1;i<=n;i++){
        root[i]=add(nums[i],root[i-1]);
    }
    long long l=0,r=4294967295;
    while(l<=r){
        long long mid=(l+r)>>1;
        long long tmp=check(mid);
        // cout<<' '<<mid<<' '<<tmp<<endl;
        if(tmp>=k){
            ans1=mid,ans2=tmp;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    // cout<<ans1<<' '<<ans2<<endl;
    long long ans=0;
    ans-=(ans2-k)*ans1;
    ans+=compute();
    printf("%lld\n",ans);
    return 0;
}