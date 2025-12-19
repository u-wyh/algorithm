#include<bits/stdc++.h>

#define MAX 305
using namespace std;

struct coord{
    int x,y;
};
queue<coord>Q;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int death[MAX][MAX],ans[MAX][MAX];

int main()
{
    int m,Ans=100000;
    scanf("%d",&m);
    memset(ans,-1,sizeof(ans));
    memset(death,1e9,sizeof(death));
    while(m--){
        int x,y,t;
        scanf("%d %d %d",&x,&y,&t);
        if(x>=0&&y>=0)
            death[x][y]=min(death[x][y],t);
        for(int i=0;i<4;i++){
            if(x+walk[i][0]>=0&&y+walk[i][1]>=0)
                death[x+walk[i][0]][y+walk[i][1]]=min(death[x+walk[i][0]][y+walk[i][1]],t);
        }
    }
    Q.push({0,0});
    ans[0][0]=0;
    while(!Q.empty()){
        coord now=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            int x=now.x+walk[i][0],y=now.y+walk[i][1];
            if(x<0||y<0||ans[x][y]!=-1||ans[now.x][now.y]+1>=death[x][y]){
                continue;
            }
            ans[x][y]=ans[now.x][now.y]+1;
            Q.push({x,y});
        }
    }
    for(int i=0;i<305;i++){
        for(int j=0;j<305;j++){
            if(death[i][j]>1000&&ans[i][j]!=-1)
                Ans=min(Ans,ans[i][j]);
        }
    }
    if(Ans==100000)
        printf("-1\n");
    else
        printf("%d\n",Ans);
    return 0;
}

