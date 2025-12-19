// https://www.luogu.com.cn/problem/P6623
// 这道题很巧妙的将 01trie 和 树形dp 结合在一起
// 如何处理加一操作  如何合并信息  都是解题的关键
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 525015;
const int MAXT = 21*MAXN;

int n;
int val[MAXN];
long long ans;

int root[MAXN];
int trie[MAXT][2];
int sz[MAXT];
int eorval[MAXT];
int cnt;

int head[MAXN];
int nxt[MAXN];
int to[MAXN];
int cntg=1;

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

inline void addedge(int u,int v){
    nxt[cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg++;
}

// 基于子节点信息 更新Trie节点u的信息
void update(int u){
    int l=trie[u][0];
    int r=trie[u][1];

    // 更新节点计数：左右子树节点数之和
    sz[u]=sz[l]+sz[r];

    // 此时左右儿子的信息中实际上是没有当前这一位上的信息
    // 也就是说这一层的节点信息需要左右儿子提供高位上的信息  
    eorval[u]=(eorval[l]^eorval[r])<<1;
    // 最底层的信息 也就是最低位上的01需要根据这一层1的个数来决定
    if(sz[r]&1){
        eorval[u]^=1;
    }
}

// 对以u为根的Trie树进行整体加1操作
void addone(int u){
    if(u==0){
        // 表示这个节点从来就没有来过  那么也就无从加一
        return ;
    }
    // 将儿子中的01交换  因为原来最低位是0  那么现在一定是1  反之也是一样
    swap(trie[u][0],trie[u][1]);
    // 原来最低位是0的  加完1之后  这一位变为1  也就结束了
    // 但是原来这一位是1的  加完1之后 会产生进位1  继续递归
    addone(trie[u][0]);
    // 更新这个节点
    update(u);
}

// 向Trie树中插入一个值
// u: Trie树根节点   bit: 当前处理的二进制位
// x: 要插入的数值   返回: 插入后的新根节点
int insert(int u,int bit,int x){
    if(u==0){
        // 新建信息节点
        u=++cnt;
    }

    // 一共就是21层
    if(bit>20){
        // 来到了最底层  更新个数
        sz[u]++;
        return u;
    }

    // 递归插入到对应的子树中
    int b=(x>>bit)&1;
    trie[u][b]=insert(trie[u][b],bit+1,x);

    update(u);

    return u;
}

// 合并两棵Trie树
// a, b: 要合并的两棵Trie树的根节点
// bit: 当前处理的二进制位
// 返回: 合并后的新根节点
int merge(int a,int b,int bit){
    if(a==0||b==0){
        return a+b;
    }
    if(bit>20){
        sz[a]+=sz[b];
        return a;
    }
    trie[a][0]=merge(trie[a][0],trie[b][0],bit+1);
    trie[a][1]=merge(trie[a][1],trie[b][1],bit+1);
    update(a);
    return a;
}

void dfs(int u){
    root[u]=0;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
        // 子树加一
        addone(root[v]);
        // 汇总信息
        root[u]=merge(root[u],root[v],0);
    }
    // 加入自己的值
    root[u]=insert(root[u],0,val[u]);
    // 收集答案
    ans+=eorval[root[u]];
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=2;i<=n;i++){
        int fa=read();
        addedge(fa,i);
    }
    dfs(1);
    cout<<ans<<endl;
    return 0;
}