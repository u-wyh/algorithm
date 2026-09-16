#include<bits/stdc++.h>
using namespace std;

void dfs(int x,int y,int mou);
long long a[11][11],dir[4][2]={1,0,-1,0,0,1,0,-1};
int tx,ty,lx,ly,n,m,mou=6,times=0,minans=1<<30;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            if(a[i][j]==2){
                tx=i;ty=j;
                //记录开始点
            }
            if(a[i][j]==3){
                lx=i;ly=j;
                //记录结束点
            }
        }
    dfs(tx,ty,mou);
    if(minans!=1<<30) cout<<minans<<endl;
    else cout<<-1<<endl;
    return 0;
}
void dfs(int x,int y,int mou){
	if(mou==0||times>m*n||times>minans) return;
	if(a[x][y]==4) mou=6;
    if(x==lx&&y==ly) minans=min(times,minans);
    else{
        for(int i=0;i<4;i++){
            tx=x+dir[i][0];
            ty=y+dir[i][1];
            if(tx<=0||tx>n||ty<=0||ty>m||a[tx][ty]==0) continue;
            //边界判断和是否撞墙
            ++times;
            dfs(tx,ty,mou-1);
			--times;
        }
    }
}
