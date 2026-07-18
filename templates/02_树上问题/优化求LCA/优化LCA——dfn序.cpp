// dfn序求LCA，C++版
// 一共有n个节点，给定n-1条边，所有节点组成一棵树，给定树头root
// 一共有m条查询，格式 u v : 打印u和v的最低公共祖先
// 1 <= n、m <= 5 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P3379
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这种方法是找到a、b的dfn序号，那么lca就是从 dfn小的+1 到 dfn大的这些序号的节点的父亲节点中
// 选择一个深度最小的
// 因为如果x是ab的lca，那么从dfn[a]+1到dfn[b]中，一定存在节点的父亲是x 
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXP = 20;

int n,m,root;

int headg[MAXN];
int nxtg[MAXN<<1];
int tog[MAXN<<1];
int cntg=1;

int dfn[MAXN];
int lg2[MAXN];
int rmq[MAXN][MAXP];
int dfncnt;

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

// 如果xy存在上下级关系，那么可以用dfn序号来判断祖先
int getup(int x,int y){
    return dfn[x]<dfn[y]?x:y;
}

void dfs(int u,int fa){
    dfn[u]=++dfncnt;
    rmq[dfn[u]][0]=fa;
    for(int i=headg[u];i;i=nxtg[i]){
        int v=tog[i];
        if(v!=fa){
            dfs(v,u);
        }
    }
}

void buildrmq(){
    dfs(root,0);
    for(int i=2;i<=n;i++){
        lg2[i]=lg2[i>>1]+1;
    }
    for(int pre=0,cur=1;cur<=lg2[n];pre++,cur++){
        for(int i=1;i+(1<<cur)-1<=n;i++){
            rmq[i][cur]=getup(rmq[i][pre],rmq[i+(1<<pre)][pre]);
        }
    }
}

int getlca(int x,int y){
    if(x==y){
        return x;
    }
    x=dfn[x];
    y=dfn[y];
    if(x>y){
        swap(x,y);
    }
    x++;
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