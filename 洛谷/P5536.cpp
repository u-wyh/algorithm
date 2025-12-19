#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5;

int n,k;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int deep[MAXN],maxdeep[MAXN];
// dist[i] : 从规定的头节点出发，走到i的距离
int dist[MAXN];
// last[i] : 从规定的头节点出发，i节点的上一个节点
int last[MAXN];
int start,en,diameter;

void dfs(int u,int f){
    last[u]=f;
    dist[u]=dist[f]+1;
    for(int i=head[u];i>0;i=Next[i]){
        if(to[i]!=f){
            dfs(to[i],u);
        }
    }
}

void road() {
    dfs(1, 0);
    //这个起点是随机的  一般都是1
    start = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[start]) {
            start = i;
        }
    }
    //选择离他距离最大的点  作为头结点
    dfs(start, 0);
    en = 1;
    for (int i = 2; i <= n; i++) {
        if (dist[i] > dist[en]) {
            en = i;
        }
    }
    diameter = dist[en];
}
//两次调用dfs

void dfs1(int u,int f){
    deep[u]=deep[f]+1;
    maxdeep[u]=deep[u];
    for(int i=head[u];i>0;i=Next[i]){
        int v=to[i];
        if(v!=f){
            dfs1(to[i],u);
            maxdeep[u]=max(maxdeep[u],maxdeep[v]);
        }
    }
}

bool cmp(int a,int b){
    return a>b;
}

int main()
{
    cin>>n>>k;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;

        Next[cnt]=head[u];
        to[cnt]=v;
        head[u]=cnt++;

        Next[cnt]=head[v];
        to[cnt]=u;
        head[v]=cnt++;
    }
    road();
    for(int i=1;i<=diameter/2;i++){
        start=last[en];
        en=start;
    }
    dfs1(start,0);
    for(int i=1;i<=n;i++){
        dist[i]=maxdeep[i]-deep[i]+1;
    }
    sort(dist+1,dist+n+1,cmp);
    cout<<dist[k+1];
    return 0;
}
