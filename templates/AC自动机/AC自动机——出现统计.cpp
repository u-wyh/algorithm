// https://www.luogu.com.cn/problem/P8451
// 思路是非常巧妙的   是在树状数组中添加答案 不是一般的在树状数组查询答案
// 这道题的统计方式是非常独特的  这道题看起来需要持久化操作
// 但是没有强制在线的要求  那么这个持久化操作就可以被当做离线操作来处理
// 我们首先将所有会被插入的字符串全部插进AC自动机中  然后建立起fail树  得到dfn序
// 我们知道在fail树中  一个节点子树中的所有节点都包括了这个节点所代表的字符串
// 我们根据操作的顺序决定树状数组上的状态 在fail树中一个节点出现了一次 意味着他的所有祖先节点出现了
// 那么根据这个性质  我们可以将判断一个字符串是否出现  变为这个字符串的完全状态在他的子树节点中的状态
// 那么在查询的时候 如果目前的节点查询出来的结果就是需要查询的贡献
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXM = 5e5+5;

int q;
int op[MAXM];
char t[MAXN];
vector<char>s[MAXM];

int ans[MAXM];

int cnt;
int trie[MAXN][26];
int fail[MAXN];

int head[MAXM];
int nxt[MAXM];
int to[MAXM];
int cntg=1;

int headq[MAXN];
int nxtq[MAXN];
int toq[MAXN];
int cntq=1;

int dfn[MAXN];
int sz[MAXN];
int dfncnt;

int tree[MAXN];

void insert(){
    int cur=0;
    int len=strlen(t+1);
    for(int i=1;i<=len;i++){
        char ch=t[i];
        int path=ch-'a';
        if(trie[cur][path]==0){
            trie[cur][path]=++cnt;
        }
        cur=trie[cur][path];
    }
}

void setfail(){
    queue<int>q;
    for(int i=0;i<26;i++){
        if(trie[0][i]){
            q.push(trie[0][i]);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<26;i++){
            if(trie[u][i]==0){
                trie[u][i]=trie[fail[u]][i];
            }
            else{
                fail[trie[u][i]]=trie[fail[u]][i];
                q.push(trie[u][i]);
            }
        }
    }
}

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

inline void addEdge(int u,int v){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    headq[u]=cntq++;
}

void dfs(int u){
    dfn[u]=++dfncnt;
    sz[u]=1;
    for(int i=headq[u];i;i=nxtq[i]){
        int v=toq[i];
        dfs(v);
        sz[u]+=sz[v];
    }
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=dfncnt){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

void update(int id,int v){
    int cur=0;
    for(char ch:s[id]){
        cur=trie[cur][ch-'a'];
    }
    add(dfn[cur],v);
    add(dfn[cur]+sz[cur],-v);
}

int query(int u){
    int ans=0;
    int cur=0;
    for(char ch:s[u]){
        cur=trie[cur][ch-'a'];
        int x=dfn[cur];
        while(x){
            ans+=tree[x];
            x-=lowbit(x);
        }
    }
    return ans;
}

void dfs1(int u){
    if(op[u]==1){
        update(u,1);
    }
    if(op[u]==2){
        ans[u]=query(u);
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs1(v);
    }
    if(op[u]==1){
        update(u,-1);
    }
}

int main()
{
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        int fa;
        scanf("%d %d",&op[i],&fa);
        addedge(fa,i);
        scanf("%s",t+1);
        int n=strlen(t+1);
        for(int j=1;j<=n;j++){
            s[i].push_back(t[j]);
        }
        if(op[i]==1){
            insert();
        }
    }
    setfail();
    for(int i=1;i<=cnt;i++){
        addEdge(fail[i],i);
    }
    dfs(0);
    dfs1(0);
    for(int i=1;i<=q;i++){
        if(op[i]==2){
            cout<<ans[i]<<endl;
        }
    }
    return 0;
}