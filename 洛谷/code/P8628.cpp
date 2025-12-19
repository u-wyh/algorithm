#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;

int n;
char s[MAXN][MAXN];
int arr[MAXN][MAXN];
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
struct coord{
    int x,y,w;
};
queue<coord>q;
bool vis[MAXN][MAXN];

int main()
{
    cin>>n;
    int sti,stj,eni,enj;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>s[i][j];
            if(s[i][j]=='A'){
                sti=i;
                stj=j;
                arr[i][j]=2;
                q.push({i,j,0});
                vis[i][j]=true;
            }else if(s[i][j]=='B'){
                eni=i;
                enj=j;
            }else if(s[i][j]=='+'){
                arr[i][j]=1;
            }else{
                arr[i][j]=0;
            }
        }
    }
    while(!q.empty()){
        coord cur=q.front();
        int x=cur.x,y=cur.y;
        //vis[x][y]=true;
        q.pop();
        for(int i=0;i<4;i++){
            int ux=x+walk[i][0],uy=y+walk[i][1];
            if(ux<=0||ux>n||uy>n||uy<=0||arr[ux][uy]==arr[x][y]||vis[ux][uy]){
                continue;
            }
            if(ux==eni&&uy==enj){
                cout<<cur.w+1;
                return 0;
            }
            vis[ux][uy]=true;
            q.push({ux,uy,cur.w+1});
        }
    }
    cout<<-1;
    return 0;
}
