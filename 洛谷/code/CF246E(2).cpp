#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = 30*MAXN;

int n,m,maxdep;

int tot;
map<string,int>nameid;
bool rooted[MAXN];
int id[MAXN];

int dep[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cnt=1;

int headq[MAXN];
int nxtq[MAXN];
int toq[MAXN];
int idq[MAXN];
int cntq=1;

int ans[MAXN];

int root[MAXN];
int ls[MAXT];
int rs[MAXT];
set<int>st[MAXT];
int cntv;

inline int getnameid(string s){
    int k=nameid[s];
    if(k!=0){
        return k;
    }
    else{
        nameid[s]=++tot;
        return tot;
    }
}

inline void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline void addquestion(int u,int v,int i){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    idq[cntq]=i;
    headq[u]=cntq++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
    }
}

int add(int pos,int jobv,int l,int r,int i){
    int rt=i;
    if(rt==0){
        rt=++cntv;
    }
    if(l==r){
        st[rt].insert(jobv);
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            ls[rt]=add(pos,jobv,l,mid,ls[rt]);
        }
        else{
            rs[rt]=add(pos,jobv,mid+1,r,rs[rt]);
        }
    }
    return rt;
}

int merge(int l,int r,int t1,int t2){
    if(t1==0||t2==0){
        return t1+t2;
    }
    if(l==r){
        if(st[t1].size()<st[t2].size()){
            swap(t1,t2);
        }
        for(auto it:st[t2]){
            st[t1].insert(it);
        }
    }
    else{
        int mid=(l+r)>>1;
        ls[t1]=merge(l,mid,ls[t1],ls[t2]);
        rs[t1]=merge(mid+1,r,rs[t1],rs[t2]);
    }
    return t1;
}

int query(int pos,int l,int r,int i){
    if(i==0){
        return 0;
    }
    if(l==r){
        return st[i].size();
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            return query(pos,l,mid,ls[i]);
        }
        else{
            return query(pos,mid+1,r,rs[i]);
        }
    }
}

void dfs(int u){
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        root[u]=merge(1,maxdep,root[u],root[v]);
    }
    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        int id=idq[i];
        if(dep[u]+v>maxdep){
            ans[id]=0;
        }
        else{
            ans[id]=query(dep[u]+v,1,maxdep,root[u]);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    string name;
    int fa;
    for(int i=1;i<=n;i++){
        cin>>name>>fa;
        id[i]=getnameid(name);
        if(fa==0){
            rooted[i]=true;
        }
        else{
            addedge(fa,i);
        }
    }
    maxdep=0;
    for(int i=1;i<=n;i++){
        if(rooted[i]){
            dfs(i,0);
        }
        maxdep=max(maxdep,dep[i]);
    }
    for(int i=1;i<=n;i++){
        root[i]=add(dep[i],id[i],1,maxdep,root[i]);
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int u,k;
        cin>>u>>k;
        addquestion(u,k,i);
    }
    for(int i=1;i<=n;i++){
        if(rooted[i]){
            dfs(i);
        }
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}