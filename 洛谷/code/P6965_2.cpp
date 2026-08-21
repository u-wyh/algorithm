#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
const int MAXP = 1000005;
const int MAXT = 6000000;
const int MAXE = 12000000;

int n;

// 两个候选字符串
string s[MAXN << 1];

// 2-SAT图
int head[MAXT];
int nxt[MAXE];
int to[MAXE];
int cntg;

void addEdge(int u,int v){
    nxt[++cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg;
}

// Trie
int trie[MAXP][2];
int faTrie[MAXP];
int trieCnt=1;

vector<int> endNode[MAXP];

// Trie树
int headT[MAXP];
int nxtT[MAXP<<1];
int toT[MAXP<<1];
int cntT;

void addTrieEdge(int u,int v){
    nxtT[++cntT]=headT[u];
    toT[cntT]=v;
    headT[u]=cntT;
}


// HLD
int dep[MAXP];
int siz[MAXP];
int son[MAXP];
int top[MAXP];
int dfn[MAXP];
int out[MAXP];
int revv[MAXP];
int dfsCnt;


void dfs1(int u){
    siz[u]=1;
    for(int e=headT[u];e;e=nxtT[e]){
        int v=toT[e];
        dep[v]=dep[u]+1;
        dfs1(v);
        siz[u]+=siz[v];
        if(!son[u]||siz[v]>siz[son[u]])
            son[u]=v;
    }
}

void dfs2(int u,int tp){
    top[u]=tp;
    dfn[u]=++dfsCnt;
    revv[dfsCnt]=u;

    if(son[u])
        dfs2(son[u],tp);

    for(int e=headT[u];e;e=nxtT[e]){
        int v=toT[e];
        if(v!=son[u])
            dfs2(v,v);
    }

    out[u]=dfsCnt;
}


// 线段树
int ls[MAXT];
int rs[MAXT];
int segRoot;
int tot;


void buildSeg(int l,int r,int rt){
    if(l==r){
        int u=revv[l];

        // Trie节点上的所有字符串
        for(int x:endNode[u]){
            addEdge(rt,n-x);
        }
        return;
    }

    int mid=(l+r)>>1;

    ls[rt]=++tot;
    rs[rt]=++tot;

    buildSeg(l,mid,ls[rt]);
    buildSeg(mid+1,r,rs[rt]);

    addEdge(rt,ls[rt]);
    addEdge(rt,rs[rt]);
}


void rangeAdd(int rt,int l,int r,int L,int R,int from){
    if(L>R)
        return;

    if(L<=l&&r<=R){
        addEdge(from,rt);
        return;
    }

    int mid=(l+r)>>1;

    if(L<=mid)
        rangeAdd(ls[rt],l,mid,L,R,from);

    if(R>mid)
        rangeAdd(rs[rt],mid+1,r,L,R,from);
}


// 树链剖分路径
void pathAdd(int x,int y,int from){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);

        rangeAdd(segRoot,1,trieCnt,
                 dfn[top[x]],dfn[x],from);

        x=faTrie[top[x]];
    }

    if(dep[x]>dep[y])
        swap(x,y);

    rangeAdd(segRoot,1,trieCnt,
             dfn[x],dfn[y],from);
}


// SCC
int dfnS[MAXT];
int low[MAXT];
int sta[MAXT];
int ins[MAXT];
int belong[MAXT];
int idx,topS,scc;


void tarjan(int u){
    dfnS[u]=low[u]=++idx;
    sta[++topS]=u;
    ins[u]=1;

    for(int e=head[u];e;e=nxt[e]){
        int v=to[e];

        if(!dfnS[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(ins[v]){
            low[u]=min(low[u],dfnS[v]);
        }
    }

    if(dfnS[u]==low[u]){
        ++scc;

        while(1){
            int x=sta[topS--];
            ins[x]=0;
            belong[x]=scc;

            if(x==u)
                break;
        }
    }
}


int other(int x){
    if(x<=n)
        return x+n;
    return x-n;
}


// 输入处理
void addString(int id,string str){
    int pos=-1;

    for(int i=0;i<(int)str.size();i++){
        if(str[i]=='?'){
            pos=i;
            break;
        }
    }

    if(pos==-1){
        s[id]=str;
        s[id+n]=str;

        if(str[0]=='0')
            addEdge(id+n,id);
        else
            addEdge(id,id+n);

        return;
    }

    str[pos]='0';
    s[id]=str;

    str[pos]='1';
    s[id+n]=str;
}


int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cin>>n;


    for(int i=1;i<=n;i++){
        string x;
        cin>>x;
        addString(i,x);
    }


    // 建Trie
    for(int i=1;i<=2*n;i++){

        int u=1;

        for(char c:s[i]){

            int v=c-'0';

            if(!trie[u][v]){
                trie[u][v]=++trieCnt;
                faTrie[trieCnt]=u;

                addTrieEdge(u,trieCnt);
            }

            u=trie[u][v];
        }

        endNode[u].push_back(i);
    }


    // Trie树HLD
    dep[1]=1;
    dfs1(1);
    dfs2(1,1);


    // 线段树节点从2n之后开始
    tot=2*n;
    segRoot=++tot;

    buildSeg(1,trieCnt,segRoot);


    // 建约束

    for(int i=1;i<=2*n;i++){

        int u=1;

        for(char c:s[i])
            u=trie[u][c-'0'];


        // 同一个节点字符串冲突
        for(int x:endNode[u]){
            if(x!=i)
                addEdge(i,other(x));
        }


        // 后代冲突
        for(int v=0;v<2;v++){

            int sonNode=trie[u][v];

            if(sonNode){

                rangeAdd(segRoot,1,trieCnt,
                         dfn[sonNode],
                         out[sonNode],
                         i);
            }
        }


        // 祖先冲突
        if(u!=1)
            pathAdd(1,faTrie[u],i);
    }


    for(int i=1;i<=tot;i++){
        if(!dfnS[i])
            tarjan(i);
    }


    for(int i=1;i<=n;i++){

        if(belong[i]==belong[i+n]){
            cout<<"NO\n";
            return 0;
        }
    }


    cout<<"YES\n";

    for(int i=1;i<=n;i++){

        if(belong[i]<belong[i+n])
            cout<<s[i]<<"\n";
        else
            cout<<s[i+n]<<"\n";
    }

    return 0;
}