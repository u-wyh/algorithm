#include<bits/stdc++.h>
using namespace std;
const int MAXN = 7e4+5;
const int MAXH = 20;

int n,p;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int in[MAXN];
int cntg=1;

int sz[MAXN];
bool vis[MAXN];

int dp[MAXN];
int dep[MAXN];
int st[MAXN][MAXH];

int ans[MAXN];

void addedge(int u,int v){
    in[v]++;
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool flag=false;
    while(!flag){
        flag=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                flag=false;
                fa=u;
                u=v;
                break;
            }
        }
    }
    return u;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
}

void bfs(){
    for(int i=1;i<=n;i++){
        dp[i]=-1;
    }
    queue<int>q;
    for(int i=1;i<=n;i++){
        if(in[i]==1){
            q.push(i);
            dp[i]=0;
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(dp[v]==-1){
                dp[v]=dp[u]+1;
                q.push(v);
            }
        }
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int dist(int a,int b){
    return dep[a]+dep[b]-2*dep[lca(a,b)];
}

struct node{
    int u;
    int val;
    int goal;
    int dis;
};
node curnode[MAXN];
int curcnt;
node allnode[MAXN];
int allcnt;

bool cmp(node &a,node &b){
    return a.val<b.val;
}

void dfs(int u,int fa,int dis){
    curnode[++curcnt]={u,dp[u]-dis,2-in[u],dis};
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            dfs(v,u,dis+1);
        }
    }
}

int find(node *nums,int len,int val){
    int l=1,r=len,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(nums[mid].val<=val){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return ans;
}

void compute(node *nums,int len,int op){
    sort(nums+1,nums+len+1,cmp);
    for(int i=2;i<=len;i++){
        nums[i].goal+=nums[i-1].goal;
    }
    for(int i=1;i<=len;i++){
        ans[nums[i].u]+=op*nums[find(nums,len,nums[i].dis)].goal;
    }
}

void calc(int u){
    allcnt=0;
    allnode[++allcnt]={u,dp[u],2-in[u],0};

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            curcnt=0;
            dfs(v,u,1);

            for(int i=1;i<=curcnt;i++){
                allnode[++allcnt]=curnode[i];
            }
            compute(curnode,curcnt,-1);
        }
    }
    compute(allnode,allcnt,1);
}

void solve(int u){
    calc(u);
    vis[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            solve(getcentroid(v,u));
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    p=log2(n);
    dfs(1,0);
    bfs();

    int centroid=getcentroid(1,0);
    solve(centroid);

    for(int i=1;i<=n;i++){
        if(in[i]==1){
            ans[i]=1;
        }
        cout<<ans[i]<<endl;
    }
    return 0;
}