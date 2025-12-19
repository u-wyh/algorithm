// https://www.luogu.com.cn/problem/P2414
// 这道题的建图方式比较特殊 需要额外添加一个fa数组 然后继续跑AC自动机的常规代码
// 问题的关键就在于如何解决 第x个单词在第y个单词中出现的次数   
// 这个问题的推导的逻辑如下：
// 对于AC自动机而言 1、AC自动机的每个节点对应一个字符串前缀
//                2、节点u的fail指针指向v，表示v对应字符串是u对应字符串的最长后缀
// 对于通过fail指针建立的反向fail树而言：若节点v在节点u的Fail树子树中，则u对应的字符串是v对应字符串的后缀
// 比如u = "ab" → v = "xab"   ---->  则"ab"是"xab"的后缀
// x在y中出现的次数 = y的所有前缀中，以x为后缀的前缀数量(当然 你也可以说是所有后缀中 以x为前缀的数量  但是我们这里用到的是前面这种定义)  
// 从自动机的角度来看 我们假设 node_x是x的结束节点 path_y是y在Trie树上的路径（根节点到node_y）
// x在y中出现次数 = path_y上所有节点v中，满足 v 在 node_x 的 Fail树的子树中的数量
// 在某个节点的子树中出现的  这一类问题可以转换为  dfn序   在线性数组上处理
// 利用树状数组可以快速查询
// 于是 我们重新走建立AC自动机的过程  在这个过程中统计答案
// 这道题很考验对fail树的理解
// 对于fail树而言  这个节点的所有子树所对应的字符串一定包含这个节点对应的字符串  因此常常被用来收集词频
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

inline void addedge(int u,int v,int w){
    nxtq[cntq]=headq[u];
    toq[cntq]=v;
    idq[cntq]=w;
    headq[u]=cntq++;
}

//得到dfn序和子树大小
void dfs(int u){
    dfn[u]=++dfncnt;
    sz[u]=1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
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