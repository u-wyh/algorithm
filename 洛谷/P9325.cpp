#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 3e5+5;
const int LIMIT = 17;

int n,m,q;
struct node{
    int u,v,w;
}nums[MAXM];

int deep[MAXN];
int fa[MAXN];
bool vis[MAXN];

int st[MAXN][LIMIT+1];
int val[MAXN][LIMIT+1];

int cnt=1;
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int weight[MAXN<<1];

inline void addedge(int u,int v,int w){
    Next[cnt]=head[u];
    to[cnt]=v;
    weight[cnt]=w;
    head[u]=cnt++;
}

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
    return a.w>b.w;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

void dfs(int u,int f){
    vis[u]=true;
    st[u][0]=f;
    deep[u]=deep[f]+1;
    for(int i=1;i<=LIMIT;i++){
        if(st[u][i-1]>0){
            st[u][i]=st[st[u][i-1]][i-1];
            val[u][i]=min(val[u][i-1],val[st[u][i-1]][i-1]);
        }
    }
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        int w=weight[i];
        if(v!=f){
            val[v][0]=w;
            dfs(v,u);
        }
    }
}

int lca(int a,int b){
    int ans=INT_MAX;
    if (deep[a] < deep[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    //确定大小关系  将a永远变为深度更深的点(与b相比)  这样仅仅是为了方便操作
    for (int p = LIMIT ;p >= 0; p--) {
        if (deep[st[a][p]] >= deep[b]) {
            ans=min(ans,val[a][p]);
            a = st[a][p];
            //注意这两行代码  不要换位置 不然a发生改变  得到的ans不是我们想要的
        }
    }
    //首先将两者变为同一高度
    if (a == b) {
        return ans;
    }
    //如果相同说明就是祖先关系  是祖先关系直接返回ans就可以了
    //如果不理解的话  仔细想想val这个倍增表的含义
    for (int p = LIMIT; p >= 0; p--) {
        if (st[a][p] != st[b][p]) {
            ans=min(ans,min(val[a][p],val[b][p]));
            a = st[a][p];
            b = st[b][p];
        }
        //判断跳完后是否符合规则
    }
    //跑到了这里  那么fa[a][0]和fa[b][0]是一样的  就是他们的祖先
    //不会的话建议学一下lca
    ans = min(ans,min(val[a][0],val[b][0]));
    return ans;
}

int main()
{
    n=read(),m=read(),q=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        nums[i].u=read(),nums[i].v=read(),nums[i].w=read();
    }
    sort(nums+1,nums+m+1,cmp);
    for(int i=1;i<=m;i++){
        //cout<<nums[i].w<<endl;
        int u=find(nums[i].u);
        int v=find(nums[i].v);
        if(u!=v){
            un(nums[i].u,nums[i].v);
            addedge(nums[i].u,nums[i].v,nums[i].w);
            addedge(nums[i].v,nums[i].u,nums[i].w);
        }
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs(i,0);
        }
    }
    for(int i=1;i<=q;i++){
        int u,v;
        u=read(),v=read();
        if(find(u)!=find(v)){
            cout<<-1<<endl;
        }
        else{
            cout<<lca(u,v)<<endl;
        }
    }
    return 0;
}
