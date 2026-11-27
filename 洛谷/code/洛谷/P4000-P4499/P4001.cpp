// https://www.luogu.com.cn/problem/P4001
// 题意：第一行输入网格大小 N, M，
// 接下来三部分依次输入横向（N 行每行 M-1 个）、纵向
// （N-1 行每行 M 个）、斜向（N-1 行每行 M-1 个
// 从 (x, y) 到 (x+1, y+1)）无向道路的权值。
// 所有兔子从 (1, 1) 逃向 (N, M)，
// 封锁一条权值为 K 的道路需 K 只狼，
// 求彻底阻断通路所需的最少狼数（即最小割）。
// 输出一个整数表示最小狼数。
// 数据范围：对于全部测试点，3 <= N, M <= 1000，
// 所有道路权值为不超过 10^6 的正整数。
// 算法标签：平面图转对偶图、Dijkstra、最小割
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1e18;
const int MAXN = 1005;
const int MAXV = 2 * MAXN * MAXN;
const int MAXE = 12 * MAXN * MAXN;

int n,m;
int s,t;

int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int weight[MAXE];
int cntg=1;

int dis[MAXV];
bool vis[MAXV];

void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;

    nxt[cntg]=head[v];
    to[cntg]=u;
    weight[cntg]=w;
    head[v]=cntg++;
}

int getid(int r,int c,int k){
    return ((r-1)*(m-1)+(c-1))*2+k+1;
}

int dijkstra(){
    for(int i=0;i<=t;i++){
        dis[i]=INF;
        vis[i]=false;
    }

    dis[s]=0;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> heap;
    heap.push({0,s});

    while(!heap.empty()){
        int u=heap.top().second;
        heap.pop();

        if(vis[u]){
            continue;
        }
        vis[u]=true;

        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];

            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                heap.push({dis[v],v});
            }
        }
    }

    return dis[t];
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;

    s=0;
    t=2*(n-1)*(m-1)+1;

    // 第一部分：横向道路
    for(int i=1;i<=n;i++){
        for(int j=1;j<m;j++){
            int w;
            cin>>w;

            if(i==1){
                addedge(s,getid(i,j,0),w);
            }
            else if(i==n){
                addedge(getid(i-1,j,1),t,w);
            }
            else{
                addedge(getid(i-1,j,1),getid(i,j,0),w);
            }
        }
    }

    // 第二部分：纵向道路
    for(int i=1;i<n;i++){
        for(int j=1;j<=m;j++){
            int w;
            cin>>w;

            if(j==1){
                addedge(getid(i,j,1),t,w);
            }
            else if(j==m){
                addedge(s,getid(i,j-1,0),w);
            }
            else{
                addedge(getid(i,j-1,0),getid(i,j,1),w);
            }
        }
    }

    // 第三部分：斜向道路
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
            int w;
            cin>>w;

            addedge(getid(i,j,0),getid(i,j,1),w);
        }
    }

    cout<<dijkstra()<<endl;

    return 0;
}