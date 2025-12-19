//两次dfs
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
#define int long long

int n,m;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cnt=1;
// 直径的开始点
int start;
// 直径的结束点
int en;
// 直径长度
int diameter;
// dist[i] : 从规定的头节点出发，走到i的距离
int dist[MAXN];
int beg[MAXN];
int ove[MAXN];
int ans=0;

void dfs(int u,int f,int w){
    dist[u]=dist[f]+w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u,weight[i]);
        }
    }
}

void road() {
    dfs(1, 0, 0);
    //这个起点是随机的  一般都是1
    start = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[start]) {
            start = i;
        }
    }
    //选择离他距离最大的点  作为头结点
    dfs(start, 0, 0);
    en = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[en]) {
            en = i;
        }
    }
    diameter = dist[en];
}
//两次调用dfs

void dfs1(int u,int f,int w){
    beg[u]=beg[f]+w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs1(to[i],u,weight[i]);
        }
    }
}

void dfs2(int u,int f,int w){
    ove[u]=ove[f]+w;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs2(to[i],u,weight[i]);
        }
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;

        Next[cnt]=head[u];
        to[cnt]=v;
        weight[cnt]=w;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        weight[cnt]=w;
        head[v]=cnt++;
    }
    road();
    ans=diameter;
    dfs1(start,0,0);
    dfs2(en,0,0);
    for(int i=1;i<=n;i++){
        ans=max(ans,min(beg[i],ove[i])+diameter);
    }
    cout<<ans;
    return 0;
}
