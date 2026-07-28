#include<bits/stdc++.h>
using namespace std;
const int MAXN = 6e5+5;

int n,m,q,k;
int cntn;

int head1[MAXN];
int nxt1[MAXN<<1];
int to1[MAXN<<1];
int weight1[MAXN<<1];
int cntg1=2;

int head2[MAXN];
int nxt2[MAXN];
int to2[MAXN];
long long weight2[MAXN];
int cntg2=1;

int head3[MAXN];
int nxt3[MAXN];
int to3[MAXN];
int cntg3=1;

int dfncnt;
int dfn[MAXN];
int low[MAXN];
int sta[MAXN];
int stasz;

long long fromweight[MAXN];
long long cyclelen[MAXN];
long long cyclesum[MAXN];

int fa[MAXN];
int son[MAXN];
int sz[MAXN];
long long len[MAXN];
int dep[MAXN];
int top[MAXN];

int arr[MAXN];
int tmp[MAXN];

long long dist[MAXN];
long long diameter;

int idx[MAXN];
long long pre[MAXN];
long long val[MAXN];
int que[MAXN];


void addedge1(int u,int v,int w){
    nxt1[cntg1]=head1[u];
    to1[cntg1]=v;
    weight1[cntg1]=w;
    head1[u]=cntg1++;
}

void addedge2(int u,int v,long long w){
    nxt2[cntg2]=head2[u];
    to2[cntg2]=v;
    weight2[cntg2]=w;
    head2[u]=cntg2++;
}

void addedge3(int u,int v){
    nxt3[cntg3]=head3[u];
    to3[cntg3]=v;
    head3[u]=cntg3++;
}

void cyclelink(int u,int v){
    cntn++;
    cyclesum[cntn]=fromweight[u];
    addedge2(u,cntn,0);
    int tmp=stasz;
    int pop;
    do{
        pop=sta[tmp--];
        cyclelen[pop]=cyclesum[cntn];
        cyclesum[cntn]+=fromweight[pop];
    }while(pop!=v);
    do{
        pop=sta[stasz--];
        addedge2(cntn,pop,min(cyclelen[pop],cyclesum[cntn]-cyclelen[pop]));
    }while(pop!=v);
}

void tarjan(int u,int preedge){
    dfn[u]=low[u]=++dfncnt;
    sta[++stasz]=u;
    for(int i=head1[u];i;i=nxt1[i]){
        if((i^1)==preedge){
            continue;
        }

        int v=to1[i];
        int w=weight1[i];
        if(dfn[v]==0){
            tarjan(v,i);
            fromweight[v]=w;
            if(low[v]<dfn[u]){
                low[u]=min(low[u],low[v]);
            }
            else if(low[v]>dfn[u]){
                stasz--;
                addedge2(u,v,w);
            }
            else{
                cyclelink(u,v);
            }
        }
        else if(dfn[v]<dfn[u]){
            fromweight[v]=w;
            low[u]=min(low[u],dfn[v]);
        }
    }
}

void dfs1(int u,int f,long long l){
    sz[u]=1;
    dep[u]=dep[f]+1;
    fa[u]=f;
    len[u]=l;
    for(int i=head2[u];i;i=nxt2[i]){
        int v=to2[i];
        long long w=weight2[i];
        if(v!=f){
            dfs1(v,u,l+w);
            sz[u]+=sz[v];
            if(sz[v]>sz[son[u]]){
                son[u]=v;
            }
        }
    }
}

void dfs2(int u,int t){
    top[u]=t;
    dfn[u]=++dfncnt;
    if(son[u]){
        dfs2(son[u],t);
    }
    for(int i=head2[u];i;i=nxt2[i]){
        int v=to2[i];
        if(v!=fa[u]&&v!=son[u]){
            dfs2(v,v);
        }
    }
}

int lca(int a,int b){
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

int find(int x,int square){
    int pre=0;
    while(top[x]!=top[square]){
        pre=top[x];
        x=fa[top[x]];
    }
    return x==square?pre:son[square];
}

bool cmp1(int a,int b){
    return dfn[a]<dfn[b];
}

int buildvirtualtree(){
    sort(arr+1,arr+k+1,cmp1);
    int len=0;
    for(int i=1;i<k;i++){
        tmp[++len]=arr[i];
        tmp[++len]=lca(arr[i],arr[i+1]);
    }
    tmp[++len]=arr[k];

    sort(tmp+1,tmp+len+1,cmp1);

    int unique=1;
    for(int i=2;i<=len;i++){
        if(tmp[i]!=tmp[i-1]){
            tmp[++unique]=tmp[i];
        }
    }

    cntg3=1;
    for(int i=1;i<=unique;i++){
        head3[tmp[i]]=0;
    }

    for(int i=1;i<unique;i++){
        addedge3(lca(tmp[i],tmp[i+1]),tmp[i+1]);
    }
    return tmp[1];
}

void computeoncycle(int u,int siz){
    sort(idx + 1, idx + siz + 1, [](int a, int b) {
        return cyclelen[a] < cyclelen[b];
    });
    for (int i = 1; i <= siz; i++) {
        pre[i] = cyclelen[idx[i]];
        pre[i + siz] = pre[i] + cyclesum[u];
        val[i] = dist[idx[i]];
        val[i + siz] = val[i];
    }
    int l = 1;
    int r = 0;
    for (int i = 1; i <= siz * 2; i++) {
        while (l <= r && (pre[i] - pre[que[l]]) * 2 > cyclesum[u]) {
            l++;
        }
        if (l <= r) {
            diameter = max(diameter, val[que[l]] - pre[que[l]] + val[i] + pre[i]);
        }
        while (l <= r && val[que[r]] - pre[que[r]] <= val[i] - pre[i]) {
            r--;
        }
        que[++r] = i;
    }
}

void dpontree(int u){
    dist[u]=0;
    if(u<=n){
        for(int i=head3[u];i;i=nxt3[i]){
            int v=to3[i];
            dpontree(v);
            diameter=max(diameter,dist[u]+dist[v]+len[v]-len[u]);
            dist[u]=max(dist[u],dist[v]+len[v]-len[u]);
        }
    }
    else{
        for(int i=head3[u];i;i=nxt3[i]){
            int v=to3[i];
            dpontree(v);
        }

        int sz=0;
        for(int i=head3[u];i;i=nxt3[i]){
            int v=to3[i];
            int f=find(v,u);
            dist[f]=dist[v]+len[v]-len[f];
            idx[++sz]=f;
            dist[u]=max(dist[v]+len[v]-len[u],dist[u]);
        }
        computeoncycle(u,sz);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin>>n>>m;
    cntn=n;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        addedge1(u,v,w);
        addedge1(v,u,w);
    }

    tarjan(1,0);

    dfncnt=0;
    dfs1(1,0,0);
    dfs2(1,1);

    cin>>q;
    for(int i=1;i<=q;i++){
        cin>>k;
        for(int j=1;j<=k;j++){
            cin>>arr[j];
        }
        diameter=0;
        int tree=buildvirtualtree();
        dpontree(tree);
        cout<<diameter<<endl;
    }
    return 0;
}