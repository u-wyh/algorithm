#include<iostream>
using namespace std;
bool a[55][55];
bool aa[55][55][4];
int b[10000][4];
int n,m,x0,y0,x1,y1;
int step=1,flag=0;
char c;
int frot=0,rear=1;
int turn(int u, bool lr)
{
    if(lr==0)
    {
        if(u==0) return 3;
        else return u-1;
    }
    else
    {
        if(u==3) return 0;
        else return u+1;
    }
}
void bfs()
{
    int i,x,y,d,step;
    while(frot < rear)
    {
        x = b[frot][0],y = b[frot][1],d = b[frot][2],step = b[frot][3];
        if(x==x1 && y==y1)
        {
            cout << b[frot][3];
            return;
        }
        if(aa[x][y][turn(d,0)]==0){
            aa[x][y][turn(d,0)]=1;
            b[rear][0]=x;
            b[rear][1]=y;
            b[rear][2]=turn(d,0);
            b[rear++][3]=step+1;
        }
        if(aa[x][y][turn(d,1)]==0){
            aa[x][y][turn(d,1)]=1;
            b[rear][0]=x;
            b[rear][1]=y;
            b[rear][2]=turn(d,1);
            b[rear++][3]=step+1;
        }
        for(i=1;i<=3;i++){
            if(d==0 && aa[x-i][y][d]==0 && a[x-1][y]==0 && a[x-i][y]==0 && x-i>0){
                aa[x-i][y][d]=1;
                b[rear][0]=x-i;
                b[rear][1]=y;
                b[rear][2]=d;
                b[rear++][3]=step+1;
            }
            if(d==2 && aa[x+i][y][d]==0 && a[x+1][y]==0 && a[x+i][y]==0 && x+i<n){
                aa[x+i][y][d]=1;
                b[rear][0]=x+i;
                b[rear][1]=y;
                b[rear][2]=d;
                b[rear++][3]=step+1;
            }
            if(d==3 && aa[x][y-i][d]==0 && a[x][y-1]==0 && a[x][y-i]==0 && y-i>0){
                aa[x][y-i][d]=1;
                b[rear][0]=x;
                b[rear][1]=y-i;
                b[rear][2]=d;
                b[rear++][3]=step+1;
            }
            if(d==1 && aa[x][y+i][d]==0 && a[x][y+1]==0 && a[x][y+i]==0 && y+i<m){
                aa[x][y+i][d]=1;
                b[rear][0]=x;
                b[rear][1]=y+i;
                b[rear][2]=d;
                b[rear++][3]=step+1;
            }
        }
        frot++;
    }
    cout << -1;
}
int main()
{
    int i,j,d,t;
    cin>>n>>m;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++){
            cin>>t;
            if(t==1)
                a[i][j] = a[i-1][j] = a[i][j-1] = a[i-1][j-1] = 1;
        }
    cin >> x0 >> y0 >> x1 >> y1 >> c;
    if(c=='N') d = 0;
    else if(c=='E') d = 1;
    else if(c=='S') d = 2;
    else d = 3;
    aa[x0][y0][d] = 1;
    b[0][0] = x0,b[0][1] = y0, b[0][2] = d, b[0][3] = 0;
    bfs();
    return 0;
}

