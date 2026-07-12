#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 1e6+5;
const int MAXV = 4e6+5;
const int MAXE = 3e7+5;
const int MAXP = 17;
const int INF = 1<<30;

int n,m,s;

int u1[MAXM];
int v1[MAXM];
int u2[MAXM];
int v2[MAXM];
int weight[MAXM];
int cntq;

int head1[MAXN];
int nxt1[MAXN<<1];
int to1[MAXN<<1];
int cnt1=1;

int head2[MAXV];
int nxt2[MAXE];
int to2[MAXE];
int weight2[MAXE];
int cnt2=1;

int fa[MAXN];

int dep[MAXN];
int st[MAXN][MAXP];
int stout[MAXN][MAXP];
int stin[MAXN][MAXP];
int cntt;

int dist[MAXV];
bool vis[MAXV];

struct node{
    int u,d;
};
struct compare{
    bool operator()(const node &a,const node &b){
        return a.d>b.d;
    }
};
priority_queue<node,vector<node>,compare>heap;

void addedge1(int u,int v){
    nxt1[cnt1]=head1[u];
    to1[cnt1]=v;
    head1[u]=cnt1++;
}

void addedge2(int u,int v,int w){
    nxt2[cnt2]=head2[u];
    to2[cnt2]=v;
    weight2[cnt2]=w;
    head2[u]=cnt2++;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void build(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;

    stout[u][0]=++cntt;
    addedge2(u,cntt,0);
    addedge2(fa,cntt,0);

    stin[u][0]=++cntt;
    addedge2(cntt,u,0);
    addedge2(cntt,fa,0);

    for(int p=1;p<MAXP;p++){
        st[u][p]=st[st[u][p-1]][p-1];

        stout[u][p]=++cntt;
        addedge2(stout[u][p-1],cntt,0);
        addedge2(stout[st[u][p-1]][p-1],cntt,0);

        stin[u][p]=++cntt;
        addedge2(cntt,stin[u][p-1],0);
        addedge2(cntt,stin[st[u][p-1]][p-1],0);
    }

    for(int i=head1[u];i;i=nxt1[i]){
        int v=to1[i];
        if(v!=fa){
            build(v,u);
        }
    }
}

void pathout(int x,int y,int vnode){
    if (dep[x] < dep[y]) {
        swap(x, y);
    }
    addedge2(y, vnode, 0);
    for (int p = MAXP - 1; p >= 0; p--) {
        if (dep[st[x][p]] >= dep[y]) {
            addedge2(stout[x][p], vnode, 0);
            x = st[x][p];
        }
    }
    if (x == y) {
        return;
    }
    for (int p = MAXP - 1; p >= 0; p--) {
        if (st[x][p] != st[y][p]) {
            addedge2(stout[x][p], vnode, 0);
            addedge2(stout[y][p], vnode, 0);
            x = st[x][p];
            y = st[y][p];
        }
    }
    addedge2(stout[x][0], vnode, 0);
}

void pathin(int x,int y,int vnode){
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    addedge2(vnode,y,0);
    for(int p=MAXP-1;p>=0;p--){
        if(dep[st[x][p]]>=dep[y]){
            addedge2(vnode,stin[x][p],0);
            x=st[x][p];
        }
    }

    if(x==y){
        return ;
    }

    for(int p=MAXP-1;p>=0;p--){
        if(st[x][p]!=st[y][p]){
            addedge2(vnode, stin[x][p], 0);
            addedge2(vnode, stin[y][p], 0);
            x=st[x][p];
            y=st[y][p];
        }
    }
    addedge2(vnode,stin[x][0],0);
}

void pathtopath(int a,int b,int c,int d,int w){
    int x=++cntt;
    int y=++cntt;
    pathout(a,b,x);
    pathin(c,d,y);
    addedge2(x,y,w);
}

void dijkstra(){
    for(int i=1;i<=cntt;i++){
        dist[i]=INF;
    }
    dist[s]=0;
    heap.push({s,0});
    while(!heap.empty()){
        node cur=heap.top();
        heap.pop();
        int u=cur.u;
        int d=cur.d;
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(int i=head2[u];i;i=nxt2[i]){
            int w=weight2[i];
            int v=to2[i];
            if(!vis[v]&&dist[v]>d+w){
                dist[v]=d+w;
                heap.push({v,dist[v]});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>s;
    cntt=n;

    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int op,a,b,c,d,u,v,w;
        cin>>op;
        if(op==1){
            cin>>a>>b>>c>>d>>w;
            if((find(a)==find(b))&&(find(c)==find(d))){
                ++cntq;
                u1[cntq]=a;
                v1[cntq]=b;
                u2[cntq]=c;
                v2[cntq]=d;
                weight[cntq]=w;
            }
        }
        else{
            cin>>u>>v>>w;
            int ufa=find(u);
            int vfa=find(v);
            if(ufa!=vfa){
                addedge1(u,v);
                addedge1(v,u);
                addedge2(u,v,w);
                addedge2(v,u,w);
                fa[ufa]=vfa;
            }
        }
    }

    for(int i=1;i<=n;i++){
        if(dep[i]==0){
            build(i,i);
        }
    }

    for(int i=1;i<=cntq;i++){
        pathtopath(u1[i],v1[i],u2[i],v2[i],weight[i]);
    }

    dijkstra();

    for(int i=1;i<=n;i++){
        cout<<((dist[i]==INF)?-1:dist[i])<<" ";
    }
    return 0;
}