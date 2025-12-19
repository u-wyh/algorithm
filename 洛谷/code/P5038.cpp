#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 45;
const int MAXM = 1605;
const int MAXE = 10005;
const int INF = 1e15;

int n,m,s,t;
int black,white;
int val[MAXN][MAXN];
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};

int dep[MAXM];
int iter[MAXM];

int cnt=2;
int head[MAXM];
int nxt[MAXE];
int to[MAXE];
int now[MAXE];
int cap[MAXE];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

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
    for(int i=1;i<=n*m+2;i++){
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
    return dep[t]>=0;// 如果汇点未被访问到，说明无增广路径
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
        for(int i=1;i<=n*m+2;i++){
            iter[i]=head[i];
        }
        int maxflow;
        while((maxflow=dfs(s,INF))>0){
            flow+=maxflow;
        }
    }
    return flow;
}

bool check(int x){
    s=n*m+1,t=n*m+2;
    for(int i=1;i<=t;i++){
        head[i]=0;
    }
    cnt=2;
    int need=(n%2==0||m%2==0)?(n*m/2*x-black):((n*m+1)/2*x-black);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int id=(i-1)*m+j;
            if((i+j)%2==0){
                addedge(s,id,x-val[i][j]);
                for(int k=0;k<4;k++){
                    int nx=i+walk[k][0];
                    int ny=j+walk[k][1];
                    if(nx>=1&&nx<=n&&ny>=1&&ny<=m){
                        int nid=(nx-1)*m+ny;
                        addedge(id,nid,INF);
                    }
                }
            }
            else{
                addedge(id,t,x-val[i][j]);
            }
        }
    }
    int flow=maxflow();
    return flow==need;
}

signed main()
{
    int T=read();
    while(T--){
        n=read(),m=read();
        int maxx=0;
        black=0,white=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                val[i][j]=read();
                maxx=max(maxx,val[i][j]);

                if((i+j)%2==0){
                    black+=val[i][j];
                }
                else{
                    white+=val[i][j];
                }
            }
        }
        if((n%2==0)||(m%2==0)){
            if(white!=black){
                cout<<-1<<endl;
                continue;
            }

            int l=maxx,r=INF,ans=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(check(mid)){
                    ans=mid;
                    r=mid-1;
                }
                else{
                    l=mid+1;
                }
            }

            if(ans==-1){
                cout<<ans<<endl;
            }
            else{
                cout<<(n*m*ans/2-black)<<endl;
            }
        }
        else{
            int x=(black-white);
            if(x<maxx){
                cout<<-1<<endl;
            }
            else if(check(x)){
                cout<<((n*m+1)/2*x-black)<<endl;
            }
            else{
                cout<<-1<<endl;
            }
        }
    }
    return 0;
}