#include<bits/stdc++.h>
using namespace std;
const int MAXN = 35;
const int MAXV = 35*35;
const int MAXE = MAXV*MAXV;
const int INF = 1e9;

int n,m,st,en;
int walk[8][2]={{1,2},{-1,2},{1,-2},{-1,-2},{2,1},{2,-1},{-2,1},{-2,-1}};
int val[MAXN][MAXN];
int id[MAXN][MAXN];

int dis[MAXN][MAXN];
bool visit[MAXN][MAXN];

int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int weight[MAXE];
int cnt=1;

struct node{
    int pos,dis;
};
struct compare{
    bool operator()(const node &a,const node&b){
        return a.dis>b.dis;
    }
};
priority_queue<node,vector<node>,compare>heap;
bool vis[MAXV];
int dist[MAXV];
long long ways[MAXV];

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

// void bfs(int sx,int sy){
//     for(int i=1;i<=n;i++){
//         for(int j=1;j<=m;j++){
//             dis[i][j]=INF;
//             visit[i][j]=false;
//         }
//     }
//     dis[sx][sy]=0;
//     deque<pair<int,int>>dq;
//     dq.push_back({sx,sy});
//     while(!dq.empty()){
//         pair<int,int>tmp=dq.front();
//         dq.pop_front();
//         int x=tmp.first;
//         int y=tmp.second;
//         if(visit[x][y]){
//             continue;
//         }
//         visit[x][y]=true;

//         for(int i=0;i<8;i++){
//             int nx=x+walk[i][0];
//             int ny=y+walk[i][1];
//             if(nx>0&&nx<=n&&ny>0&&ny<=m&&val[nx][ny]!=2){
//                 // if(val[nx][ny]==1){
//                 //     dq.push_front()
//                 // }
//                 int w=(val[nx][ny]==1||val[nx][ny]==4)?0:1;
//                 if(dis[x][y]+w<dis[nx][ny]){
//                     dis[nx][ny]=dis[x][y]+w;
//                     if(w==0){
//                         dq.push_front({nx,ny});
//                     }
//                     else{
//                         dq.push_back({nx,ny});
//                     }
//                 }
//             }
//         }
//     }
//     for(int i=1;i<=n;i++){
//         for(int j=1;j<=m;j++){
//             if(dis[i][j]!=INF&&val[i][j]!=1){
//                 if(i!=sx||j!=sy){
//                     addedge(id[sx][sy],id[i][j],dis[i][j]);
//                 }
//             }
//         }
//     }
// }

void dfs(int s,int x,int y){
    visit[x][y]=true;
    for(int i=0;i<8;i++){
        int nx=x+walk[i][0];
        int ny=y+walk[i][1];
        if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
        if (visit[nx][ny]) continue;
        
        if (val[nx][ny] == 1) {
            // 遇到莲花，继续免费探索
            dfs(s, nx, ny);
        } else if (val[nx][ny] != 2&&val[nx][ny]!=3) {
            // 遇到空水或终点，记录边
            visit[nx][ny] = true;
            int weight = (val[nx][ny] == 4) ? 0 : 1;
            addedge(s,id[nx][ny],weight);
        }
    }
}

void dijkstra(){
    for(int i=1;i<=n*m;i++){
        dist[i]=INF;
    }
    dist[st]=0;
    ways[st]=1;
    heap.push({st,0});
    while(!heap.empty()){
        node tmp=heap.top();
        heap.pop();
        int u=tmp.pos;
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=weight[i];
            if(dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                ways[v]=ways[u];
                heap.push({v,dist[v]});
            }
            else if(dist[u]+w==dist[v]){
                ways[v]+=ways[u];
            }
        }
    }
}

void zero_one_bfs() {
    for(int i = 1; i <= n * m; i++) {
        dist[i] = INF;
        ways[i] = 0;
    }
    
    dist[st] = 0;
    ways[st] = 1;
    
    deque<int> dq;
    dq.push_back(st);
    
    while(!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        
        
        for(int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            int w = weight[i];
            
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                ways[v] = ways[u];
                
                if(w == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            } else if(dist[u] + w == dist[v]) {
                ways[v] += ways[u];
                
                // if(w == 0) {
                //     dq.push_front(v);
                // } else {
                //     dq.push_back(v);
                // }
            }
        }
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>val[i][j];
            id[i][j]=(i-1)*m+j;
            if(val[i][j]==3){
                st=id[i][j];
            }
            else if(val[i][j]==4){
                en=id[i][j];
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(val[i][j]==0||val[i][j]==3){
                memset(visit,false,sizeof(visit));
                dfs(id[i][j],i,j);
            }
        }
    }
    // dijkstra();
    zero_one_bfs();

    if(dist[en]==INF){
        cout<<-1<<endl;
    }
    else{
        cout<<dist[en]<<endl<<ways[en]<<endl;
    }
    return 0;
}