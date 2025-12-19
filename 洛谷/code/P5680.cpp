#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXH = 20;
const int MAXM = 2e5+5;
const int INF = 1e9;

int n,m,p,s,q,k;

// 原图建边
int headp[MAXN];
int nxtp[MAXM];
int top[MAXM];
int weightp[MAXM];
int cntp=1;

int from[MAXN];
int fromweight[MAXN];
int dis[MAXN];
bool vis[MAXN];

struct node{
    int x,dis;
};
struct compare{
    bool operator()(const node&a,const node&b){
        return a.dis>b.dis;
    }
};
priority_queue<node,vector<node>,compare>heap;

// bool intree[MAXN];

// 生成树建图
int headq[MAXN];
int nxtq[MAXN];
int toq[MAXN];
int weightq[MAXN];
int cntq=1;

int dep[MAXN];
int dfn[MAXN];
int st[MAXN][MAXH];
int dfncnt;

// 虚树建图
int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int weight[MAXN];
int cnt=1;

int arr[MAXN];
bool iskey[MAXN];
int tmp[MAXN];
int dp[MAXN];

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

inline void addedgep(int u,int v,int w){
    nxtp[cntp]=headp[u];
    top[cntp]=v;
    weightp[cntp]=w;
    headp[u]=cntp++;
}

void dijkstra(){
    for(int i=1;i<=n;i++){
        dis[i]=INF;
        from[i]=n+1;
    }
    dis[s]=0;
    heap.push({s,0});
    while(!heap.empty()){
        node cur=heap.top();
        heap.pop();
        int u=cur.x;
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=headp[u];i;i=nxtp[i]){
            int v=top[i];
            int w=weightp[i];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                from[v]=u;
                fromweight[v]=w;
                heap.push({v,dis[v]});
            }
            else if(dis[v]==dis[u]+w&&from[v]>u){
                from[v]=u;
                fromweight[v]=w;
            }
        }
    }
}

inline void addedgeq(int u,int v,int w){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    weightq[cntq]=w;
    headq[u]=cntq++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    dfn[u]=++dfncnt;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        dfs(v,u);
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

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

bool cmp(int a,int b){
    return dfn[a]<dfn[b];
}

int buildvirtualtree(){
    sort(arr+1,arr+k+1,cmp);
    int len=0;
    tmp[++len]=s;
    for(int i=1;i<k;i++){
        tmp[++len]=arr[i];
        tmp[++len]=lca(arr[i],arr[i+1]);
    }
    tmp[++len]=arr[k];
    sort(tmp+1,tmp+len+1,cmp);

    bool flag=false;
    for(int i=1;i<=len;i++){
        if(iskey[tmp[i]]){
            flag=true;
        }
    }
    if(!flag){
        return -1;
    }

    int m=1;
    for(int i=2;i<=len;i++){
        if(tmp[i]!=tmp[i-1]){
            tmp[++m]=tmp[i];
        }
    }

    cnt=1;
    for(int i=1;i<=m;i++){
        head[tmp[i]]=0;
    }
    for(int i=1;i<m;i++){
        int fa=lca(tmp[i],tmp[i+1]);
        addedge(fa,tmp[i+1],dis[tmp[i+1]]-dis[fa]);
    }
    return tmp[1];
}

void dfs1(int u){
    dp[u]=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(iskey[v]){
            dp[u]+=w;
        }
        else{
            dp[u]+=min(w,dp[v]);
        }
    }
}

int compute(){
    int tree=buildvirtualtree();
    if(tree==-1){
        return -1;
    }
    dfs1(tree);
    return dp[tree];
}

int main()
{
    n=read(),m=read(),s=read(),q=read();
    p=log2(n)+1;
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        addedgep(u,v,w);
        addedgep(v,u,w);
    }
    dijkstra();

    for(int i=1;i<=n;i++){
        if(from[i]==n+1){
            // if(i==s){
            //     intree[i]=true;
            // }
            continue;
        }
        else{
            addedgeq(from[i],i,fromweight[i]);
            // intree[i]=true;
        }
    }
    dfs(s,0);

    for(int t=1;t<=q;t++){
        int op=read();
        k=read();
        if(op==0){
            for(int i=1;i<=k;i++){
                int u=read();
                iskey[u]=!iskey[u];
            }
        }
        else{
            // bool check=false;
            for(int i=1;i<=k;i++){
                arr[i]=read();
                // if(iskey[arr[i]]){
                //     check=true;
                // }
            }
            // if(!check){
            //     cout<<-1<<endl;
            // }
            // else{
            //     cout<<compute()<<endl;
            // }
            cout<<compute()<<endl;
        }
    }
    return 0;
}