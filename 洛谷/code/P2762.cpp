#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 105;
const int MAXV = MAXN*2;
const int MAXE = 2*MAXN*MAXN;
const int INF = 1e15;

int n,m,s,t;

int dep[MAXV];
int iter[MAXV];
bool vis[MAXV];  // 添加：用于DFS标记访问

int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int now[MAXE];
int cap[MAXE];

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

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    now[cnt]=0;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
    now[cnt]=0;
    head[v]=cnt++;
}

bool bfs(){
    for(int i=1;i<=t;i++){
        dep[i]=-1;
    }
    queue<int>q;
    dep[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=cap[i];
            int k=now[i];
            if(dep[v]<0&&(k<w)){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t]>=0;
}

int dfs(int u,int f){
    if(u==t){
        return f;
    }
    int flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        int v=to[i];
        int w=cap[i];
        int k=now[i];
        if(dep[u]+1==dep[v]&&k<w){
            int d=dfs(v,min(f,w-k));
            if(d>0){
                now[i]+=d;
                now[i^1]-=d;//更新反向边
                flow+=d;
                f-=d;
                if(f==0){
                    break;
                }
            }
        }
    }
    return flow;
}

int maxflow(){
    int flow=0;
    while(bfs()){
        for(int i=1;i<=t;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

// 添加：find_set函数 - 从节点u开始DFS遍历残量网络
void find_set(int u){
    vis[u] = true;
    for(int i = head[u]; i; i = nxt[i]){
        int v = to[i];
        // 如果边还有剩余容量且目标节点未被访问，则继续遍历
        if(cap[i] > now[i] && !vis[v]){
            find_set(v);
        }
    }
}

signed main()
{
    m=read(),n=read();
    s=n+m+1,t=s+1;
    int all=0;
    for(int i=1;i<=m;i++){
        int val=read();
        all+=val;
        addedge(s,i,val);
        string line;
        getline(cin,line);
        stringstream ss(line);
        int x;
        while(ss>>x){
            addedge(i,m+x,INF);
        }
    }
    for(int i=1;i<=n;i++){
        int val=read();
        addedge(m+i,t,val);
    }
    int flow=maxflow();
    
    // 添加：找出选择的实验和仪器
    memset(vis, 0, sizeof(vis));
    find_set(s);  // 从源点开始DFS
    
    // 输出选择的实验
    bool first = true;
    for(int i=1;i<=m;i++){
        if(vis[i]){
            if(!first) cout << " ";
            cout << i;
            first = false;
        }
    }
    cout << endl;
    
    // 输出选择的仪器
    first = true;
    for(int i=1;i<=n;i++){
        if(vis[m+i]){
            if(!first) cout << " ";
            cout << i;
            first = false;
        }
    }
    cout << endl;
    
    // 输出净收益
    cout << (all-flow) << endl;
    
    return 0;
}