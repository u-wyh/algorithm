#include<bits/stdc++.h>
using namespace std;
const int MAXN = 255;
const int MAXM = 4*MAXN*MAXN;
const int INF = 1e9;

int n,m,c,d;
int s,t;
char str[MAXN][MAXN];

int dep[MAXN*2];//记录深度数组
int iter[MAXN*2];//当前弧数组 记录这个节点有效访问的第一条边的编号

//这里编号从2开始 为了正反边编号寻找方便
int cnt=2;
int head[MAXN*2];
int nxt[MAXM];
int to[MAXM];
int cap[MAXM];//表示剩余容量

int st[MAXN<<1];

inline void addedge(int u,int v,int w){
    nxt[cnt]=head[u];
    to[cnt]=v;
    cap[cnt]=w;
    head[u]=cnt++;

    nxt[cnt]=head[v];
    to[cnt]=u;
    cap[cnt]=0;
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
            if(dep[v]<0&&cap[i]>0){
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
        if(dep[u]+1==dep[v]&&cap[i]>0){
            int d=dfs(v,min(f,cap[i]));
            if(d>0){
                cap[i]-=d;      
                cap[i^1]+=d;    
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

// Dinic算法主函数
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

int main()
{
    scanf("%d %d %d %d",&n,&m,&c,&d);
    s=n+m+1,t=n+m+2;
    int all=0;
    for(int i=1;i<=n;i++){
        scanf("%s",str[i]+1);
        for(int j=1;j<=m;j++){
            if(str[i][j]=='.'){
                all++;
            }
        }
    }

    long long ans=min(1ll*c*all,1ll*all*d);

    for(int i=1;i<=n;i++){
        st[i]=cnt;
        addedge(s,i,0);
    }
    // cout<<cnt<<endl;
    for(int j=1;j<=m;j++){
        st[n+j]=cnt;
        addedge(j+n,t,0);
    }
    // cout<<cnt<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(str[i][j]=='.'){
                addedge(i,j+n,1);
            }
        }
    }

    int res=0;
    for(int k=1;k<=max(n,m);k++){
        for(int i=1;i<=n+m;i++){
            cap[st[i]]++;
        }
        // for(int i=2;i<=2*n;i+=2){
        //     cap[i]++;
        //     // cap[i^1]--;
        // }
        // for(int j=2*n+2;j<=2*n+2*m;j+=2){
        //     cap[j]++;
        //     // cap[j^1]--;
        // }

        res+=maxflow();
        ans=min(ans,1ll*c*k+1ll*d*(all-res));
    }
    cout<<ans<<endl;
    return 0;
}