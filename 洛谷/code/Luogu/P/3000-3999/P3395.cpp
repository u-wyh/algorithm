#include<bits/stdc++.h>
using namespace std;

int n;
int death[1005][1005],t[1005][1005];
int T;
struct coord{
    int x,y;
};
queue<coord>Q;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int main()
{
    cin>>T;
    while(T--){
        memset(death,10000,sizeof(death));
        memset(t,10000,sizeof(t));
        cin>>n;
        int x,y;
        for(int i=1;i<=2*n-2;i++){
            cin>>x>>y;
            death[x][y]=i;
        }
        t[1][1]=0;
        Q.push({1,1});
        while(!Q.empty()){
            coord u=Q.front();
            Q.pop();
            int ux=u.x,uy=u.y;
            for(int k=0;k<4;k++){
                int x=ux+walk[k][0],y=uy+walk[k][1];
                if(x==0||x>n||y>n||y==0||t[ux][uy]+1>=death[x][y]||t[x][y]!=10000){
                    continue;
                }
                t[x][y]=t[ux][uy]+1;
                Q.push({x,y});
            }
        }
        if(t[n][n]!=10000){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}
