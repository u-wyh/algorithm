#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXH = 20;

int n,m,p;

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int cntg=1;

int dep[MAXN];
int dfn[MAXN];
int dfncnt;
int st[MAXN][MAXH];

int k;
int key[MAXN];
bool iskey[MAXN];
int len;
int tmp[MAXN<<1];

int sz[MAXN];
int cost[MAXN];

int headv[MAXN];
int nxtv[MAXN];
int tov[MAXN];
int cntv=1;

void addedgeg(int u,int v){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

void dfs(int u,int fa){
    dfn[u]=++dfncnt;
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }

    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=fa)
            dfs(v,u);
    }
}

int lca(int a,int b){
    if(dep[a]<=dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }

    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

bool cmp(int a,int b){
    return dfn[a]<dfn[b];
}

void addedgev(int u,int v){
    nxtv[cntv]=headv[u];
    tov[cntv]=v;
    headv[u]=cntv++;
}

int buildvirtualtree(){
    sort(key+1,key+k+1,cmp);
    len=k;
    for(int i=1;i<=k;i++){
        tmp[i]=key[i];
    }
    for(int i=1;i<k;i++){
        tmp[++len]=lca(key[i],key[i+1]);
    }
    sort(tmp+1,tmp+len+1,cmp);

    len=1;
    for(int i=2;i<=2*k-1;i++){
        if(tmp[i]!=tmp[i-1]){
            tmp[++len]=tmp[i];
        }
    }

    cntv=1;
    for(int i=1;i<=len;i++){
        headv[tmp[i]]=0;
    }
    for(int i=1;i<len;i++){
        addedgev(lca(tmp[i],tmp[i+1]),tmp[i+1]);
    }

    return tmp[1];
}

void dp(int u){
    cost[u]=sz[u]=0;
    for(int i=headv[u];i;i=nxtv[i]){
        int v=tov[i];
        dp(v);
        sz[u]+=sz[v];
        cost[u]+=cost[v];
    }
    if(iskey[u]){
        cost[u]+=sz[u];
        sz[u]=1;
    }
    else if(sz[u]>1){
        cost[u]++;
        sz[u]=0;
    }
}

int compute(){
    int ans=0;
    for(int i=1;i<=k;i++){
        iskey[key[i]]=true;
    }
    for(int i=1;i<=k;i++){
        if(iskey[st[key[i]][0]]){
            ans=-1;
            break;
        }
    }

    if(ans!=-1){
        int tree=buildvirtualtree();
        dp(tree);
        ans=cost[tree];
    }

    for(int i=1;i<=k;i++){
        iskey[key[i]]=false;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedgeg(u,v);
        addedgeg(v,u);
    }
    p=log2(n)+1;

    dfs(1,0);

    cin>>m;
    for(int t=1;t<=m;t++){
        cin>>k;
        for(int i=1;i<=k;i++){
            cin>>key[i];
        }
        cout<<compute()<<endl;
    }
    return 0;
}