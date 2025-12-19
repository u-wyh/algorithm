#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int LIMIT = 16;

int n,m,power;

int ans[MAXN];//记录答案
vector<pair<int,int>>vec[MAXN];//初始时的边  和  边的编号

struct node{
    int u,v,w;
}nums[MAXN];//新建的边

int to[MAXN];//这个是用于记录如果到达当前节点  实际上是跳转到那个节点
int son[MAXN];//这个用于记录每条原始的边中较低的节点  用于统计答案

int deep[MAXN];
int st[MAXN][LIMIT];

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

bool cmp(node a,node b){
    return a.w<b.w;
}

void dfs(int u, int f) {
    deep[u] = deep[f] + 1;
    st[u][0] = f;
    for (int p = 1; p <= power; p++) {
        st[u][p] = st[st[u][p - 1]][p - 1];
    }
    //完成u的deep  stjump
    for(int i=0;i<vec[u].size();i++){
        int v=vec[u][i].first;
        int id=vec[u][i].second;
        if(v==f){
            continue;
        }
        son[id]=v;//表示这条边要是断了  那么要记录的是v这个节点的答案
        dfs(v,u);
    }
}

int lca(int a, int b) {
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //确定大小关系
    for (int p = power; p >= 0; p--) {
        if (deep[st[a][p]] >= deep[b]) {
            a = st[a][p];
        }
    }
    //首先将两者变为同一高度
    if (a == b) {
        return a;
    }
    //如果相同说明就是祖先关系
    for (int p = power; p >= 0; p--) {
        if (st[a][p] != st[b][p]) {
            a = st[a][p];
            b = st[b][p];
        }
        //判断跳完后是否符合规则
    }
    return st[a][0];
    //我们将头结点的祖先设置为0  实际上没有0
}

//类似于并查集的工作
int find(int x){
    return x==to[x]?x:to[x]=find(to[x]);
}

int main()
{
    n=read(),m=read();
    power=(int)log2(n);
    for(int i=1;i<n;i++){
        int u,v;
        u=read(),v=read();
        vec[u].push_back({v,i});
        vec[v].push_back({u,i});
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        nums[i].u=read();
        nums[i].v=read();
        nums[i].w=read();
    }
    sort(nums+1,nums+m+1,cmp);
    for(int i=1;i<=n;i++){
        to[i]=i;//初始时 每个节点所代表的都是自己
        ans[i]=-1;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=power;j++){
            cout<<st[i][j]<<' ';
        }
        cout<<endl;
    }
    for(int i=0;i<=n;i++){
        cout<<deep[i]<<' ';
    }
    cout<<endl;
    for(int i=1;i<=m;i++){
        int u=nums[i].u;
        int v=nums[i].v;
        int w=nums[i].w;
        int fa=lca(u,v);
        //cout<<u<<' '<<v<<' '<<w<<' '<<fa<<' '<<st[u][0]<<' '<<st[v][0]<<endl;
        //实际上这个目前的值影响到的是  从u到lca  和  从v到lca  不包括lca
        for(int u=find(u);deep[u]>deep[fa];u=find(st[u][0])){
            //表示的是 来到了u节点 实际上跳转到了哪里
            //本次更新要将这个节点的答案更新  原来一定是没有答案的  如果有答案 一定不会到达这个节点
            //这个节点完成 那么以后到达这个节点  一定会直接去上面
            ans[u]=w;
            to[u]=st[u][0];
            cout<<' '<<u<<endl;
        }
        for(int v=find(v);deep[v]>deep[fa];v=find(st[v][0])){
            ans[v]=w;
            to[v]=st[v][0];
            cout<<' '<<v<<endl;
        }
    }
    for(int i=1;i<n;i++){
        cout<<ans[son[i]]<<endl;
    }
    return 0;
}
