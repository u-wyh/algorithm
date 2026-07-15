#include<bits/stdc++.h>
using namespace std;
const int MAXN = 805;

int nums[MAXN][MAXN];
int T;
int n,m;
int ai,aj,bi,bj,sti1,stj1,sti2,stj2;
int t[MAXN][MAXN];
int ta[MAXN],tb[MAXN];
bool vis[MAXN][MAXN],avis[MAXN][MAXN],bvis[MAXN][MAXN];
queue<pair<int,int>>q;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int main()
{
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                char c;
                cin>>c;
                if(c=='.'){
                    nums[i][j]=1;
                }
                else if(c=='X'){
                    nums[i][j]=-1;
                }
                else if(c=='M'){
                    ai=i;
                    aj=j;
                }
                else if(c=='G'){
                    bi=i;
                    bj=j;
                }
                else {
                    t[i][j]=0;
                    vis[i][j]=true;
                    q.push({i,j});
                }
            }
            while(!q.empty()){
                int ux=q.front().first;
                int uy=q.front().second;
                q.pop();
                for(int i=0;i<4;i++){
                    int x=ux+walk[i][0];
                    int y=uy+walk[i][1];
                    if(vis[x][y]||x>n||y>m||x==0||y==0)
                        continue;
                    q.push({x,y});
                    vis[x][y]=true;
                    t[x][y]=t[ux][uy]+1;
                }
            }
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    ta[i][j]=INT_MAX;
                    tb[i][j]=INT_MAX:
                }
            }
            avis[ai][aj]=true;
            ta[ai][aj]=0;
            q.push({ai,aj});
            while(!q.empty()){
                int ux=q.front().first;
                int uy=q.front().second;
                q.pop();
                for(int i=0;i<4;i++){
                    int x=ux+walk[i][0];
                    int y=uy+walk[i][1];
                    if(avis[x][y]||x>n||y>m||x==0||y==0||nums[x][y]==-1||ta[x][y])
                        continue;
                    q.push({x,y});
                    avis[x][y]=true;
                    ta[x][y]=ta[ux][uy]+1;
                }
            }
        }
    }
    return 0;
}
