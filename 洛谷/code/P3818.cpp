#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n,m,d,r;
int st[MAXN][MAXN][2];
int arr[MAXN][MAXN];
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
struct node{
    int x,y,u;
};
queue<node>q;

int main()
{
    cin>>n>>m>>d>>r;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            arr[i][j]= c=='.';
        }
    }
    st[1][1][0]=0;
    q.push({1,1,0});
    while(!q.empty()){
        node u=q.front();
        q.pop();
        if(u.x==n&&u.y==m){
            break;
        }
        for(int i=0;i<4;i++){
            int x=u.x+walk[i][0];
            int y=u.y+walk[i][1];
            if(x<=n&&x>0&&y<=m&&y>0&&arr[x][y]&&st[x][y][u.u]==0){
                q.push({x,y,u.u});
                st[x][y][u.u]=st[u.x][u.y][u.u]+1;
            }
        }
        int x=u.x+d,y=u.y+r;
        if(u.u==0&&x<=n&&x>0&&y<=m&&y>0&&arr[x][y]&&st[x][y][1]==0){
            q.push({x,y,1});
            st[x][y][1]=st[u.x][u.y][u.u]+1;
        }
    }
    if(st[n][m][0]==0&&st[n][m][1]==0){
        cout<<-1<<endl;
    }
    else{
        if(st[n][m][0]==0){
            cout<<st[n][m][1]<<endl;
        }
        else if(st[n][m][1]==0){
            cout<<st[n][m][0]<<endl;
        }
        else{
            cout<<min(st[n][m][0],st[n][m][1])<<endl;
        }
    }
    return 0;
}
