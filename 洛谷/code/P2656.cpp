#include<bits/stdc++.h>
using namespace std;
const int MAXN = 8e4+5;
const int MAXM = 2e5+5;

int n,m,s;
struct node{
    int u,v,first;
    double op;
}edge[MAXM];
vector<int>vec[MAXN];
int dfn[MAXN],low[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
bool instack[MAXN];

int val[MAXN];//点权

int cnt=1;
int head[MAXN];
int to[MAXM];
int Next[MAXM];
int weight[MAXM];

void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    st[++top]=x;
    instack[x]=true;
    for(int i=0;i<vec[x].size();i++){
        int v=vec[x][i];
        if(!dfn[v]){
            //表示这个节点没有被访问过
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            //表示这个属于是回溯了 一定是同一个环上的
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        //将所有节点按照颜色分类  完成缩点
        while(st[top]!=x){
            //属于同一个强联通分量
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

bool vis[MAXN];
queue<int>q;

void spfa(){
    q.push(s);
    vis[s]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=head[u];i;i=Next[i]){
            int v=to[i];
            int w=weight[i];
            if(val[v]<val[u]+w){
                val[v]=val[u]+w;
                if(!vis[v]){
                    q.push(v);
                    vis[v]=true;
                }
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        double op;
        cin>>edge[i].u>>edge[i].v>>edge[i].first>>edge[i].op;
        vec[edge[i].u].push_back(edge[i].v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
    for(int i=1;i<=m;i++){
        if(col[edge[i].u]==col[edge[i].v]){
            int k=(int)edge[i].first;
            val[col[edge[i].u]]+=k;
            int op=edge[i].op*10;
            while(k){
                k=k*op;
                k/=10;
                val[col[edge[i].u]]+=k;
            }
        }
        else{
            addedge(col[edge[i].u],col[edge[i].v],edge[i].first);
        }
    }
    cin>>s;
    s=col[s];
    spfa();
    int ans=0;
    for(int i=1;i<=color;i++){
        ans=max(ans,val[i]);
    }
    cout<<ans<<endl;
    return 0;
}
