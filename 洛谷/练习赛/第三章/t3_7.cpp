#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int MAXK = 15;
const int INF = 1e9;

int n,k,a,b,c;
int dist[MAXN][MAXN][MAXK];
bool vis[MAXN][MAXN][MAXK];
int oil[MAXN][MAXN];
int walk[4][2]={{0,-1},{0,1},{-1,0},{1,0}};

struct node{
    int x,y,o;
    int cost;
};
struct compare{
    bool operator()(const node &a,const node &b){
        return a.cost>b.cost;
    }
};
priority_queue<node,vector<node>,compare>heap;

void dijkstra(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int o=0;o<=k;o++){
                dist[i][j][o]=INF;
            }
        }
    }
    dist[1][1][k]=0;
    heap.push({1,1,k,0});
    while(!heap.empty()){
        node tmp=heap.top();
        heap.pop();
        int x=tmp.x;
        int y=tmp.y;
        int o=tmp.o;
        int cost=tmp.cost;
        if(vis[x][y][o]){
            continue;
        }
        vis[x][y][o]=true;
        if(x==n&&y==n){
            cout<<cost<<endl;
            return ;
        }

        if(oil[x][y]==1&&o<k){
            // 必须要加油的情况  此时不能直接走路
            int nc=cost+a;
            if(dist[x][y][k]>nc){
                dist[x][y][k]=nc;
                heap.push({x,y,k,nc});
            }
            // continue;
        }

        if(oil[x][y]==0){
            // 可以设置也可以不设置加油站  这是设置的情况
            int nc=cost+c+a;
            if(dist[x][y][k]>nc){
                dist[x][y][k]=nc;
                heap.push({x,y,k,nc});
            }
        }
        
        for(int i=0;i<4;i++){
            int nx=x+walk[i][0];
            int ny=y+walk[i][1];
            int no=o-1;
            if(nx<1||nx>n||ny<1||ny>n||no<0){
                continue;
            }
            int nc=((i==0||i==2)?b:0)+cost;
            if(dist[nx][ny][no]>nc){
                dist[nx][ny][no]=nc;
                heap.push({nx,ny,no,dist[nx][ny][no]});
            }
        }
    }
}

int main()
{
    cin>>n>>k>>a>>b>>c;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>oil[i][j];
        }
    }
    dijkstra();
    return 0;
}
/*
9 3 2 3 6
0 0 0 0 1 0 0 0 0 
0 0 0 1 0 1 1 0 0 
1 0 1 0 0 0 0 1 0 
0 0 0 0 0 1 0 0 1 
1 0 0 1 0 0 1 0 0 
0 1 0 0 0 0 0 1 0
0 0 0 0 1 0 0 0 1
1 0 0 1 0 0 0 1 0
0 1 0 0 0 0 0 0 0
*/