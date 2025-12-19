#include<bits/stdc++.h>
using namespace std;
const int MAXN = 155;
const int INF = 1e9;

int n,m;
int val[MAXN][MAXN];
int cost[MAXN][MAXN];
int d[MAXN][MAXN];
bool vis[MAXN][MAXN];
int fa[MAXN][MAXN];

int find(int i,int j){
    if(j>=m+1){
        return m+1;
    }
    return fa[i][j]==j?j:fa[i][j]=find(i,fa[i][j]);
}

struct node{
    int x,y,dis;
};
struct compare{
    bool operator()(node a,node b){
        return a.dis>b.dis;
    }
};
priority_queue<node,vector<node>,compare>heap;

void dijkstra(int sx,int sy){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            fa[i][j]=j;
            vis[i][j]=false;
            d[i][j]=INF;
        }
    }
    d[sx][sy]=0;
    heap.push({sx,sy,0});
    while(!heap.empty()){
        node u=heap.top();
        heap.pop();
        int x=u.x,y=u.y,dis=u.dis;
        if(vis[x][y]){
            continue;
        }
        vis[x][y]=true;
        int f=find(x,y+1);
        fa[x][y]=f;

        int range=val[x][y];
        if(range==0){
            continue;
        }

        int sti=max(1,x-range);
        int eni=min(n,x+range);

        for(int i=sti;i<=eni;i++){
            int d1=range-abs(i-x);
            int l=max(1,y-d1);
            int r=min(m,y+d1);
            int j=find(i,l);
            while(j<=r){
                int d2=cost[x][y]+dis;
                if(d2<d[i][j]){
                    d[i][j]=d2;
                    heap.push({i,j,d2});
                }
                j=find(i,j+1);
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
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>cost[i][j];
        }
    }
    int x1,y1,x2,y2,x3,y3;
    cin>>x1>>y1>>x2>>y2>>x3>>y3;
    
    int d1=0,d2=0,d3=0;
    dijkstra(x1,y1);
    d2+=d[x2][y2];
    d3+=d[x3][y3];

    
    dijkstra(x2,y2);
    d1+=d[x1][y1];
    d3+=d[x3][y3];

    dijkstra(x3,y3);
    d2+=d[x2][y2];
    d1+=d[x1][y1];

    if(d1>=INF&&d2>=INF&&d3>=INF){
        cout<<"NO"<<endl;
    }
    else{
        if(d1<=d2&&d1<=d3){
            cout<<'X'<<endl<<d1<<endl;
        }
        else if(d2<=d3){
            cout<<'Y'<<endl<<d2<<endl;
        }
        else{
            cout<<'Z'<<endl<<d3<<endl;
        }
    }
    return 0;
}