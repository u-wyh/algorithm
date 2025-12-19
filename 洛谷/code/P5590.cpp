#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 2005;

int n,m;

int dis[MAXN];
int updatecnt[MAXN];

bool ok[MAXN];//表示是否在到n的路径上

int x[MAXM],y[MAXM];
bool vis[MAXN<<1];

int cnt=1;
int head[MAXN];
int nxt[MAXM];
int to[MAXM];

int tot=1;
int head1[MAXN];
int nxt1[MAXM<<1];
int to1[MAXM<<1];
int weight[MAXM<<1];

queue<int>q;

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

void addedge(int u,int v){
    // cout<<' '<<u<<' '<<v<<endl;
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void addEdge(int u,int v,int w){
    // cout<<' '<<u<<' '<<v<<' '<<w<<endl;
    nxt1[tot]=head1[u];
    to1[tot]=v;
    weight[tot]=w;
    head1[u]=tot++;
}

bool spfa(){
    for(int i=0;i<=n+1;i++){
        vis[i]=false;
    }
    dis[0] = 0;
    updatecnt[0]++;
    q.push(0) ;
    vis[0] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int ei = head1[u], v, w; ei > 0; ei = nxt1[ei]) {
            v = to1[ei];
            w = weight[ei];
            if (dis[u] + w < dis[v]) {
                //如果值变小了  那么就要改变
                dis[v] = dis[u] + w;
                if (!vis[v]) {
                    if (++updatecnt[v] > n) {
                        return true;
                    }
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    return false;
}

bool dfs(int u){
    if(u==n||ok[u])
        return 1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[i]){
            vis[i]=true;
            if(dfs(v)){
                ok[u]=1;
                addEdge(u,v,9);
                addEdge(v,u,-1);
            }
        }
    }
    return ok[u];
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        x[i]=read(),y[i]=read();
        addedge(x[i],y[i]);
    }
    for(int i=1;i<=n;i++){
        addEdge(0,i,0);
        dis[i]=INT_MAX;
    }
    if(!dfs(1)){
        cout<<-1<<endl;
        return 0;
    }
    if(spfa()){
        cout<<-1<<endl;
        return 0;
    }
    printf("%d %d\n",n,m);
    for(int i=1;i<=m;i++){
        printf("%d %d ",x[i],y[i]);
        int d=abs(dis[x[i]]-dis[y[i]]);
        if(d>=1&&d<=9){
            printf("%d\n",d);
        }
        else{
            printf("1\n");
        }
    }
    return 0;
}