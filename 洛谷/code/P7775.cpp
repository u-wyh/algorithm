#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;

struct node{
    int x,y;
};
int dis[MAXN][MAXN];
bool vis[MAXN][MAXN];
int n,m;
queue<node>q;
int sti,stj,eni,enj;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
queue<node>Q;

bool check(int limit){
    if(dis[sti][stj]<limit||dis[eni][enj]<limit)
        return false;
    Q.push({sti,stj});
    vis[sti][stj]=true;
    int f=0;
    while(!Q.empty()){
        node u=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            int x=u.x+walk[i][0];
            int y=u.y+walk[i][1];
            if(dis[x][y]<limit||x==0||y==0||x>n||y>m||vis[x][y]){
                continue;
            }
            Q.push({x,y});
            vis[x][y]=true;
            if(x==eni&&y==enj){
                f=1;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            vis[i][j]=false;
        }
    }
    if(f){
        return true;
    }
    return false;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            dis[i][j]=-1;
            char c;
            cin>>c;
            if(c=='+'){
                q.push({i,j});
                dis[i][j]=0;
            }
            else if(c=='V'){
                sti=i;
                stj=j;
            }
            else if(c=='J'){
                eni=i;
                enj=j;
            }
        }
    }
    while(!q.empty()){
        node u=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int x=u.x+walk[i][0];
            int y=u.y+walk[i][1];
            if(dis[x][y]!=-1||x==0||y==0||x>n||y>m){
                continue;
            }
            q.push({x,y});
            dis[x][y]=dis[u.x][u.y]+1;
        }
    }
//    cout<<sti<<' '<<stj<<' '<<eni<<' '<<enj<<endl;
//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=m;j++){
//            cout<<dis[i][j]<<' ';
//        }
//        cout<<endl;
//    }
    int l=0,r=n+m;
    int ans=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    cout<<ans;
    return 0;
}
