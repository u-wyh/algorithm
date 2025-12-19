#include<bits/stdc++.h>
using namespace std;
const int MAXN = 255;

int n;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int arr[MAXN][MAXN];
bool vis[MAXN][MAXN];
unordered_map<int,unordered_map<int,bool>>mmp;

struct node{
    int x,y;
};

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int bfs(int x,int y){
    queue<node>q;
    int ans=1;
    vis[x][y]=1;
    q.push({x,y});
    int col=arr[x][y];
    while(!q.empty()){
        int x=q.front().x;
        int y=q.front().y;
        q.pop();
        for(int i=0;i<4;i++){
            int nx=x+walk[i][0];
            int ny=y+walk[i][1];
            if(nx<1||nx>n||ny<1||ny>n||vis[nx][ny]||arr[nx][ny]!=col){
                continue;
            }
            ans++;
            vis[nx][ny]=1;
            q.push({nx,ny});
        }
    }
    return ans;
}

int bfs(int x,int y,int x1,int y1){
    queue<node>q;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            vis[i][j]=false;
        }
    }
    int col=arr[x][y];
    int col1=arr[x1][y1];
    int ans=2;
    vis[x][y]=1;
    vis[x1][y1]=1;
    q.push({x,y});
    q.push({x1,y1});
    while(!q.empty()){
        int x=q.front().x;
        int y=q.front().y;
        q.pop();
        for(int i=0;i<4;i++){
            int nx=x+walk[i][0];
            int ny=y+walk[i][1];
            if(nx<1||nx>n||ny<1||ny>n||vis[nx][ny]||(arr[nx][ny]!=col&&arr[nx][ny]!=col1)){
                continue;
            }
            ans++;
            vis[nx][ny]=1;
            q.push({nx,ny});
        }
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            arr[i][j]=read();
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(!vis[i][j]){
                ans=max(ans,bfs(i,j));
            }
        }
    }
    cout<<ans<<endl;
    ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=0;k<4;k++){
                int x=i+walk[k][0];
                int y=j+walk[k][1];
                if(x<1||x>n||y<1||y>n||arr[i][j]==arr[x][y]||mmp[arr[i][j]][arr[x][y]]){
                    continue;
                }
                ans=max(ans,bfs(i,j,x,y));
                mmp[arr[i][j]][arr[x][y]]=mmp[arr[x][y]][arr[i][j]]=1;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}