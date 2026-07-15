#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 1e6+5;

int n,m;
int height[MAXN];
int fa[MAXN];
bool ok[MAXN];
int tot;
struct node{
    int u,v,w;
}nums[MAXM<<1];

int cnt=1;
int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int weight[MAXM<<1];
bool vis[MAXM<<1];

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

bool cmp(node a,node b){
    return (height[a.v]==height[b.v])?(a.w<b.w):(height[a.v]>height[b.v]);
}

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

inline int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

void bfs() {
    queue<int> q;
    q.push(1);
    ok[1] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            nums[++tot] = {u, v, weight[i]}; // 添加边到新图
            if (!ok[v]) {
                ok[v] = true;
                q.push(v);
            }
        }
    }
}

// void bfs(int u){
//     ok[u]=true;
//     for(int i=head[u];i;i=nxt[i]){
//         if(vis[i]){
//             continue;
//         }
//         vis[i]=true;
//         nums[++tot]={u,to[i],weight[i]};
//         bfs(i);
//     }
// }

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        height[i]=read();
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        u=read(),v=read(),w=read();
        if(height[u]>=height[v]){
            addedge(u,v,w);
        }
        if(height[v]>=height[u]){
            addedge(v,u,w);
        }
    }
    bfs();
    int ans1=0;
    for(int i=1;i<=n;i++){
        if(ok[i]){
            ans1++;
        }
    }
    cout<<ans1<<' ';
    long long ans2=0;
    sort(nums+1,nums+tot+1,cmp);
    for(int i=1;i<=tot;i++){
        int fx=find(nums[i].u);
        int fy=find(nums[i].v);
        if(fx!=fy){
            fa[fx]=fy;
            ans2+=nums[i].w;
        }
    }
    cout<<ans2;
    return 0;
}