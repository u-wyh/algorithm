#include<bits/stdc++.h>
#include<queue>
#define inf 0x3f3f3f3f
using namespace std;
int n,m;
int a[110][110];//保存地图
struct node{
    int x,y;
    int num;
}s,t;
queue<node> q;
void dfs(int fx,node u){ //fx记录方向（1上2下3左4右） u为当前所在点
    int x=u.x,y=u.y,p=u.num;
    if(a[x][y]<p || a[x][y]==inf) return;
    if(x<1 || y<1 || x>n || y>m) return;

    if(fx==1){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(1,(node){x-1,y,p});
    }
    if(fx==2){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(2,(node){x+1,y,p});
    }
    if(fx==3){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(3,(node){x,y-1,p});
    }
    if(fx==4){
        a[x][y]=p;
        q.push((node){x,y,p});
        dfs(4,(node){x,y+1,p});
    }
}

void bfs(){
    while(!q.empty()){
        node u=q.front(),v=q.front();
        q.pop();
        u.num++;
        v=u; v.x=u.x-1;//上
        dfs(1,v);
        v=u; v.x=u.x+1;//下
        dfs(2,v);
        v=u; v.y=u.y-1;//左
        dfs(3,v);
        v=u; v.y=u.y+1;//右
        dfs(4,v);
    }
}
int main(){
    cin>>m>>n;
    char zwh;
    memset(a,inf,sizeof(a));
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++) a[i][j]=inf-1;
    //如果地图范围全部是比答案小的数字（比如0），那么在dfs染色的时候就会直接返回，导致错误。
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf(" %c",&zwh);
            if(zwh=='C'){
                if(s.x) t.x=i,t.y=j,t.num=0;//找到起点和终点
                else s.x=i,s.y=j,s.num=0;
            }
            if(zwh=='*'){
                a[i][j]=inf;
            }

        }
    }
    q.push(s);
    bfs();
    cout<<a[t.x][t.y]-1;//注意减一
    return 0;
}
