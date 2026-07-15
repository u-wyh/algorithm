#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 250005;
const int MAXK = 5e5+5;
const int MAXH = 20;

int n,m,p;

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int weightg[MAXN<<1];
int cntg=1;

int k;
int key[MAXN];
int tmp[MAXN<<1];
bool iskey[MAXN];
int cost[MAXN];

int st[MAXN][MAXH];
int dis[MAXN][MAXH];
int dep[MAXN];

int dfncnt;
int dfn[MAXN];

int headv[MAXN];
int nxtv[MAXN];
int tov[MAXN];
int weightv[MAXN];
int cntv=1;

void addedgeg(int u,int v,int w){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    weightg[cntg]=w;
    headg[u]=cntg++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    dfn[u]=++dfncnt;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
        dis[u][i]=min(dis[u][i-1],dis[st[u][i-1]][i-1]);
    }

    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=fa){
            int w=weightg[i];
            dis[v][0]=w;
            dfs(v,u);
        }
    }
}

void prepare(){
    p=log2(n)+1;
    dfs(1,0);
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

int getdist(int a,int b){
    if(a==b){
        return 0;
    }
    if(dep[a]<=dep[b]){
        swap(a,b);
    }
    int ans=1e6;
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            ans=min(ans,dis[a][i]);
            a=st[a][i];
        }
    }
    return ans;
}

void addedgev(int u,int v,int w){
    // cout<<"   "<<u<<' '<<v<<' '<<w<<endl;
    nxtv[cntv]=headv[u];
    tov[cntv]=v;
    weightv[cntv]=w;
    headv[u]=cntv++;
}

bool cmp(int a,int b){
    return dfn[a]<dfn[b];
}

int buildvirtualtree(){
    sort(key+1,key+k+1,cmp);

    int len=k;
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
        // cout<<' '<<tmp[i];
    }
    // cout<<endl;

    for(int i=1;i<len;i++){
        int fa=lca(tmp[i],tmp[i+1]);
        addedgev(fa,tmp[i+1],getdist(fa,tmp[i+1]));
    }
    return tmp[1];
}

void dp(int u){
    cost[u]=0;
    for(int i=headv[u];i;i=nxtv[i]){
        int v=tov[i];
        int w=weightv[i];
        dp(v);
        if(iskey[v]){
            cost[u]+=w;
        }
        else{
            cost[u]+=min(cost[v],w);
        }
    }
}

int compute(){
    int ans=0;
    key[++k]=1;
    for(int i=1;i<=k;i++){
        iskey[key[i]]=true;
    }

    int tree=buildvirtualtree();
    dp(tree);
    ans=cost[tree];

    for(int i=1;i<=k;i++){
        iskey[key[i]] = false;
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedgeg(u,v,w);
        addedgeg(v,u,w);
    }

    prepare();

    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>k;
        for(int j=1;j<=k;j++){
            cin>>key[j];
        }
        cout<<compute()<<endl;
    }
    return 0;
}