#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 3e5+5;
const int MAXT = 5e6+5;

int n,m,q;

int val[MAXN];
int sorted[MAXN];
int cntv;

int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cntg=2;

int head2[MAXN];
int nxt2[MAXM];
int to2[MAXM];
int cntg2=1;

int cntn;

int dfncnt;
int dfn[MAXN];
int low[MAXN];
int sta[MAXN];
int stasz;

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
int all[MAXT];
int odd[MAXT];
int cntt;

int op[MAXN];
int qy[MAXN];
int headq[MAXN];
int nxtq[MAXN];
int toq[MAXN];
int cntq=1;

int ans[MAXN];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

inline void addedge2(int u,int v){
    nxt2[cntg2]=head2[u];
    to2[cntg2]=v;
    head2[u]=cntg2++;
}

void cyclelink(int u, int v) {
    cntn++;
    addedge2(u,cntn);
    int pop;
    do {
        pop = sta[stasz--];
        addedge2(cntn, pop);
    } while (pop != v);
}

void tarjan(int u,int preedge){
    dfn[u]=low[u]=++dfncnt;
    sta[++stasz]=u;
    for(int i=head[u];i;i=nxt[i]){
        if((i^1)==preedge){
            continue;
        }
        int v=to[i];
        if(dfn[v]==0){
            tarjan(v,i);
            if(low[v]<dfn[u]){
                low[u]=min(low[u],low[v]);
            }
            else if(low[v]>dfn[u]){
                stasz--;
                addedge2(u,v);
            }
            else{
                cyclelink(u,v);
            }
        }
        else if(dfn[v]<dfn[u]){
            low[u]=min(low[u],dfn[v]);
        }
    }
}

void prepare(){
    cntn=n;
    tarjan(1,0);
}

inline void addquery(int x,int v){
    nxtq[cntq]=headq[x];
    toq[cntq]=v;
    headq[x]=cntq++;
}

int find(int val){
    int l=1,r=cntv,ans=cntv+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans-1;
}

void up(int i){
    all[i]=all[ls[i]]+all[rs[i]];
    odd[i]=odd[ls[i]]+odd[rs[i]];
}

int add(int jobv,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=++cntt;
    }
    if(l==r){
        all[rt]=1;
        odd[rt]=1;
    }
    else{
        int mid=(l+r)>>1;
        if(jobv<=mid){
            ls[rt]=add(jobv,l,mid,ls[rt]);
        }
        else{
            rs[rt]=add(jobv,mid+1,r,rs[rt]);
        }
        up(rt);
    }
    return rt;
}

int merge(int l,int r,int t1,int t2){
    if(!t1||!t2){
        return t1+t2;
    }

    if(l==r){
        all[t1]=1;
        odd[t1]^=odd[t2];
    }
    else{
        int mid=(l+r)>>1;
        ls[t1]=merge(l,mid,ls[t1],ls[t2]);
        rs[t1]=merge(mid+1,r,rs[t1],rs[t2]);
        up(t1);
    }
    return t1;
}

int query(int jobl,int jobr,int l,int r,int i,int op){
    if(i==0||jobl>jobr){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return op?odd[i]:(all[i]-odd[i]);
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,ls[i],op);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,rs[i],op);
        }
        return ans;
    }
}

void dfs(int u){
    for(int i=head2[u];i;i=nxt2[i]){
        int v=to2[i];
        dfs(v);
        root[u]=merge(1,cntv,root[u],root[v]);
    }

    if(u<=n){
        for(int i=headq[u];i;i=nxtq[i]){
            int v=toq[i];
            ans[v]=query(1,qy[v],1,cntv,root[u],op[v]);
        }
    }
}

void compute(){
    for(int i=1;i<=n;i++){
        sorted[i]=val[i];
    }
    sort(sorted+1,sorted+n+1);
    cntv=1;
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++cntv]=sorted[i];
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
        root[i]=add(val[i],1,cntv,root[i]);
    }
    for(int i=1;i<=q;i++){
        qy[i]=find(qy[i]);
    }
    dfs(1);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    prepare();

    cin>>q;
    for(int i=1;i<=q;i++){
        int x;
        cin>>op[i]>>x>>qy[i];
        addquery(x,i);
    }

    compute();

    for(int i=1;i<=q;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}