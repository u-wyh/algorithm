#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int INF = 1e9;

int n,m;
int nums[MAXN][MAXN];
int t[MAXN][MAXN][4];
bool vis[MAXN][MAXN][4];
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int nxt[4]={1,2,3,1};

struct node{
    int val;
    int x,y,t;
};
struct compare{
    bool operator()(node a,node b){
        return a.val>b.val;
    }
};
priority_queue<node,vector<node>,compare>heap;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>nums[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=3;k++){
                t[i][j][k]=INF;
            }
        }
    }
    t[1][1][0]=0;
    heap.push({0,1,1,0});
    while(!heap.empty()){
        node u=heap.top();
        heap.pop();
        if(vis[u.x][u.y][u.t]){
            continue;
        }
        if(u.x==n&&u.y==n){
            cout<<u.val<<endl;
            return 0;
        }
        vis[u.x][u.y][u.t]=true;
        for(int i=0;i<4;i++){
            int x=u.x+walk[i][0];
            int y=u.y+walk[i][1];
            int ti=nxt[u.t];
            if(x<1||x>n||y<1||y>n||vis[x][y][ti]){
                continue;
            }
            if((u.val+m+(ti==3?nums[x][y]:0))<t[x][y][ti]){
                t[x][y][ti]=u.val+m+(ti==3?nums[x][y]:0);
                heap.push({t[x][y][ti],x,y,ti});
            }
        }
    }
    return 0;
}
