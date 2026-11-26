// https://www.luogu.com.cn/problem/P3866
// 题意：第一行输入矩阵行数 M 和列数 N，接下来 M 行每行 N 个整数描述地图（-1 为障碍，0 为敌军起点，正数 x 为将该空地炸成障碍所需的炸药数）。
// 敌军可向四连通邻格移动（不可进障碍），若移出地图边界则失败；不能直接轰炸敌军所在格，求阻止所有敌军走出边界所需的最少炸药总量。
// 输出一个整数表示最少炸药数（保证有解）。
// 数据范围：对于 100% 的数据，1 <= M, N <= 30，矩阵每个正整数不超过 100。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 35;
const int MAXV = 2005;
const int MAXM = 10005;
const int INF = 1e10;

int n,m,s,t;
int val[MAXN][MAXN];

int dep[MAXV];//记录深度数组
int iter[MAXV];//当前弧数组 记录这个节点有效访问的第一条边的编号
int que[MAXV];

// 正反边从编号 2 开始配对，反向边编号为 e^1。
int cnt=2;
int head[MAXV];
int nxt[MAXM];
int to[MAXM];
int now[MAXM];//表示现在的流量
int cap[MAXM];//表示流量限制

int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    now[cnt]=0;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
    now[cnt]=0;
    head[v]=cnt++;
}

bool bfs(){
    // 只沿有剩余容量的边分层，汇点不可达时最大流已求完。
    for(int i=1;i<=n;i++){
        dep[i]=-1;
    }
    int ql=0,qr=0;
    dep[s]=0;
    que[qr++]=s;
    while(ql<qr){
        int u=que[ql++];
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=cap[i];
            int k=now[i];
            if(dep[v]<0&&(k<w)){
                dep[v]=dep[u]+1;
                que[qr++]=v;
            }
        }
    }
    return dep[t]>=0;// 如果汇点未被访问到，说明无增广路径
}

int dfs(int u,int f){
    // 当前弧沿分层图送出最多 f；增广后同时更新正反残量。
    if(u==t){
        return f;
    }
    int flow=0;
    // 引用当前弧，避免重复扫描已耗尽的边。
    for(int &i=iter[u];i;i=nxt[i]){
        int v=to[i];
        int w=cap[i];
        int k=now[i];
        if(dep[u]+1==dep[v]&&k<w){
            int d=dfs(v,min(f,w-k));
            if(d>0){
                now[i]+=d;
                now[i^1]-=d;//更新反向边
                flow+=d;
                f-=d;
                if(f==0){
                    break;
                }
            }
        }
    }
    return flow;
}

int maxflow(){
    int flow=0;
    while(bfs()){
        for(int i=1;i<=n;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

int id(int x,int y){
    return (x-1)*m+y;
}

int in(int x,int y){
    return id(x,y);
}

int out(int x,int y){
    return id(x,y)+n*m;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>val[i][j];
        }
    }
    s=2*n*m+1;
    t=s+1;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(val[i][j]==-1){
                continue;
            }

            int a=in(i,j);
            int b=out(i,j);

            if(val[i][j]==0){
                addedge(a,b,INF);
                addedge(s,a,INF);
            }
            else{
                addedge(a,b,val[i][j]);
            }

            if(i==1||i==n||j==1||j==m){
                addedge(b,t,INF);
            }

            for(int k=0;k<4;k++){
                int x=i+walk[k][0];
                int y=j+walk[k][1];

                if(x<1||x>n||y<1||y>m){
                    continue;
                }

                if(val[x][y]==-1){
                    continue;
                }

                addedge(b,in(x,y),INF);
            }
        }
    }

    n=t;
    cout<<maxflow()<<endl;
    return 0;
}
