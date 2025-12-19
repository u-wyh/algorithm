#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;
int val[MAXN];
long long all;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
bool vis[MAXN<<1];
int cnt=1;

int block;
int belong[MAXN];
long long valsum[MAXN];
int vsum[MAXN];
int esum[MAXN];
queue<int>q;

int dfn[MAXN];
int low[MAXN];
int fa[MAXN];
long long sum[MAXN];
int dfncnt;

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

void tarjan(int u,int f){
    fa[u]=f;
    dfn[u]=low[u]=++dfncnt;
    sum[u]=val[u];
    for(int i=head[u];i;i=nxt[i]){
        if(vis[i]){
            continue;
        }
        vis[i]=vis[((i-1)^1)+1]=true;
        int v=to[i];

        if(!dfn[v]){
            tarjan(v,u);
            sum[u]+=sum[v];
            low[u]=min(low[u],low[v]);
        }
        else {
            low[u]=min(low[u],dfn[v]);
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
        all+=val[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }

    for(int i=1;i<=n;i++){
        if(!belong[i]){
            block++;
            valsum[block]+=val[i];
            vsum[block]++;
            belong[i]=block;
            q.push(i);

            while(!q.empty()){
                int u=q.front();
                q.pop();
                for(int i=head[u];i;i=nxt[i]){
                    esum[block]++;
                    int v=to[i];
                    if(belong[v]){
                        continue;
                    }
                    vsum[block]++;
                    valsum[block]+=val[v];
                    belong[v]=block;
                    q.push(v);
                }
            }

        }
        esum[block]/=2;
    }

    if(block>2){
        cout<<-1<<endl;
    }
    else if(block==2){
        bool flag=false;
        if(vsum[2]-1<esum[2]||vsum[1]-1<esum[1]){
            flag=true;
        }
        if(flag){
            cout<<abs(valsum[2]-valsum[1])<<endl;
        }
        else{
            cout<<-1<<endl;
        }
    }
    else{
        long long ans=LLONG_MAX;
        tarjan(1,0);

        for(int i=2;i<=n;i++){
            int u=fa[i];
            if(low[i]>dfn[u]){
                ans=min(ans,abs(all-2*sum[i]));
            }
        }

        if(ans==LLONG_MAX){
            cout<<-1<<endl;
        }
        else{
            cout<<ans<<endl;
        }
    }
    return 0;
}