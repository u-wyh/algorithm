#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXH = 22;

int n,p,q,k,m;

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int cntg=1;

int headv[MAXN];
int nxtv[MAXN<<1];
int tov[MAXN<<1];
int cntv=1;

int dep[MAXN];
int dfn[MAXN];
int st[MAXN][MAXH];
int dfncnt;

int arr[MAXN<<1];
int tmp[MAXN<<2];
int len;

int start[MAXN];
int speed[MAXN];
int query[MAXN];

bool vis[MAXN];
int mintime[MAXN];
int findvirus[MAXN];

struct node {
    int id, dist, time, virus;
    bool operator<(const node &other) const {
        if (time != other.time) {
            return time > other.time;
        }
        return virus > other.virus;
    }
};
priority_queue<node>heap;

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

inline void addedgeg(int u,int v){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    dfn[u]=++dfncnt;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
}

bool cmp(int a,int b){
    return dfn[a]<dfn[b];
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
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

inline void addedgev(int u,int v){
    nxtv[cntv]=headv[u];
    tov[cntv]=v;
    headv[u]=cntv++;
}

int buildvirtualtree(){
    int tot=0;
    for(int i=1;i<=k;i++){
        arr[++tot]=start[i];
    }
    for(int i=1;i<=m;i++){
        arr[++tot]=query[i];
    }
    sort(arr+1,arr+tot+1,cmp);
    
    len=0;
    for(int i=1;i<tot;i++){
        tmp[++len]=arr[i];
        tmp[++len]=lca(arr[i],arr[i+1]);
    }
    tmp[++len]=arr[tot];
    sort(tmp+1,tmp+len+1,cmp);

    int m=1;
    for(int i=2;i<=len;i++){
        if(tmp[i]!=tmp[i-1]){
            tmp[++m]=tmp[i];
        }
    }

    cntv=1;
    for(int i=1;i<=m;i++){
        headv[tmp[i]]=0;
    }
    for(int i=1;i<m;i++){
        int fa=lca(tmp[i],tmp[i+1]);
        addedgev(fa,tmp[i+1]);
        addedgev(tmp[i+1],fa);
    }
    len=m;
    return tmp[1];
}

void dijkstra(){
    for(int i=1;i<=len;i++){
        int u=tmp[i];
        mintime[u]=n+1;
        findvirus[u]=k+1;
        vis[u]=false;
    }
    for(int i=1;i<=k;i++){
        int s=start[i];
        mintime[s]=0;
        findvirus[s]=i;
        heap.push({s,0,0,i});
    }
    
    while(!heap.empty()){
        node cur=heap.top();
        heap.pop();
        int u=cur.id;
        int udist=cur.dist;
        int uvirus=cur.virus;
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=headv[u];i;i=nxtv[i]){
            int v=tov[i];
            if(!vis[v]){
                int vdist=udist+abs(dep[u]-dep[v]);
                int vtime=(vdist+speed[uvirus]-1)/speed[uvirus];
                if(vtime<mintime[v]||(vtime==mintime[v]&&uvirus<findvirus[v])){
                    mintime[v]=vtime;
                    findvirus[v]=uvirus;
                    heap.push({v,vdist,vtime,uvirus});
                }
            }
        }
    }
}

int main()
{
    n=read();
    p=log2(n)+1;
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedgeg(u,v);
        addedgeg(v,u);
    }
    dfs(1,0);
    q=read();
    for(int t=1;t<=q;t++){
        k=read(),m=read();
        for(int i=1;i<=k;i++){
            start[i]=read();
            speed[i]=read();
        }
        for(int i=1;i<=m;i++){
            query[i]=read();
        }
        buildvirtualtree();
        dijkstra();
        for(int i=1;i<=m;i++){
            cout<<findvirus[query[i]]<<' ';
        }
        cout<<endl;
    }
    return 0;
}