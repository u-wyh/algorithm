#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int MAXH = 17;

int n,m,q;
int pos[MAXN];
int val[MAXN];

int fa[MAXN];

struct node{
    int u,v,w;
};
node nums[MAXM+MAXN];
int arr[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

int dep[MAXN];
int st[MAXN][MAXH];
int dis[MAXN][MAXH];

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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

bool cmp(node a,node b){
    return a.w>b.w;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void dfs(int u,int fa){
    // cout<<u<<' '<<fa<<endl;
    dep[u]=dep[fa]+1;
    for(int i=1;i<MAXH;i++){
        st[u][i]=st[st[u][i-1]][i-1];
        dis[u][i]=min(dis[u][i-1],dis[st[u][i-1]][i-1]);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v==fa){
            continue;
        }
        st[v][0]=u;
        dis[v][0]=w;
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=MAXH-1;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=MAXH-1;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int query(int s,int d){
    // cout<<"   "<<s<<' '<<d<<' ';
    if(s==d){
        // cout<<INF<<endl;
        return INF;
    }
    int ans=INF;
    for(int i=MAXH-1;i>=0;i--){
        if(dep[st[s][i]]>dep[d]){
            ans=min(ans,dis[s][i]);
            s=st[s][i];
        }
    }
    ans=min(ans,dis[s][0]);
    // cout<<ans<<endl;
    return ans;
}

signed main()
{
    n=read(),m=read(),q=read();
    for(int i=1;i<=n;i++){
        pos[i]=read();
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        nums[i].u=read(),nums[i].v=read(),nums[i].w=read();
    }
    for(int i=1;i<=q;i++){
        arr[i]=read();
    }
    for(int i=1;i<q;i++){
        nums[m+i]={arr[i],arr[i+1],INF};
    }
    q=max(0ll,q-1);
    sort(nums+1,nums+m+q+1,cmp);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m+q;i++){
        int fx=find(nums[i].u);
        int fy=find(nums[i].v);
        if(fx!=fy){
            fa[fx]=fy;
            addedge(nums[i].u,nums[i].v,nums[i].w);
            addedge(nums[i].v,nums[i].u,nums[i].w);
        }
    }
    dfs(1,0);
    int now=0;
    if(val[pos[1]]<0){
        cout<<0<<endl;
    }
    else{
        now+=val[pos[1]];
    }
    cout<<now<<endl;
    for(int i=2;i<=n;i++){
        int fa=lca(pos[i],pos[i-1]);
        int limit=min(query(pos[i],fa),query(pos[i-1],fa));
        now=min(now,limit);
        if(val[pos[i]]<0){
            if(now+val[pos[i]]<0){
                cout<<now<<endl;
                now=0;
            }
            else{
                cout<<-val[pos[i]]<<endl;
                now+=val[pos[i]];
            }
        }
        else{
            now+=val[pos[i]];
        }
        // cout<<fa<<' '<<limit<<' '<<now<<endl;
    }
    return 0;
}