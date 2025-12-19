#include<bits/stdc++.h>
using namespace std;
const int MAXN = 45;
const int MAXV = 65005;
const int MAXE = 4e5+5;
const int INF = 1e9;

int p,q,r,d;
int s,t;

int val[MAXN][MAXN][MAXN];
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int dep[MAXV];
int iter[MAXV];

int cnt=2;
int head[MAXV];
int nxt[MAXE];
int to[MAXE];
int now[MAXE];
int cap[MAXE];

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
    for(int i=1;i<=t;i++){
        dep[i]=-1;
    }
    queue<int>q;
    dep[s]=0;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            int w=cap[i];
            int k=now[i];
            if(dep[v]<0&&(k<w)){
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[t]>=0;
}

int dfs(int u,int f){
    if(u==t){
        return f;
    }
    int flow=0;
    for(int &i=iter[u];i;i=nxt[i]){
        int v=to[i];
        int w=cap[i];
        int k=now[i];
        if(dep[u]+1==dep[v]&&k<w){
            int d=dfs(v,min(f,w-k));
            if(d>0){
                now[i]+=d;
                now[i^1]-=d;
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
        for(int i=1;i<=t;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

int id(int x,int y,int z){
    return (z-1)*p*q+(x-1)*q+y;
}

int main()
{
    scanf("%d %d %d %d",&p,&q,&r,&d);
    for(int z=1;z<=r;z++){
        for(int x=1;x<=p;x++){
            for(int y=1;y<=q;y++){
                scanf("%d",&val[x][y][z]);
            }
        }
    }

    s = p*q*(r+1)+1;
    t = s+1;
    for(int x=1;x<=p;x++){
        for(int y=1;y<=q;y++){
            addedge(s,id(x,y,1),INF);
            for(int z=1;z<=r;z++){
                addedge(id(x,y,z),id(x,y,z+1),val[x][y][z]);
            }
            addedge(id(x,y,r+1),t,INF);
        }
    }

    for(int x=1;x<=p;x++){
        for(int y=1;y<=q;y++){
            for(int i=0;i<4;i++){
                int nx=x+walk[i][0];
                int ny=y+walk[i][1];
                if(nx>=1&&nx<=p&&ny>=1&&ny<=q){
                    for(int z=d+1;z<=r+1;z++){
                        // 这里要注意  边的方向一定是从高层指向低层
                        // 这样才可以体现出约束
                        addedge(id(x,y,z),id(nx,ny,z-d),INF);
                        // addedge(id(x,y,d),id(nx,ny,z-d),INF);
                    }
                }
            }
        }
    }

    int flow=maxflow();
    cout<<flow<<endl;
    return 0;
}