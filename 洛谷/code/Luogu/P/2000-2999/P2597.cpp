#include<bits/stdc++.h>
using namespace std;
const int MAXN = 70000;
const int MAXH = 17;

int n;

int in[MAXN];
vector<int>vec[MAXN];
vector<int>food[MAXN];

int dep[MAXN];
int st[MAXN][MAXH];
int sz[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

queue<int>q;
vector<int>topo;

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
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

void dfs(int u){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        sz[u]+=sz[v];
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        int v=read();
        while(v){
            vec[v].push_back(i);
            food[i].push_back(v);
            in[i]++;
            v=read();
        }
    }
    for(int i=1;i<=n;i++){
        if(in[i]==0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        topo.push_back(u);
        for(int i=0;i<(int)vec[u].size();i++){
            int v=vec[u][i];
            in[v]--;
            if(in[v]==0){
                q.push(v);
            }
        }
    }
    for(int i=0;i<n;i++){
        int v=topo[i];
        int u;
        if(food[v].empty()){
            u=0;
        }
        else{
            u=food[v][0];
            for(int j=1;j<(int)food[v].size();j++){
                u=lca(u,food[v][j]);
            }
        }
        dep[v]=dep[u]+1;
        st[v][0]=u;
        for(int j=1;j<MAXH;j++){
            st[v][j]=st[st[v][j-1]][j-1];
        }
        addedge(u,v);
    }
    dfs(0);
    for(int i=1;i<=n;i++){
        cout<<(sz[i]-1)<<endl;
    }
    return 0;
}