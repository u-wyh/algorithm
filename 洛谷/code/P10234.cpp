#include<bits/stdc++.h>
using namespace std;
#define MAX 2005

int n,m,t;
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};//1R  2L  3D  4U
struct coord{
    int x,y;
};
queue<coord>Q;

int main()
{
    cin>>t;
    while(t--){
        cin>>n>>m;
        char s[n+1][m+1];
        int d1[n+1][m+1];
        char d2[n+1][m+1];
        memset(d2,-1,sizeof(d2));
        memset(d1,-1,sizeof(d1));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>s[i][j];
            }
        }
        Q.push({1,1});
        d1[1][1]=0;
        d2[1][1]='0';
        while(!Q.empty()){
            coord u=Q.front();
            int ux=u.x,uy=u.y;
            if(ux==n&&uy==m)
                break;
            Q.pop();
            for(int i=0;i<4;i++){
                int x=ux+walk[i][0],y=uy+walk[i][1];
                if(x==0||y==0||x>n||y>m||d1[x][y]!=-1||s[x][y]==s[ux][uy])
                    continue;
                d1[x][y]=d1[ux][uy]+1;
                if(i==0)
                    d2[x][y]='R';
                if(i==1)
                    d2[x][y]='L';
                if(i==2)
                    d2[x][y]='D';
                if(i==3)
                    d2[x][y]='U';
                Q.push({x,y});
            }
        }
        if(d1[n][m]==-1)
            printf("-1\n");
        else{
            printf("%d\n",d1[n][m]);
            stack<char>str;
            int x=n,y=m;
            for(int i=1;i<=d1[n][m];i++){
                str.push(d2[x][y]);
                if(d2[x][y]='D'){
                    y-=1 ;
                }
                if(d2[x][y]='R'){
                    x-=1 ;
                }
                if(d2[x][y]='U'){
                    y+=1 ;
                }
                if(d2[x][y]='L'){
                    x+=1 ;
                }
            }
            for(int i=1;i<=d1[n][m];i++){
                cout<<str.top();
                str.pop();
            }
        }
    }
    return 0;
}
