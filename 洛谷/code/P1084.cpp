#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int LIMIT = 17;

int n,m;

int nums[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;

int st[MAXN][LIMIT];
long long dist[MAXN][LIMIT];

bool need[MAXN];
bool vis[MAXN];
pair<long long,int> f[MAXN];
long long g[MAXN];
int cnt1,cnt2;

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

void dfs(int u,int fa){
    st[u][0]=fa;
    for(int i=1;i<LIMIT;i++){
        st[u][i]=st[st[u][i-1]][i-1];
        dist[u][i]=dist[st[u][i-1]][i-1]+dist[u][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dist[v][0]=weight[i];
        dfs(v,u);
    }
}

void compute(int u,long long limit){
    for(int i=LIMIT-1;i>=0;i--){
        if(st[u][i]>1&&limit>=dist[u][i]){
            limit-=dist[u][i];
            u=st[u][i];
        }
    }
    if(st[u][0]==1){
        ++cnt1;
        f[cnt1]={limit-dist[u][0],u};
    }
    need[u]=false;
}

void dfs1(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        if(need[v]){
            dfs1(v,u);
            if(need[v]){
                need[u]=true;
                break;
            }
        }
    }
}

bool fun(){
    sort(f+1,f+cnt1+1);
    sort(g+1,g+cnt2+1);
    int l=1;
    for(int i=1;i<=cnt2;i++){
        while(l<=cnt1&&f[l].first<g[i]){
            l++;
        }
        if(l>cnt1){
            return false;
        }
        l++;
    }
    return true;
}

bool check(long long limit){
    for(int i=1;i<=n;i++){
        need[i]=true;
        vis[i]=false;
    }
    cnt1=0,cnt2=0;
    for(int i=1;i<=m;i++){
        compute(nums[i],limit);
    }
    dfs1(1,0);
    if(!need[1]){
        return true;
    }
    vis[1]=true;
    sort(f+1,f+cnt1+1);
    for(int i=1;i<=cnt1;i++){
        if(!vis[f[i].second]){
            vis[f[i].second]=true;
            f[i].first=0;
        }
    }
    for(int i=head[1];i;i=nxt[i]){
        int v=to[i];
        if(need[v]){
            g[++cnt2]=weight[i];
        }
    }
    return fun();
}

int main()
{
    n=read();
    int son=0;
    long long l=0,r=0,ans=0;
    for(int i=1;i<n;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedge(u,v,w);
        addedge(v,u,w);
        r+=w;
        if(u==1||v==1){
            son++;
        }
    }
    m=read();
    for(int i=1;i<=m;i++){
        nums[i]=read();
    }
    if(son>m){
        cout<<-1<<endl;
        return 0;
    }
    dfs(1,0);
    while(l<=r){
        long long mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}