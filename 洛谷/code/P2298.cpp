#include<bits/stdc++.h>
using namespace std;
#define MAX 2005

int n,m,n1,m1,n2,m2;
int nums[MAX][MAX],d[MAX][MAX];
char s[MAX];
struct coord{
    int x,y;
};
queue<coord>Q;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int main()
{
    memset(d,-1,sizeof(d));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>s[j];
            if(s[j]=='#'){
                nums[i][j]=0;
            }else{
                nums[i][j]=1;
                if(s[j]=='m'){
                    n1=i,m1=j;
                }
                if(s[j]=='d'){
                    n2=i,m2=j;
                }
            }
        }
    }
    Q.push({n1,m1});
    d[n1][m1]=0;
    while(!Q.empty()){
        coord u=Q.front();
        Q.pop();
        int ux=u.x,uy=u.y;
        for(int k=0;k<4;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            if(x==0||x>n||y>m||y==0||d[x][y]!=-1||nums[x][y]==0){
                continue;
            }
            d[x][y]=d[ux][uy]+1;
            Q.push({x,y});
            if(x==n2&&y==m2){
                printf("%d\n",d[x][y]);
                return 0;
            }
        }
    }
    printf("No Way!\n");
    return 0;
}
