#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];
int cntg=1;

double dn[MAXN];
double up[MAXN];
int facnt[MAXN];
int soncnt[MAXN];

int from[MAXN];
int fromedge[MAXN];
int cycle[MAXN];
int dfncnt;
int dfn[MAXN];
int cnta;
int arr[MAXN];
int edgel[MAXN];
int edger[MAXN];

inline void addedge(int u,int v,int w){
    nxt[cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg++;
}

void dfs1(int u,int fa){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=fa&&!cycle[v]){
            facnt[v]=1;
            dfs1(v,u);
            soncnt[u]++;
            dn[u]+=dn[v]+w;
        }
    }
    if(soncnt[u]){
        dn[u]/=soncnt[u];
    }
}

void dfs2(int u,int fa,int edgew){
    up[u]=edgew;
    int rest=facnt[fa]+soncnt[fa]-1;
    if(rest){
        up[u]+=(up[fa]*facnt[fa]+dn[fa]*soncnt[fa]-dn[u]-edgew)/rest;
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!cycle[v]){
            dfs2(v,u,weight[i]);
        }
    }
}

void computeTree(){
    dfs1(1,0);
    for(int i=head[1];i;i=nxt[i]){
        int v=to[i];
        int w=weight[i];
        dfs2(v,1,w);
    }
}

void dfs(int u){
    dfn[u]=++dfncnt;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(dfn[v]==0){
            from[v]=u;
            fromedge[v]=i;
            dfs(v);
        }
        else if(dfn[u]<dfn[v]){
            cycle[u]=true;
            arr[++cnta]=u;
            facnt[u]=2;
            edger[u]=edgel[v]=i;
            for(int j=v;j!=u;j=from[j]){
                cycle[j]=true;
                arr[++cnta]=j;
                facnt[j]=2;
                int k=from[j];
                edger[j]=edgel[k]=fromedge[j];
            }
        }
    }
}

int leftid(int x){
    if(x==cnta){
        return 1;
    }
    return x+1;
}

int rightid(int x){
    if(x==1){
        return cnta;
    }
    return x-1;
}

void dponcycle(){
    for(int i=1;i<=cnta;i++){
        int u=arr[i];

        double p=0.5;
        for(int j=rightid(i);j!=i;j=rightid(j)){
            int x=arr[j];
            if(rightid(j)==i){
                up[u]+=p*(dn[x]+weight[edger[arr[j]]]);
            }
            else{
                up[u]+=p*(weight[edger[arr[j]]]+dn[x]*soncnt[x]/(soncnt[x]+1));
            }

            p/=(soncnt[x]+1);
        }

        p=0.5;
        for(int j=leftid(i);j!=i;j=leftid(j)){
            int x=arr[j];
            if(leftid(j)==i){
                up[u]+=p*(dn[x]+weight[edgel[arr[j]]]);
            }
            else{
                up[u]+=p*(weight[edgel[arr[j]]]+dn[x]*soncnt[x]/(soncnt[x]+1));
            }

            p/=(soncnt[x]+1);
        }
    }
}

void computeCycle(){
    dfs(1);
    for(int i=1;i<=cnta;i++){
        dfs1(arr[i],0);
    }
    dponcycle();
    for(int i=1;i<=cnta;i++){
        int u=arr[i];
        for(int e=head[u];e;e=nxt[e]){
            int v=to[e];
            int w=weight[e];
            if(!cycle[v]){
                dfs2(v,u,w);
            }
        }
    }
}

double compute(){
    double ans=0;
    for(int i=1;i<=n;i++){
        int cnt=facnt[i]+soncnt[i];
        if(cnt){
            ans+=(dn[i]*soncnt[i]+up[i]*facnt[i])/cnt;
        }
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge(u,v,w);
        addedge(v,u,w);
    }

    if(m==(n-1)){
        computeTree();
    }
    else{
        computeCycle();
    }
    printf("%.8lf",compute()/n);
    return 0;
}