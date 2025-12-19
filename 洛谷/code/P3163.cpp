#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXM = MAXN*MAXN;
const int MAXE = MAXM*20;
const int INF = 1e9;

int n;
int a1,a2,an,b1,b2,bn;
char str[MAXN][MAXN];
int s,t;

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
    while(cin>>n>>a1>>a2>>an>>b1>>b2>>bn){
        a1++,a2++,b1++,b2++;
        cnt=2;
        memset(head,0,sizeof(head));

        for(int i=1;i<=n;i++){
            scanf("%s",str[i]+1);
        }
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(str[i][j]=='N'){
                    addedge(i,j,INF);
                    addedge(j,i,INF);
                }
            }
        }
        int nodecnt=n;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(str[i][j]=='O'){
                    int in=++nodecnt;
                    int out=++nodecnt;
                    addedge(i,in,INF);
                    addedge(j,in,INF);
                    addedge(in,out,2);
                    addedge(out,i,INF);
                    addedge(out,j,INF);
                }
            }
        }
        s=++nodecnt;
        t=++nodecnt;

        addedge(s,a1,2*an);
        addedge(s,b1,2*bn);
        addedge(b2,t,2*bn);
        addedge(a2,t,2*an);

        int flow1=maxflow();

        cnt=2;
        memset(head,0,sizeof(head));

        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(str[i][j]=='N'){
                    addedge(i,j,INF);
                    addedge(j,i,INF);
                }
            }
        }
        nodecnt=n;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(str[i][j]=='O'){
                    int in=++nodecnt;
                    int out=++nodecnt;
                    addedge(i,in,INF);
                    addedge(j,in,INF);
                    addedge(in,out,2);
                    addedge(out,i,INF);
                    addedge(out,j,INF);
                }
            }
        }
        s=++nodecnt;
        t=++nodecnt;

        addedge(s,a1,2*an);
        addedge(s,b2,2*bn);
        addedge(b1,t,2*bn);
        addedge(a2,t,2*an);

        int flow2=maxflow();

        if(flow1==flow2&&flow1==2*(an+bn)){
            cout<<"Yes"<<endl;
        }
        else{
            cout<<"No"<<endl;
        }
    }
    return 0;
}