#include<bits/stdc++.h>

using namespace std;

#define MAX 155

struct coord{
    int x,y;
};
queue<coord>Q;
int n,m,n1,m1,n2,m2;
int nums[MAX][MAX],d[MAX][MAX];
char s[MAX];
int walk[8][2]={{2,1},{2,-1},{-2,1},{-2,-1},{1,-2},{1,2},{-1,-2},{-1,2}};

int main()
{
    memset(d,-1,sizeof(d));
    scanf("%d %d",&m,&n);
    getchar();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%c",&s[j]);
            if(s[j]=='*'){
                nums[i][j]=0;
            }else{
                nums[i][j]=1;
            }
            if(s[j]=='H'){
                n2=i,m2=j;
            }
            if(s[j]=='K'){
                n1=i,m1=j;
            }
        }
        getchar();
    }
    Q.push({n1,m1});
    d[n1][m1]=0;
    while(!Q.empty()){
        coord u=Q.front();
        Q.pop();
        int ux=u.x,uy=u.y;
        for(int k=0;k<8;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            if(x<=0||x>n||y<=0||y>m||nums[x][y]==-1||d[x][y]!=-1)
                continue;
            Q.push({x,y});
            d[x][y]=d[ux][uy]+1;
            if(x==n2&&y==m2){
                printf("%d\n",d[x][y]);
                return 0;
            }
        }
    }
    return 0;
}

