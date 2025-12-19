#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

struct node{
    int x,y;
    int goal;
};
int nums[MAXN][MAXN];
int l,r,ans=0;
int n,m;
queue<node>q;
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
bool vis[MAXN][MAXN];

void clean(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            vis[i][j]=false;
        }
    }
    while(!q.empty()){
        q.pop();
    }
}

bool bfs(int limit){
    for(int i=1;i<=m;i++){
        vis[1][i]=true;
        q.push({1,i,0});
    }
    while(!q.empty()){
        node u=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int x=u.x+walk[i][0];
            int y=u.y+walk[i][1];
            if(vis[x][y]||x>n||y>m||x==0||y==0||nums[x][y]>limit){
                continue;
            }
            int goal=max(u.goal,nums[x][y]);
            if(x==n&&goal==limit)
                return 1;
            vis[x][y]=true;
            q.push({x,y,goal});
        }
    }
    return 0;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>nums[i][j];
            r=max(nums[i][j],r);
        }
    }
    while(l<=r){
        clean();
        int mid=(l+r)>>1;
        if(bfs(mid)){
            r=mid-1;
            ans=mid;
        }else{
            l=mid+1;
        }
    }
    cout<<ans;
    return 0;
}
