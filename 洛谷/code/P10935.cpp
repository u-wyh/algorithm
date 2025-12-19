#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

struct node{
    int u,v,w;
};
node nums[MAXN<<1];
int cntg;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

int headv[MAXN];
int nxtv[MAXN<<1];
int tov[MAXN<<1];
int weightv[MAXN<<1];
int cntv=1;
int in[MAXN];

int dfn[MAXN];
int low[MAXN];
int st[MAXN],top;
int color,dfncnt;
bool instack[MAXN];
int col[MAXN];
int sz[MAXN];

int dp[MAXN];

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

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline void addedge(int u,int v,int w){
    nxtv[cntv]=headv[u];
    tov[cntv]=v;
    weightv[cntv]=w;
    in[v]++;
    headv[u]=cntv++;
}

void tarjan(int u){
    dfn[u]=++dfncnt;
    low[u]=dfncnt;
    st[++top]=u;
    instack[u]=true;

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(instack[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }

    if(dfn[u]==low[u]){
        col[u]=++color;
        sz[color]++;
        while(st[top]!=u){
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
            sz[color]++;
        }
        instack[u]=false;
        top--;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        int op,u,v;
        op=read(),u=read(),v=read();
        if(op==1){
            addedge(u,v);
            addedge(v,u);
            nums[++cntg]={u,v,0};
            nums[++cntg]={v,u,0};
        }
        else if(op==2){
            nums[++cntg]={u,v,1};
            addedge(u,v);
        }
        else if(op==3){
            nums[++cntg]={v,u,0};
            addedge(v,u);
        }
        else if(op==4){
            nums[++cntg]={v,u,1};
            addedge(v,u);
        }
        else{
            nums[++cntg]={u,v,0};
            addedge(u,v);
        }
    }

    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i);
        }
    }

    for(int i=1;i<=cntg;i++){
        int x=col[nums[i].u];
        int y=col[nums[i].v];
        if(x!=y){
            addedge(x,y,nums[i].w);
        }
        else if(nums[i].w){
            cout<<-1<<endl;
            return 0;
        }
    }

    queue<int>q;
    for(int i=1;i<=color;i++){
        if(in[i]==0){
            q.push(i);
            dp[i]=1;
        }
    }

    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=headv[u];i;i=nxtv[i]){
            int v=tov[i];
            int w=weightv[i];
            if(dp[v]<dp[u]+w){
                dp[v]=dp[u]+w;
            }
            in[v]--;
            if(in[v]==0){
                q.push(v);
            }
        }
    }

    long long ans=0;
    for(int i=1;i<=color;i++){
        ans+=dp[i]*sz[i];
    }
    cout<<ans<<endl;
    return 0;
}