#include<bits/stdc++.h>
using namespace std;

const int MAXN=2e5+5;
const int MAXM=4e5+5;

int n,m;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;

int sta[MAXM];
int top;

int deg[MAXN];
int tag[MAXN];
int tmp[MAXN];
int lentmp;
int bcccnt;

int ans[MAXN];

inline void addedge(int u,int v){
    nxt[++cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg;
}

void getbcc(int lastedge){
    bcccnt++;
    lentmp=0;

    while(1){
        int e=sta[top--];

        int u=to[e^1];
        int v=to[e];

        // 统计当前点双中每个点的度数
        deg[u]++;
        deg[v]++;

        // 记录当前点双中出现过哪些点
        if(tag[u]!=bcccnt){
            tag[u]=bcccnt;
            tmp[++lentmp]=u;
        }

        if(tag[v]!=bcccnt){
            tag[v]=bcccnt;
            tmp[++lentmp]=v;
        }

        if(e==lastedge){
            break;
        }
    }

    // 当前点双对每个点贡献 floor(deg/2)
    for(int i=1;i<=lentmp;i++){
        int u=tmp[i];
        ans[u]+=deg[u]/2;
        deg[u]=0;
    }
}

void tarjan(int u,int preedge){
    dfn[u]=low[u]=++dfncnt;

    for(int i=head[u];i;i=nxt[i]){
        if(i==(preedge^1)){
            continue;
        }

        int v=to[i];

        if(!dfn[v]){
            // 树边进入边栈
            sta[++top]=i;

            tarjan(v,i);

            low[u]=min(low[u],low[v]);

            // 弹出一个点双连通分量
            if(low[v]>=dfn[u]){
                getbcc(i);
            }
        }
        else if(dfn[v]<dfn[u]){
            // 只把指向祖先的返祖边压栈一次
            sta[++top]=i;
            low[u]=min(low[u],dfn[v]);
        }
    }
}

void solve(){
    cin>>n>>m;

    cntg=1;
    dfncnt=0;
    top=0;
    bcccnt=0;

    for(int i=1;i<=n;i++){
        head[i]=0;
        dfn[i]=0;
        low[i]=0;
        deg[i]=0;
        tag[i]=0;
        ans[i]=0;
    }

    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;

        addedge(u,v);
        addedge(v,u);
    }

    // 图不一定连通
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tarjan(i,0);
        }
    }

    for(int i=1;i<=n;i++){
        cout<<ans[i];

        if(i==n){
            cout<<"\n";
        }
        else{
            cout<<" ";
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin>>T;

    while(T--){
        solve();
    }

    return 0;
}