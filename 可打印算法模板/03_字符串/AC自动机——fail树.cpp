// 用途：AC 自动机的 fail 指针反向建树，查询一个已打印单词在另一打印文本中出现几次。
// 时间：建 Trie/AC O(26N)，编辑与询问 O((N+Q)log N)；N 为操作串长度。
// 空间：O(26N+Q)。
// 注意：操作串含小写字母、B(退格)、P(打印)；N,Q≤100000，退格时当前串非空。
// 例题：https://www.luogu.com.cn/problem/P2414
// 题意：打字机产生多个单词，询问第 x 个打印单词在第 y 个打印单词中出现次数。
// 思路：文本每个前缀在 Trie 中对应一节点；模式串节点的 fail 树子树统计这些节点。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

string s;
int n;

int cnt;
int trie[MAXN][26];
int fail[MAXN];
//这里比一般的AC自动机多出来的部分 是由于建立自动机时的特殊情况所决定的  用于B、P操作
int fa[MAXN];
int endpos[MAXN];//记录这个是为了在统计答案的时候更方便  具体参见代码

//fail树的建图
int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

//查询问题的建图
int headq[MAXN];
int nxtq[MAXN];
int toq[MAXN];
int idq[MAXN];
int cntq=1;

int dfn[MAXN];
int sz[MAXN];
int dfncnt;

int tree[MAXN];

int ans[MAXN];
int bfsQueue[MAXN], dfsStack[MAXN], nextEdge[MAXN];

void setfail(){
    int front=0, back=0;
    for(int i=0;i<26;i++){
        if(trie[0][i]){
            bfsQueue[back++]=trie[0][i];
        }
    }
    while(front<back){
        int u=bfsQueue[front++];
        for(int i=0;i<26;i++){
            if(trie[u][i]==0){
                trie[u][i]=trie[fail[u]][i];
            }
            else{
                fail[trie[u][i]]=trie[fail[u]][i];
                bfsQueue[back++]=trie[u][i];
            }
        }
    }
}

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

inline void addedge(int u,int v,int w){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    idq[cntq]=w;
    headq[u]=cntq++;
}

// 按 DFS 序展开 fail 树；深链用定长栈避免递归爆栈。
void dfs(int u){
    int top=0;
    dfsStack[top++]=u;
    while(top){
        int cur=dfsStack[top-1];
        if(!dfn[cur]){
            dfn[cur]=++dfncnt;
            sz[cur]=1;
            nextEdge[cur]=head[cur];
        }
        if(nextEdge[cur]){
            int e=nextEdge[cur];
            nextEdge[cur]=nxt[e];
            dfsStack[top++]=to[e];
        }else{
            --top;
            if(top) sz[dfsStack[top-1]]+=sz[cur];
        }
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

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int main()
{
    cin>>s;

    //直接建立AC自动机
    int cur=0;//当前来到的自动机节点编号
    int id=0;//当前字符串的序号
    for(char c:s){
        if(c=='B'){
            //回退操作
            cur=fa[cur];
        }
        else if(c=='P'){
            //新建一个单词
            endpos[++id]=cur;
        }
        else{
            int path=c-'a';
            if(trie[cur][path]==0){
                trie[cur][path]=++cnt;
                fa[cnt]=cur;
            }
            cur=trie[cur][path];
        }
    }

    setfail();

    //建立fail树  反向建树
    for(int i=1;i<=cnt;i++){
        addedge(fail[i],i);
    }

    //得到dfn序
    dfs(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        addedge(y,x,i);
    }

    //重新跑一遍trie  统计答案
    cur=0;
    id=0;
    for(char c:s){
        if(c=='B'){
            add(dfn[cur],-1);//移除当前节点
            cur=fa[cur];
        }
        else if(c=='P'){
            id++;
            for(int i=headq[id];i;i=nxtq[i]){
                int v=toq[i];
                int w=idq[i];
                int node=endpos[v];
                ans[w]=query(dfn[node]+sz[node]-1)-query(dfn[node]-1);
            }
        }
        else{
            int path=c-'a';
            cur=trie[cur][path];
            add(dfn[cur],1);//当前节点加入树状数组中
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
