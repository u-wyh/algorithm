// https://www.luogu.com.cn/problem/P9340
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXH = 20;

int n,m,q;

// 表示原图的边
int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cntg=1;

// 树链剖分相关
int dfncnt;
int dfn[MAXN];
int fa[MAXN];
int son[MAXN];
int sz[MAXN];
int top[MAXN];
int dep[MAXN];

// 表示这个长链的长度
int len[MAXN];
// 表示这个节点是这个长链的第几个节点
int pos[MAXN];
// 表示这个节点所在长链的编号
int id[MAXN];
int cntid;

// 用于记录每个长链的颜色段
struct node{
    int col,r;
};
stack<node>stk[MAXN];

int spot[MAXN];
int lg2[MAXN];
int stmin[MAXH][MAXN];
int stmax[MAXH][MAXN];

int headq[MAXN];
int nxtq[MAXN];
int toq[MAXN];
int idq[MAXN];
int cntq=1;

// 用于统计每种颜色的节点个数
int tree[MAXN<<2];

int ans[MAXN];

void addedgeq(int u,int v,int id){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    idq[cntq]=id;
    headq[u]=cntq++;
}

void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

void dfs1(int u,int f){
    sz[u]=1;
    dep[u]=dep[f]+1;
    fa[u]=f;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=f){
            dfs1(v,u);
            sz[u]+=sz[v];
            if(sz[v]>sz[son[u]]){
                son[u]=v;
            }
        }
    }
}

void dfs2(int u,int t){
    dfn[u]=++dfncnt;
    pos[u]=++len[t];
    id[u]=id[t];
    top[u]=t;

    if(son[u]){
        dfs2(son[u],t);
    }

    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v!=fa[u]&&v!=son[u]){
            id[v]=++cntid;
            dfs2(v,v);
        }
    }
}

void prepare(){
    dfs1(1,0);

    id[1]=++cntid;
    dfs2(1,1);

    for(int i=1;i<=n;i++){
        if(top[i]==i){
            stk[id[i]].push({0,len[i]});
        }
    }
}

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}

int rangelca(int l,int r){
    int k=lg2[r-l+1];
    int t=r-(1<<k)+1;
    int mn,mx;
    if(dfn[stmin[k][l]]<dfn[stmin[k][t]]){
        mn=stmin[k][l];
    }
    else{
        mn=stmin[k][t];
    }
    if(dfn[stmax[k][l]]>dfn[stmax[k][t]]){
        mx=stmax[k][l];
    }
    else{
        mx=stmax[k][t];
    }
    // cout<<l<<' '<<r<<' '<<t<<' '<<k<<' '<<mn<<' '<<mx<<' '<<lca(mn,mx)<<endl;
    return lca(mn,mx);
}

void buildst(){
    lg2[0]=-1;
    for(int i=1;i<=m;i++){
        lg2[i]=lg2[i>>1]+1;
    }
    for(int i=1;i<=m;i++){
        stmin[0][i]=stmax[0][i]=spot[i];
    }
    for(int k=1;(1<<k)<=m;k++){
        for(int i=1;i+(1<<k)-1<=m;i++){
            if(dfn[stmin[k-1][i]]<dfn[stmin[k-1][i+(1<<(k-1))]]){
                stmin[k][i]=stmin[k-1][i];
            }
            else{
                stmin[k][i]=stmin[k-1][i+(1<<(k-1))];
            }

            
            if(dfn[stmax[k-1][i]]>dfn[stmax[k-1][i+(1<<(k-1))]]){
                stmax[k][i]=stmax[k-1][i];
            }
            else{
                stmax[k][i]=stmax[k-1][i+(1<<(k-1))];
            }

            // cout<<"  "<<k<<' '<<i<<' '<<stmin[k][i]<<' '<<stmax[k][i]<<endl;
        }
    }
}

void add(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]+=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            add(pos,jobv,l,mid,i<<1);
        }
        else{
            add(pos,jobv,mid+1,r,i<<1|1);
        }
        tree[i]=tree[i<<1]+tree[i<<1|1];
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

void calc(int x,int len,int c){
    int now=1;
    while(true){
        node tmp=stk[x].top();
        stk[x].pop();
        int r=tmp.r;
        int col=tmp.col;
        if(r<=len){
            if(col)
                add(col,-(r-now+1),1,m,1);
            now=r+1;
        }
        else{
            if(col)
                add(col,-(len-now+1),1,m,1);
            stk[x].push(tmp);
            now=len+1;
        }
        if(now>len){
            break;
        }
    }
    add(c,len,1,m,1);
    stk[x].push({c,len});
}

void update(int x,int c){
    while(x){
        calc(id[x],pos[x],c);
        x=fa[top[x]];
    }
}

void compute(){
    for(int l=m;l>=1;l--){
        update(spot[l],l);

        for(int i=headq[l];i;i=nxtq[i]){
            int r=toq[i];
            int id=idq[i];

            int lcalr=rangelca(l,r);
            ans[id]=query(l,r,1,m,1)-dep[lcalr]+1;
        }
    }
}

int main()
{
    cin>>n>>m>>q;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }

    prepare();

    for(int i=1;i<=m;i++){
        cin>>spot[i];
    }
    buildst();

    // for(int i=1;i<=n;i++){
    //     cout<<i<<":   "<<dfn[i]<<endl;
    // }

    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        addedgeq(l,r,i);

        // cout<<i<<":  "<<' '<<l<<' '<<r<<' '<<rangelca(l,r)<<endl;
    }

    compute();

    for(int i=1;i<=q;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}