#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 5005;

int n,m;
bool tag[MAXN];
bool vis[MAXN];

int x[MAXM],y[MAXM];

int dis[MAXN];
int updatecnt[MAXN];

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
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void addEdge(int u,int v,int w){
    nxt1[tot]=head1[u];
    to1[tot]=v;
    weight[tot]=w;
    head1[u]=tot++;
}

bool spfa(){
    for(int i=1;i<=n;i++){
        vis[i]=false;
    }
    dis[0]=0;
    vis[0]=1;
    q.push(0);
    updatecnt[0]++;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=head1[u];i;i=nxt1[i]){
            int v=to1[i];
            int w=weight[i];
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(!vis[v]){
                    if(++updatecnt[v]>n){
                        return true;
                    }
                    vis[v]=true;
                    q.push(v);
                }
            }
        }
    }
    return false;
}

void dfs(int u){
    if(u==n){
        return ;
    }
    for(int i=head[u];i;i=nxt[i]){
        if(!vis[to[i]]){
            vis[to[i]]=1;
            dfs(to[i]);
        }
        if(tag[to[i]]){
            tag[u]=1;
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        x[i]=read(),y[i]=read();
        addedge(x[i],y[i]);
    }
    tag[n]=true;
    vis[1]=true;
    dfs(1);
    for(int i=1;i<=m;i++){
        if(tag[x[i]]&&tag[y[i]]){
            addEdge(x[i],y[i],2);
            addEdge(y[i],x[i],-1);
        }
    }
    for(int i=1;i<=n;i++){
        dis[i]=INT_MAX;
        addEdge(0,i,0);
    }
    if(spfa()){
        cout<<"No"<<endl;
        return 0;
    }
    printf("Yes\n");
    for(int i=1;i<=m;i++){
        if (tag[x[i]] && tag[y[i]]) {
            printf("%d\n", dis[y[i]] - dis[x[i]]);
        } else {
            printf("1\n");
        }
    }
    return 0;
}