#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m,d;

int fa[MAXN];
char s[MAXN];

int walk[3][2]={{0,-1},{1,0},{-1,0}};
int walk2[3][2]={{0,1},{1,0},{-1,0}};

struct node{
    int x,y;
};
queue<node>q;

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        if(((fx-1)%m)>((fy-1)%m)){
            fa[fy]=fx;
        }
        else{
            fa[fx]=fy;
        }
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d %d %d",&n,&m,&d);

        vector<vector<int>>vec(n+1,vector<int>(m+1,0));
        vector<vector<bool>>vis(n+1,vector<bool>(m+1,0));
        vector<vector<bool>>visit(n+1,vector<bool>(m+1,0));

        for(int i=1;i<=n;i++){
            scanf("%s",s+1);
            for(int j=1;j<=m;j++){
                vec[i][j]=s[j]-'0';
            }
        }

        q.push({1,m});
        vis[1][m]=true;
        while(!q.empty()){
            node u=q.front();
            q.pop();
            for(int i=0;i<3;i++){
                int x=u.x+walk[i][0];
                int y=u.y+walk[i][1];
                if(x>n||x<1||y>m||y<1||vis[x][y]||vec[x][y]){
                    continue;
                }
                vis[x][y]=true;
                q.push({x,y});
            }
        }
        
        q.push({1,1});
        visit[1][1]=true;
        while(!q.empty()){
            node u=q.front();
            q.pop();
            for(int i=0;i<3;i++){
                int x=u.x+walk2[i][0];
                int y=u.y+walk2[i][1];
                if(x>n||x<1||y>m||y<1||vec[x][y]||visit[x][y]){
                    continue;
                }
                visit[x][y]=true;
                q.push({x,y});
            }
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(vis[i][j]&&visit[i][j]){
                    vis[i][j]=true;
                }
                else{
                    vis[i][j]=false;
                }
            }
        }
        // for(int i=1;i<=n;i++){
        //     for(int j=1;j<=m;j++){
        //         cout<<vis[i][j]<<' ';
        //     }
        //     cout<<endl;
        // }
        // cout<<endl;
        for(int i=1;i<=n*m;i++){
            fa[i]=i;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(vis[i][j]||vec[i][j]||!visit[i][j]){
                    continue;
                }
                for(int k=0;k<3;k++){
                    int x=i+walk2[k][0];
                    int y=j+walk2[k][1];
                    if(x>n||x<1||y>m||y<1||vec[x][y]){
                        continue;
                    }
                    un((i-1)*m+j,(x-1)*m+y);
                }
            }
        }
        bool flag=false;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(vis[i][j]||vec[i][j]){
                    continue;
                }
                int x=find((i-1)*m+j);
                if(x==((i-1)*m+j)){
                    continue;
                }
                if(((x-1)%m+1-j+1)>=d){
                    flag=true;
                    break;
                }
            }
            if(flag){
                break;
            }
        }
        if(flag){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}