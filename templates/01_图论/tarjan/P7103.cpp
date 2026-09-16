//https://www.luogu.com.cn/problem/P7103
//tarjan求lca操作
//这道题很巧妙的运用了tarjan求lca
//这道题不能使用倍增  因为会导致空间不够(5e6*20)  
// 这道题过于卡常，好像只有这一种写法可以通过
// 如果想要计算同一层dfn序号最大和最小值  实际上也会超时
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e6+5;

int n,m;
int fa[MAXN];
int ans[MAXN];
int dep[MAXN];

int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

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
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

void dfs(int u,int f){
    dep[u]=dep[f]+1;
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v,u);
        fa[v]=u;//遍历完子树后  那么这颗子树要和当前节点合并 并且代表节点设置成当前节点  
        //tarjan的经典操作
    }
    ans[dep[u]]= ans[dep[u]]?find(ans[dep[u]]):u;
	//ans[d[x]]表示在x节点之前的深度和d[x]一样的节点的lca  如果是0  就表示以前没有遇到过相同深度的  那么设置成自己
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=n;i++){
        int f;
        f=read();
        addedge(f,i);
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        cout<<ans[read()]<<endl;
    }
    return 0;
}