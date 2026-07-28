// 仙人掌直径，C++版
// 给定n个点、m条路径表示无向图，每条路径的相邻两点之间都有边
// 点x到点y的距离，是指x到y的最短路径中的边数
// 仙人掌直径，是指任意两点距离的最大值
// 输入保证图是仙人掌，计算仙人掌直径
// 1 <= n <= 5 * 10^4
// 1 <= 边总数 <= 10^6
// 测试链接 : https://www.luogu.com.cn/problem/P4244
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 2e6+5;

int n,m;

int head[MAXN];
int nxt[MAXM<<1];
int to[MAXM<<1];
int cntg=2;

int dfncnt;
int dfn[MAXN];
int low[MAXN];
int sta[MAXN];
int top;

int diameter;
int dist[MAXN];
int arr[MAXN<<1];
int que[MAXN<<1];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dponcycle(int u,int v){
    int sz=0;
    arr[++sz]=dist[u];
    int pop;
    do{
        pop=sta[top--];
        arr[++sz]=dist[pop];
    }while(pop!=v);
    for(int i=1;i<=sz;i++){
        arr[i+sz]=arr[i];
    }

    int l=1,r=0;
    que[++r]=1;
    for(int i=2;i<=sz<<1;i++){
        while(l<=r&&(i-que[l])*2>sz){
            l++;
        }
        diameter=max(diameter,arr[i]+i+arr[que[l]]-que[l]);
        while(l<=r&&arr[que[r]]-que[r]<=arr[i]-i){
            r--;
        }
        que[++r]=i;
    }
    for(int i=2;i<=sz;i++){
        dist[u]=max(dist[u],arr[i]+min(i-1,sz-i+1));
    }
}

void tarjan(int u,int preedge){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;
    for(int i=head[u];i;i=nxt[i]){
        if((i^1)==preedge){
            continue;
        }

        int v=to[i];
        if(dfn[v]==0){
            tarjan(v,i);
            if(low[v]<dfn[u]){
                low[u]=min(low[u],low[v]);
            }
            else if(low[v]>dfn[u]){
                top--;
                diameter=max(diameter,dist[v]+dist[u]+1);
                dist[u]=max(dist[u],dist[v]+1);
            }
            else{
                dponcycle(u,v);
            }
        }
        else if(dfn[v]<dfn[u]){
            low[u]=min(low[u],dfn[v]);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int k,x,y;
        cin>>k>>x;
        for(int j=2;j<=k;j++){
            cin>>y;
            addedge(x,y);
            addedge(y,x);
            x=y;
        }
    }

    tarjan(1,0);

    cout<<diameter<<endl;
    return 0;
}