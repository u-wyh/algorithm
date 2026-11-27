#include<bits/stdc++.h>
using namespace std;
const int MAXN = 12e5+5;

int m;
int cnt;
map<pair<int,int>,int>mp;

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int cntg=1;

int dfn[MAXN];
int low[MAXN];
int dfncnt;
int sta[MAXN];
int top;
bool insta[MAXN];
int scc[MAXN];
int scccnt;
int col[MAXN];

int get(int x,int y){
    int v=mp[{x,y}];
    if(v){
        return v;
    }
    mp[{x,y}]=++cnt;
    return cnt;
}

void addedge(int u,int v){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    sta[++top]=u;
    insta[u]=true;

    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(insta[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }

    if(dfn[u]==low[u]){
        scccnt++;
        int pop;
        do{
            pop=sta[top--];
            insta[pop]=false;
            scc[pop]=scccnt;
        }while(pop!=u);
    }
}

bool dfs(int u){
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(scc[u]!=scc[v]){
            continue;
        }
        int c=(col[u]+1)%3;
        if(col[v]==-1){
            col[v]=c;
            if(dfs(v)){
                return 1;
            }
        }
        else if(col[v]!=c){
            return 1;
        }
    }
    return 0;
}

void solve(){
    mp.clear();
    cntg=1;
    for(int i=1;i<=cnt;i++){
        headg[i]=0;
        dfn[i]=low[i]=0;
        insta[i]=0;
        scc[i]=0;
        col[i]=-1;
    }
    cnt=0;
    dfncnt=0;
    scccnt=0;
    top=0;

    cin>>m;
    for(int i=1;i<=m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        int ab=get(a,b);
        int bc=get(b,c);
        int ac=get(a,c);
        int ba=get(b,a);
        int cb=get(c,b);
        int ca=get(c,a);

        addedge(ab,bc);
        addedge(bc,ca);
        addedge(ca,ab);
        addedge(ac,cb);
        addedge(cb,ba);
        addedge(ba,ac);
    }

    for(int i=1;i<=cnt;i++){
        col[i]=-1;
        if(!dfn[i]){
            tarjan(i);
        }
    }

    for(int i=1;i<=cnt;i++){
        if(col[i]!=-1){
            continue;
        }

        col[i]=0;
        if(dfs(i)){
            cout<<"yes"<<endl;
            return;
        }
    }
    cout<<"no"<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}