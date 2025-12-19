#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int INF = 1e9;

int n,m;

struct Edge{
    int u,v,r,p;
};
Edge edge[MAXN];

int ans[MAXN];
int vis[MAXN];
int out[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

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

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

bool cmp(Edge a,Edge b){
    return a.r<b.r;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        edge[i].u=read(),edge[i].v=read(),edge[i].r=read(),edge[i].p=read();
        out[edge[i].u]++;
    }
    sort(edge+1,edge+m+1,cmp);
    for(int i=1;i<=n;i++){
        ans[i]=INF;
    }
    for(int i=1;i<=m;i++){
        addedge(edge[i].v,i);
    }

    queue<int>q;
    for(int i=1;i<=n;i++){
        if(out[i]==0){
            q.push(i);
        }
    }

    for(int i=m;i>=1;i--){
        while(!q.empty()){
            int u=q.front();
            q.pop();

            for(int ei=head[u];ei;ei=nxt[ei]){
                int v=to[ei];
                if(vis[v]){
                    continue;
                }
                vis[v]=true;

                int st=edge[v].u;
                out[st]--;
                if(out[st]==0){
                    q.push(st);
                }

                if(ans[u]!=INF){
                    ans[st]=min(ans[st],max(edge[v].r,ans[u]-edge[v].p));
                }
            }
        }

        if(!vis[i]){
            vis[i]=true;
            int st=edge[i].u;
            out[st]--;

            if(out[st]==0){
                q.push(st);
            }

            ans[st]=min(ans[st],edge[i].r);
        }
    }

    for(int i=1;i<=n;i++){
        if(ans[i]==INF){
            cout<<-1<<' ';
        }
        else{
            cout<<ans[i]<<' ';
        }
    }
    return 0;
}