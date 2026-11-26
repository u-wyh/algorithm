// https://www.luogu.com.cn/problem/P1699
// 题意：给定农场地图，从湖 L 到着火的牛棚 B 找一条上下左右相连的路径，绕开岩石 R。求路径中最少要占用几个空格，湖和牛棚两格不计。
// 数据范围：地图固定为 10×10，B、L、R 各出现一次，B 和 L 不相邻。

#include<bits/stdc++.h>

using namespace std;

struct coord{
    int x,y;
};
int d[11][11];
int nums[11][11];
char s[11];
int n1,n2,m1,m2;
queue<coord>Q;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int main()
{
    memset(d,-1,sizeof(d));
    for(int i=1;i<11;i++){
        for(int j=1;j<11;j++){
            scanf("%c",&s[j]);
            if(s[j]=='B'){
                nums[i][j]=1;
                d[i][j]=0;
                n1=i,m1=j;
            }
            if(s[j]=='R')
                nums[i][j]=-1;
            if(s[j]=='L'){
                nums[i][j]=1;
                n2=i,m2=j;
            }
            if(s[j]=='.'){
                nums[i][j]=1;
            }
        }
        getchar();
    }
    Q.push({n1,m1});
    while(!Q.empty()){
        coord u=Q.front();
        Q.pop();
        int ux=u.x,uy=u.y;
        for(int k=0;k<4;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            if(x<0||x>10||y<0||y>10||d[x][y]!=-1||nums[x][y]==-1){
                continue;
            }
            d[x][y]=d[ux][uy]+1;
            Q.push({x,y});
            if(x==n2&&y==m2){
                printf("%d\n",d[x][y]-1);
                return 0;
            }
        }
    }
    return 0;
}
