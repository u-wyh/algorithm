#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+1;
const int MAXM = 3e6+1;

int head[MAXN];
int Next[MAXM];
int to[MAXM];
int cnt;
int a[MAXN],b[MAXN];
int dfn[MAXN],low[MAXN];
bool instack[MAXN];
int st[MAXN],top;
int color,Time;
int col[MAXN];
int n,m;

void tarjan(int x){
    dfn[x]=++Time;
    low[x]=Time;
    for(int i=head[x];i;i=Next[i]){
        int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            low[x]=min(low[x],low[v]);
        }
        else if(instack[v]){
            low[x]=min(low[x],dfn[v]);
        }
    }
    if(dfn[x]==low[x]){
        col[x]=++color;
        while(st[top]!=x){
            col[st[top]]=color;
            instack[st[top]]=false;
            top--;
        }
        instack[x]=false;
        top--;
    }
}

inline void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        Time=0;
        cnt=0;
        top=0;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=n;i++){
            cin>>b[i];
            addedge(a[i],b[i]);
        }
        for(int i=1;i<=MAXN/2;i++){
            for(int j=1;j*i<MAXN;j++){
                addedge(i,i*j);
            }
        }
        for(int i=1;i<MAXN;i++){
            if(!dfn[i]){
                tarjan(i);
            }
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            if(col[a[i]]==col[b[i]]){
                ans++;
            }
        }
        cout<<ans<<endl;
        for(int i=1;i<MAXN;i++){
            head[i]=0;
            dfn[i]=low[i]=col[i]=0;
        }
        for(int i=1;i<=cnt;i++){
            to[i]=Next[i]=0;
        }
    }
    return 0;
}
