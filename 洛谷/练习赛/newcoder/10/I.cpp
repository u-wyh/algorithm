#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500001;
const int MAXP = 1000002;
const int MAXT = 5000001;
const int MAXE = 10000001;

int n,cntt;

// 每个用户有两个候选串
string arr[MAXN<<1];

// 2-SAT建图
int headg[MAXT];
int nextg[MAXE];
int tog[MAXE];
int cntg;

// 前缀树优化建图
int tree[MAXP][26];
int fa[MAXP];
int up[MAXP];
int down[MAXP];
int cntp;

// 前缀树节点x拥有哪些候选串
int headx[MAXP];
int nextx[MAXP];
int tox[MAXP];
int cntx;

// 相同的候选串构成一组，进行前后缀优化建图
int group[MAXP];
int gsiz;

// Tarjan
int dfn[MAXT];
int low[MAXT];
int cntd;
int sta[MAXT];
int top;
int belong[MAXT];
int sccCnt;

void addEdge(int u,int v){
    nextg[++cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg;
}

int other(int x){
    return x<=n?x+n:x-n;
}

int newGraphNode(){
    headg[++cntt]=0;
    return cntt;
}

int newTrieNode(int f){
    int u=++cntp;
    memset(tree[u],0,sizeof(tree[u]));
    headx[u]=0;
    fa[u]=f;
    up[u]=down[u]=0;
    return u;
}

void addGroup(int u,int x){
    nextx[++cntx]=headx[u];
    tox[cntx]=x;
    headx[u]=cntx;
}

// 插入候选串，并连接其严格祖先和严格后代
void insert(int x){
    string &str=arr[x];
    int cur=1;

    for(int si=0;si<(int)str.length();si++){
        int path=str[si]-'a';

        if(tree[cur][path]==0){
            int v=newTrieNode(cur);
            tree[cur][path]=v;

            up[v]=newGraphNode();
            down[v]=newGraphNode();

            // up沿Trie向根移动
            addEdge(up[v],up[cur]);

            // down沿Trie向子树移动
            addEdge(down[cur],down[v]);
        }

        cur=tree[cur][path];
    }

    // 选择x以后，不能选择严格祖先中的候选
    addEdge(x,up[fa[cur]]);

    // up[cur]代表在cur结束的候选x
    addEdge(up[cur],other(x));

    // 选择x以后，不能选择严格后代中的候选
    addEdge(x,down[cur]);

    // down[fa[cur]]可以到达在cur结束的候选x
    addEdge(down[fa[cur]],other(x));

    addGroup(cur,x);
}

// 同一Trie节点上的候选两两冲突
// 使用前缀和后缀汇总将平方条边压缩成线性条边
void groupLink(){
    if(gsiz<=1){
        return;
    }

    int cur=newGraphNode();
    addEdge(cur,other(group[1]));

    for(int i=2;i<=gsiz;i++){
        int last=cur;
        cur=newGraphNode();
        addEdge(cur,other(group[i]));
        addEdge(group[i],last);
        addEdge(cur,last);
    }

    cur=newGraphNode();
    addEdge(cur,other(group[gsiz]));

    for(int i=gsiz-1;i>=1;i--){
        int last=cur;
        cur=newGraphNode();
        addEdge(cur,other(group[i]));
        addEdge(group[i],last);
        addEdge(cur,last);
    }
}

void buildGraph(){
    cntt=n<<1;
    cntg=0;
    cntp=0;
    cntx=0;

    // 先清空所有2-SAT文字节点
    memset(headg+1,0,sizeof(int)*(n<<1));

    newTrieNode(0);
    up[1]=newGraphNode();
    down[1]=newGraphNode();

    for(int x=1;x<=(n<<1);x++){
        insert(x);
    }

    for(int u=1;u<=cntp;u++){
        gsiz=0;
        for(int e=headx[u];e;e=nextx[e]){
            group[++gsiz]=tox[e];
        }
        groupLink();
    }
}

void tarjan(int u){
    dfn[u]=low[u]=++cntd;
    sta[++top]=u;

    for(int e=headg[u];e;e=nextg[e]){
        int v=tog[e];

        if(dfn[v]==0){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(belong[v]==0){
            low[u]=min(low[u],dfn[v]);
        }
    }

    if(dfn[u]==low[u]){
        sccCnt++;
        int pop;
        do{
            pop=sta[top--];
            belong[pop]=sccCnt;
        }while(pop!=u);
    }
}

void solve(){
    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>arr[i]>>arr[i+n];
    }

    buildGraph();

    memset(dfn+1,0,sizeof(int)*cntt);
    memset(belong+1,0,sizeof(int)*cntt);
    cntd=0;
    top=0;
    sccCnt=0;

    for(int i=1;i<=cntt;i++){
        if(dfn[i]==0){
            tarjan(i);
        }
    }

    for(int i=1;i<=n;i++){
        if(belong[i]==belong[i+n]){
            cout<<"NO\n";
            return;
        }
    }

    cout<<"YES\n";
    for(int i=1;i<=n;i++){
        if(belong[i]<belong[i+n]){
            cout<<'l';
        }
        else{
            cout<<'r';
        }
    }
    cout<<'\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin>>T;

    while(T--){
        solve();
    }

    return 0;
}
