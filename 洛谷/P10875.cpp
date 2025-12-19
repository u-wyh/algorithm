// https://www.luogu.com.cn/problem/P10875
//这道题可以用并查集来解决边双问题   题目实际上要我们求的就是u v最早什么时候可以是在同一个边双中
//我们首先可以建立起一个dfs树  把所有的树边加进来  构成一棵树
//所有的非树边我们记录下u v以及添加的时间
//在同一个边双中  那么意味着他们肯定在一个环中  树上是不可能存在环的
//所以如果想要构成环  那么一定是通过非树边
//一条非树边可以更新他的两个顶点之间的最短路径上的边变成环的时间（这个地方我是通过并查集实现的）
//在查询的时候  如果不在一个联通块中  那么直接输出-1
//否则我们查询u v之间的最短路径上的边的变成某一个环的一部分的最晚时间  如果存在边始终不是  那么输出-1
//我们可以通过倍增实现这个查询
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int LIMIT = 20;

int n,m,p;

int fa[MAXN];//生成树所用的并查集  也用于最后判断是否在同一个联通块

//我们更新每条边变成某个环的一部分  由于这些边都是树边  所以我们用节点也是同样效果
int fa2[MAXN];//使用节点并查集  查询如果当前来到这个节点 他的上面的第一个边没有被更新的点
int covertime[MAXN];//每条边的最早更新时间

//根据生成树  做出倍增表  求lca
int dep[MAXN];
int st[MAXN][LIMIT];

//g[i][j]表示从i出发  往上数2^j条边  这些边中的最晚更新时间
int g[MAXN][LIMIT];

//存储非树边
struct node{
    int u,v,id;
};
node nontree[MAXN];
int noncnt;

int head[MAXN];
int nxt[MAXN<<1];
int to[MAXN<<1];
int cnt=1;

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void dfs(int u,int fa){
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    for(int i=1;i<=p;i++){
        st[u][i]=st[st[u][i-1]][i-1];
    }
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==fa){
            continue;
        }
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(dep[a]<dep[b]){
        swap(a,b);
    }
    for(int i=p;i>=0;i--){
        if(dep[st[a][i]]>=dep[b]){
            a=st[a][i];
        }
    }
    if(a==b){
        return a;
    }
    for(int i=p;i>=0;i--){
        if(st[a][i]!=st[b][i]){
            a=st[a][i];
            b=st[b][i];
        }
    }
    return st[a][0];
}

int find2(int x){
    return x==fa2[x]?x:fa2[x]=find2(fa2[x]);
}

//通过时间为t的非树边来更新从x到y这中间的树边的时间
void update(int x,int y,int t){
    x=find2(x);
    while(dep[x]>dep[y]){
        covertime[x]=t;
        fa2[x]=find2(st[x][0]);
        x=find2(x);
    }
}

//查询从x到y中间的路径上的所有树边的最晚更新时间
int query(int x,int y){
    if(x==y){
        return 0;
    }
    int ans=0;
    for(int i=p;i>=0;i--){
        if(dep[st[x][i]]>=dep[y]){
            ans=max(ans,g[x][i]);
            x=st[x][i];
        }
    }
    return ans;
}

int main()
{
    n=read(),m=read();
    p=log2(n)+1;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        int fu=find(u),fv=find(v);
        if(fu!=fv){
            fa[fu]=fv;
            addedge(u,v);
            addedge(v,u);
        }
        else{
            nontree[++noncnt]={u,v,i};
        }
    }
    for(int i=1;i<=n;i++){
        if(dep[i]==0){
            dfs(i,0);
        }
    }
    for(int i=1;i<=n;i++){
        fa2[i]=i;
    }

    for(int i=1;i<=noncnt;i++){
        int u=nontree[i].u;
        int v=nontree[i].v;
        int w=nontree[i].id;
        int uvlca=lca(u,v);
        update(u,uvlca,w);
        update(v,uvlca,w);
    }

    for(int i=1;i<=n;i++){
        if(covertime[i]==0){
            covertime[i]=m+1;//如果没有被覆盖  那么时间设置为m+1
        }
        g[i][0]=covertime[i];
    }
    //注意枚举顺序  要先枚举层次
    for(int i=1;i<=p;i++){
        for(int j=1;j<=n;j++){
            g[j][i]=max(g[j][i-1],g[st[j][i-1]][i-1]);
        }
    }
    int ques=read();
    while(ques--){
        int u,v;
        u=read(),v=read();
        if(find(u)!=find(v)){
            printf("-1\n");
        }
        else{
            int falca=lca(u,v);
            int ans=max(query(u,falca),query(v,falca));
            if(ans==m+1){
                printf("-1\n");
            }
            else{
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}