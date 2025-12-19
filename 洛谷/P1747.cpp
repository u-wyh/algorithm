#include<bits/stdc++.h>
using namespace std;
#define MAX 25

struct coord{
    int x,y;
};
queue<coord>black;
queue<coord>white;
int bx,by,wx,wy;
int bd[MAX][MAX],wd[MAX][MAX];
int walk[12][2]={{2,2},{-2,2},{2,-2},{-2,-2},{2,1},{-2,1},{2,-1},{-2,-1},{1,2},{1,-2},{-1,-2},{-1,2}};

int main()
{
    cin>>bx>>by;
    cin>>wx>>wy;
    memset(bd,-1,sizeof(bd));
    memset(wd,-1,sizeof(wd));
    black.push({bx,by});
    bd[bx][by]=0;
    while(!black.empty()){
        coord u=black.front();
        black.pop();
        int ux=u.x,uy=u.y;
        if(ux==1&&uy==1){
            printf("%d\n",bd[ux][uy]);
            break;
        }
        for(int k=0;k<12;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            if(x==0||x>25||y>25||y==0||bd[x][y]!=-1){
                continue;
            }
            bd[x][y]=bd[ux][uy]+1;
            black.push({x,y});
        }
    }

    white.push({wx,wy});
    wd[wx][wy]=0;
    while(!white.empty()){
        coord u=white.front();
        white.pop();
        int ux=u.x,uy=u.y;
        if(ux==1&&uy==1){
            printf("%d\n",wd[ux][uy]);
            break;
        }
        for(int k=0;k<12;k++){
            int x=ux+walk[k][0],y=uy+walk[k][1];
            if(x==0||x>25||y>25||y==0||wd[x][y]!=-1){
                continue;
            }
            wd[x][y]=wd[ux][uy]+1;
            white.push({x,y});
        }
    }
    return 0;
}
