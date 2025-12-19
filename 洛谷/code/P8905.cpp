#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;

int n,m;
long long ans=0;

int in[MAXN];//这是重新开始加点时的度数
bool vis[MAXN];//表示是否已经被重新加入
int degree[MAXN];//这是最开始的入度

int head[MAXN];
int Next[MAXM<<1];
int to[MAXM<<1];
int cnt=1;

int fa[MAXN];
int sz[MAXN];

set<pair<int,int>>s;//实际上堆也可以  但是功能实现较为麻烦
stack<int>st;//表示插入顺序

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
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        sz[fy]+=sz[fx];
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
        degree[u]++,degree[v]++;
    }
    for(int i=1;i<=n;i++){
        s.insert({degree[i],i});
    }
    while(!s.empty()){
        int u=(*s.begin()).second;
        s.erase(s.begin());
        st.push(u);
        in[u]=degree[u];
        //表示这个节点已经被删除  还没有删除的点  在这个点被重新加入的时候 也一定还在
        for(int i=head[u];i;i=Next[i]){
            int v=to[i];
            if(in[v]){
                //如果不是0  一定是已经被删除
                continue;
            }
            s.erase(s.lower_bound({degree[v],v}));//弹出元素
            degree[v]--;//因为u这个节点被弹出 所以度数减一  因为重新加入v的时候  u一定没有在图中
            s.insert({degree[v],v});
        }
    }
    for(int i=1;i<=n;i++){
        int u=st.top();
        vis[u]=true;
        st.pop();
        for(int j=head[u];j;j=Next[j]){
            int v=to[j];
            if(vis[v]){
                //表示这个点已经加入
                un(u,v);
            }
        }
        //此时的in[u]一定是度最小的  因为在目前重新加入的点都存在的时候  删除的节点是u  说明u的度数一定是最小的
        ans=max(ans,(long long)sz[find(u)]*in[u]);
        //cout<<in[i]<<' ';
    }
    cout<<ans<<endl;
    return 0;
}
