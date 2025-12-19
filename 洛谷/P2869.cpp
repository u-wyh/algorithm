#include<bits/stdc++.h>
using namespace std;
#define inf 1e18+10
#define int long long
const int maxn=100010;
int n,a[maxn],v[maxn],rd[maxn],ans,minn=inf;
bool vis[maxn];
queue<int>q;
void topo(){
    for(int i=1;i<=n;i++){
        if(!rd[i])
            q.push(i);
    }
    while(!q.empty()){
        int x=q.front();
        q.pop();
        ans+=v[x];
        rd[a[x]]--;
        vis[x]=1;//表示不在环上
        if(!rd[a[x]])
            q.push(a[x]);
    }
    return;
}
void dfs(int x){
    vis[x]=1;
    minn=min(minn,v[x]);
    if(vis[a[x]])return;
    dfs(a[x]);
    return;
}
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&a[i],&v[i]);
        rd[a[i]]++;
    }
    topo();
    for(int i=1;i<=n;i++){
        if(!vis[i])
            ans+=v[i];
    }
    for(int i=1;i<=n;i++){
        if(vis[i])
            continue;
        minn=inf;
        dfs(i);
        ans-=minn;
    }
    printf("%lld",ans);
    return 0;
}
