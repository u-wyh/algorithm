// https://www.luogu.com.cn/problem/P5168
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 3e5+5;
const int MAXQ = 2e5+5;
const int MAXH = 20;

int n,m,q,p;
int col[MAXN];

struct Edge{
    int u,v,w;
};
Edge edge[MAXM];
bool cmp(Edge &a,Edge &b){
    return a.w<b.w;
}

int cntn;
int fa[MAXN];
int nodekey[MAXN];

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

int dep[MAXN];
int st[MAXN][MAXH];

struct Query{
    int l,r,t,id;
};
struct Update{
    int pos,val;
};
Query query[MAXQ];
Update update[MAXQ];
int cntq;
int cntu;
int cntans;

int cnt[MAXN];
int kind;
int ans[MAXQ];

int sorted[MAXN<<1];
int len;

int dfncnt;
int dfn[MAXN];
int lt[MAXN];
int rt[MAXN];

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void kruskalrebuild(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    sort(edge+1,edge+m+1,cmp);
    cntn=n;
    for(int i=1;i<=m;i++){
        int u=edge[i].u;
        int v=edge[i].v;
        int fu=find(u);
        int fv=find(v);
        if(fu!=fv){
            int rt=++cntn;
            nodekey[rt]=edge[i].w;
            fa[rt]=rt;
            addedge(rt,fu);
            addedge(rt,fv);
            fa[fu]=rt;
            fa[fv]=rt;
        }
    }
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }

    lt[u]=dfncnt+1;

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
    }

    if(u<=n){
        dfn[u]=++dfncnt;
    }
    rt[u]=dfncnt;
}

int lca(int x,int y){
    if(dep[x]<dep[y]){
        swap(x,y);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[x][i]]>=dep[y]){
            x=st[x][i];
        }
    }
    if(x==y){
        return x;
    }

    for(int i=p;i>=0;i--){
        if(st[x][i]!=st[y][i]){
            x=st[x][i];
            y=st[y][i];
        }
    }
    return st[x][0];
}

int find1(int x){
    int l=1,r=len,ans=len;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=x){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int calc(int x,int limit){
    for(int i=p;i>=0;i--){
        if(st[x][i]){
            if(nodekey[st[x][i]]<=limit){
                x=st[x][i];
            }
        }
    }
    return x;
}

int arr[MAXN];
int bi[MAXN];

bool cmp1(Query &a,Query &b){
    if(bi[a.l]!=bi[b.l]){
        return bi[a.l]<bi[b.l];
    }

    if(bi[a.r]!=bi[b.r]){
        return bi[a.r]<bi[b.r];
    }

    return a.t<b.t;
}

void add(int num){
    if(++cnt[num]==1){
        kind++;
    }
}

// 删除颜色
void del(int num){
    if(--cnt[num]==0){
        kind--;
    }
}

void moveTime(int jobl,int jobr,int tim){
    int pos=update[tim].pos;
    int val=update[tim].val;

    if(jobl<=pos&&pos<=jobr){
        del(arr[pos]);
        add(val);
    }

    // 交换即可同时支持修改和撤销
    swap(arr[pos],update[tim].val);
}

void compute(){
    int winl=1,winr=0,wint=0;

    for(int i=1;i<=cntq;i++){
        int jobl=query[i].l;
        int jobr=query[i].r;
        int jobt=query[i].t;
        int id=query[i].id;

        while(winl>jobl){
            add(arr[--winl]);
        }
        while(winr<jobr){
            add(arr[++winr]);
        }
        while(winl<jobl){
            del(arr[winl++]);
        }
        while(winr>jobr){
            del(arr[winr--]);
        }

        while(wint<jobt){
            moveTime(jobl,jobr,++wint);
        }
        while(wint>jobt){
            moveTime(jobl,jobr,wint--);
        }

        ans[id]=kind;
    }
}

void prepare(){
    int blen=max(1,(int)pow(n,2.0/3));
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    sort(query+1,query+cntq+1,cmp1);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m>>q;
    int k=0;
    for(int i=1;i<=n;i++){
        cin>>col[i];
        sorted[++k]=col[i];
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edge[i]={u,v,w};
    }

    kruskalrebuild();

    p=log2(n)+1;
    for(int i=1;i<=cntn;i++){
        if(i==find(i)){
            dfs(i,0);
        }
    }

    for(int i=1;i<=q;i++){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==1){
            sorted[++k]=y;
            ++cntu;
            update[cntu]={dfn[x],y};
        }
        else if(op==2){
            ++cntans;
            ans[cntans]=nodekey[lca(x,y)];
        }
        else{
            int u=calc(x,y);
            ++cntq;
            ++cntans;
            query[cntq]={lt[u],rt[u],cntu,cntans};
        }
    }

    sort(sorted+1,sorted+k+1);
    len=1;
    for(int i=2;i<=k;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }

    for(int i=1;i<=n;i++){
        arr[dfn[i]]=find1(col[i]);
    }
    for(int i=1;i<=cntu;i++){
        update[i].val=find1(update[i].val);
    }

    prepare();
    compute();

    for(int i=1;i<=cntans;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}