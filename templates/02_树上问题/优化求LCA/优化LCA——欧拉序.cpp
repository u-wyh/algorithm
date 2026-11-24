// 欧拉序求LCA，C++版
// 一共有n个节点，给定n-1条边，所有节点组成一棵树，给定树头root
// 一共有m条查询，格式 u v : 打印u和v的最低公共祖先
// 1 <= n、m <= 5 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3379
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 记录每个位置最早被访问的欧拉序编号
// 那么查询两个点的LCA就是这两个欧拉序之间的深度最低的节点
// 因为如果x节点是他们的lca，那么他们中间经过的点一定会包括x
// 但是一定不会包括x的祖先节点中的任何一个
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXP = 20;

int n,m,root;

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int cntg=1;

int first[MAXN];
int lg2[MAXN<<1];
int rmq[MAXN<<1][MAXP];
int cnteuler;

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

void addedge(int u,int v){
    nxtg[cntg]=headg[u];
    tog[cntg]=v;
    headg[u]=cntg++;
}

// 如果x，y具有上下级关系，那么应该用dep数组来判断，但是也可以用first来判断
int getup(int x,int y){
    return (first[x]<first[y])?x:y;
}

void dfs(int u,int fa){
    first[u]=++cnteuler;
    rmq[cnteuler][0]=u;
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=fa){
            dfs(v,u);
            rmq[++cnteuler][0]=u;
        }
    }
}

void buildrmq(){
    dfs(root,0);
    for(int i=2;i<=cnteuler;i++){
        lg2[i]=lg2[i>>1]+1;
    }
    for(int pre=0,cur=1;cur<=lg2[cnteuler];pre++,cur++){
        for(int i=1;i+(1<<cur)-1<=cnteuler;i++){
            rmq[i][cur]=getup(rmq[i][pre],rmq[i+(1<<pre)][pre]);
        }
    }
}

int getlca(int x,int y){
    x=first[x];
    y=first[y];
    if(x>y){
        swap(x,y);
    }
    int k=lg2[y-x+1];
    return getup(rmq[x][k],rmq[y-(1<<k)+1][k]);
}

int main()
{
    n=read(),m=read(),root=read();
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    buildrmq();
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        cout<<getlca(u,v)<<endl;
    }
    return 0;
}