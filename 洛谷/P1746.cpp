#include<bits/stdc++.h>
using namespace std;
#define MAX 1005

int n;
char s[MAX];
int nums[MAX][MAX],d[MAX][MAX];
int x1,x2,y1,y2;
struct coord{
    int x,y;
};
queue<coord>Q;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>s[j];
            nums[i][j]=s[j]-'0';
        }
    }
    cin>>x1>>y1>>x2>>y2;
    Q.push({x1,y1});
    d[x1][y1]=0;
    while(!Q.empty()){
        coord u=Q.front();
        Q.pop();
        int ux=u.x,uy=u.y;
        for(int k=0;k<4;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            if(x<=0||x>n||y<=0||y>n||d1[x][y]!=10000||nums[x][y]==0)
                continue;
            d[x][y]=d[ux][uy]+1;
            Q1.push({x,y});
            if(x==x2&&y==y2){
                printf("%d\n",d[x2][y2]);
                return 0;
            }
        }
    }
    return 0;
}
