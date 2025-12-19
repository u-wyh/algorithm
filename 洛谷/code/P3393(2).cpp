#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 4e5+8;
#define int long

auto compare = [](const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second; // 注意这里是大于，因为我们想要小根堆
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> heap(compare);
int n,m,k,s;
int p,q;
int grade[MAXN];

int head[MAXN];
int to[MAXM];
int Next[MAXM];
int weight[MAXM];
int cnt=1;

int edge[MAXM][2];

int dis[MAXN];
bool vis[MAXN];

void add_edge(int u, int v, int w) {
    Next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

signed main()
{
    cin>>n>>m>>k>>s>>p>>q;
    for(int i=1;i<=n;i++){
        grade[i]=1;
        dis[i]=LONG_MAX;
    }
    for(int i=1;i<=k;i++){
        int h;
        cin>>h;
        grade[h]=3;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        if(grade[u]==3){
            grade[v]=grade[v]==3?3:2;
        }
        if(grade[v]==3){
            grade[u]=grade[u]==3?3:2;
        }
        edge[i][0]=u;
        edge[i][1]=v;
    }
    grade[1]=0;
    grade[n]=0;

    for(int i=1;i<=m;i++){
        int u = edge[i][0], v = edge[i][1];
        //cout<<u<<' '<<v<<endl;
        int wu = (grade[u] == 3) ? INT_MAX/2 : (grade[u] == 0 ? 0 : (grade[u] == 1 ? p : q));
        int wv = (grade[v] == 3) ? INT_MAX/2 : (grade[v] == 0 ? 0 : (grade[v] == 1 ? p : q));

        add_edge(u, v, wv); // 假设 add_edge 是一个您定义的函数，用于添加边和权重
        add_edge(v, u, wu); // 添加反向边和权重
    }
    dis[1]=0;
    heap.push({1,0});
    while(!heap.empty()){
        int u=heap.top().first;
        long w=heap.top().second;
        heap.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i>0;i=Next[i]){
            int v=to[i];
            if(!vis[v]&&dis[v]>weight[i]+w){
                dis[v]=weight[i]+w;
                heap.push({v,dis[v]});
            }
        }
    }
//    for(int i=1;i<=n;i++){
//        cout<<i<<' '<<grade[i]<<' '<<dis[i]<<endl;
//    }
    cout<<dis[n];
    return 0;
}
