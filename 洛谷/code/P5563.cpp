// https://www.luogu.com.cn/problem/P5563
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MOD = 65536+5;

int n,mod;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

bool vis[MAXN];
int sz[MAXN];

void getSize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            getSize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getCentroid(int u,int fa){
    getSize(u,fa);
    int half=sz[u]>>1;
    bool find=false;
    while(!find){
        find=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                fa=u;
                u=v;
                find=false;
                break;
            }
        }
    }
    return u;
}

int ans[MAXN];

struct node{
    int u,dis,top;
};
node nums[MAXN];
int cntt;

bool cmp(node &a,node &b){
    if(a.dis!=b.dis){
        return a.dis<b.dis;
    }
    return a.top<b.top;
}

void dfs(int u,int fa,int t,int d){
    nums[++cntt]={u,d,t};
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,t,(d+w)%mod);
        }
    }
}

int pre[MAXN];

void calc(int u){
    cntt=0;
    nums[++cntt]={u,0,0};
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(!vis[v]){
            dfs(v,u,v,w%mod);
        }
    }
    sort(nums+1,nums+cntt+1,cmp);
    int p=cntt;
    int top1=0,top2=0;
    int topbelong=0;
    top1=nums[cntt].dis;
    topbelong=nums[cntt].top;
    for(int i=cntt;i>=1;i--){
        if(nums[i].top!=topbelong){
            top2=nums[i].dis;
            break;
        }
    }
    
    pre[1]=0;
    for(int i=2;i<=cntt;i++){
        if(nums[i].top!=nums[i-1].top){
            pre[i]=i-1;
        }else{
            pre[i]=pre[i-1];
        }
    }

    for(int i=1;i<=cntt;i++){
        while(p && nums[i].dis+nums[p].dis>=mod){
            p--;
        }

        int j=p;
        if(j && nums[i].top==nums[j].top){
            j=pre[j];
        }
        if(j){
            ans[nums[i].u]=max(ans[nums[i].u],nums[i].dis+nums[j].dis);
        }
        ans[nums[i].u]=max(ans[nums[i].u],((nums[i].top==topbelong?top2:top1)+nums[i].dis)%mod);
    }
}

void solve(int u){
    vis[u]=true;
    calc(u);
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            solve(getCentroid(v,u));
        }
    }
}

int main()
{
    cin>>n>>mod;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    solve(getCentroid(1,0));
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}