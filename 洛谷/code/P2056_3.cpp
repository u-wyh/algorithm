#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
bool black[MAXN];

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

int fa[MAXN];
int sz[MAXN];
int top[MAXN];
int dep[MAXN];
int son[MAXN];

bool vis[MAXN];
int centfa[MAXN];

struct Set{
    priority_queue<int>addheap;
    priority_queue<int>delheap;

    void clean(){
        while(!delheap.empty()&&!addheap.empty()&&delheap.top()==addheap.top()){
            addheap.pop();
            delheap.pop();
        }
    }

    int pophead(){
        int ans=addheap.top();
        addheap.pop();
        clean();
        return ans;
    }

    int size(){
        return addheap.size()-delheap.size();
    }

    void add(int v){
        addheap.push(v);
    }

    void del(int v){
        delheap.push(v);
        clean();
    }

    int first(){
        return addheap.top();
    }

    int second(){
        int a=pophead();
        int b=first();
        add(a);
        return b;
    }
};

Set distfa[MAXN];
Set sonmax[MAXN];
Set maxdist;

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs1(int u,int f){
    dep[u]=dep[f]+1;
    fa[u]=f;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            sz[u]+=sz[v];
            if(sz[son[u]]<sz[v]){
                son[u]=v;
            }
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
        }
    }
}

int getlca(int a,int b){
    while(top[a]!=top[b]){
        if(dep[top[a]]<dep[top[b]]){
            b=fa[top[b]];
        }
        else{
            a=fa[top[a]];
        }
    }
    return dep[a]<dep[b]?a:b;
}

int getdist(int a,int b){
    return dep[a]+dep[b]-(dep[getlca(a,b)]<<1);
}

void getsize(int u,int fa){
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa&&!vis[v]){
            getsize(v,u);
            sz[u]+=sz[v];
        }
    }
}

int getcentroid(int u,int fa){
    getsize(u,fa);
    int half=sz[u]>>1;
    bool find=false;
    while(!find){
        find=true;
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v!=fa&&!vis[v]&&sz[v]>half){
                find=false;
                fa=u;
                u=v;
                break;
            }
        }
    }
    return u;
}

void centroidtree(int u,int fa){
    centfa[u]=fa;
    vis[u]=true;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(!vis[v]){
            centroidtree(getcentroid(v,u),u);
        }
    }
}

void addans(int x){
    if(sonmax[x].size()>=2){
        maxdist.add(sonmax[x].first()+sonmax[x].second());
    }
}

void delans(int x){
    if(sonmax[x].size()>=2){
        maxdist.del(sonmax[x].first()+sonmax[x].second());
    }
}

void on(int x){
    delans(x);
    sonmax[x].del(0);
    addans(x);
    for(int cur=x,fa=centfa[cur];fa;cur=fa,fa=centfa[cur]){
        delans(fa);
        sonmax[fa].del(distfa[cur].first());
        distfa[cur].del(getdist(x,fa));
        if(distfa[cur].size()>0){
            sonmax[fa].add(distfa[cur].first());
        }
        addans(fa);
    }
}

void off(int x){
    delans(x);
    sonmax[x].add(0);
    addans(x);
    for(int cur=x,fa=centfa[cur];fa;cur=fa,fa=centfa[cur]){
        delans(fa);
        if(distfa[cur].size()>0){
            sonmax[fa].del(distfa[cur].first());
        }
        distfa[cur].add(getdist(x,fa));
        sonmax[fa].add(distfa[cur].first());
        addans(fa);
    }
}

void prepare(){
    for(int i=1;i<=n;i++){
        black[i]=true;
    }
    for(int i=1;i<=n;i++){
        for(int cur=i,fa=centfa[cur];fa;cur=fa,fa=centfa[cur]){
            distfa[cur].add(getdist(i,fa));
        }
    }
    for(int i=1;i<=n;i++){
        sonmax[i].add(0);
        if(centfa[i]){
            sonmax[centfa[i]].add(distfa[i].first());
        }
    }
    for(int i=1;i<=n;i++){
        addans(i);
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    dfs2(1,1);
    centroidtree(getcentroid(1,0),0);
    prepare();
    scanf("%d",&m);
    int blackcnt=n;
    for(int i=1;i<=m;i++){
        char op;
        int x;
        scanf(" %c",&op);
        if(op=='C'){
            scanf("%d",&x);
            black[x]=!black[x];
            if(black[x]){
                off(x);
                blackcnt++;
            }
            else{
                on(x);
                blackcnt--;
            }
        }
        else{
            if(blackcnt<=1){
                cout<<(blackcnt-1)<<endl;
            }
            else{
                cout<<maxdist.first()<<endl;
            }
        }
    }
    return 0;
}