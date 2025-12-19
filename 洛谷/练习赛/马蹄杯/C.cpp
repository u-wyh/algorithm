#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;

int n;
char s[2][MAXN];
int walk[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int col[2][MAXN];
int color;

void dfs(int x,int y,int c){
    col[x][y]=c;
    for(int i=0;i<4;i++){
        int nx=x+walk[i][0];
        int ny=y+walk[i][1];
        if(nx<0||nx>1||ny<=0||ny>n||col[nx][ny]||s[nx][ny]!=s[x][y]){
            continue;
        }
        dfs(nx,ny,c);
    }
}

int main()
{
    cin>>n;
    scanf("%s",s[0]+1);
    scanf("%s",s[1]+1);
    for(int i=0;i<=1;i++){
        for(int j=1;j<=n;j++){
            if(col[i][j]==0){
                ++color;
                dfs(i,j,color);
            }
        }
    }
    cout<<color<<endl;
    return 0;
}