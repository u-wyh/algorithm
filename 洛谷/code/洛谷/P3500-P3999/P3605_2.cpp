// https://www.luogu.com.cn/problem/P3605
// 题意：输入奶牛数量 n，每头奶牛互不相同的能力指数 p_1..p_n，
// 以及 2..n 号奶牛在公司树（1 号为根）中的父节点编号。
// 若奶牛 i 是奶牛 j 的祖先，则 j 是 i 的下属；
// 对每头奶牛 i 统计其下属中满足 p_j > p_i 的人数。
// 输出 n 行，第 i 行表示第 i 头奶牛满足条件的下属数量。
// 数据范围：1 <= n <= 10^5，1 <= p_i <= 10^9，
// 且所有 p_i 互不相同。
//P3605
// 算法标签：树状数组、DFS序、排序
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
struct node{
    int num,id,sub;
}arr[MAXN];
int dfncnt=0;
int dfn[MAXN];
int sz[MAXN];
int head[MAXN];
int Next[MAXN<<1];
int to[MAXN<<1];
int cnt=1;
int tree[MAXN];
int ans[MAXN];

bool cmp(node a,node b){
    return a.num>b.num;
}

void add(int i,int v){
    while(i<=n){
        tree[i]+=v;
        i+=i&-i;
    }
}

int sum(int i){
    int ans=0;
    while(i){
        ans+=tree[i];
        i-=i&-i;
    }
    return ans;
}

void addedge(int u,int v){
    Next[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

void dfs(int u){
    dfn[u]=++dfncnt;
    sz[u]=1;
    for(int i=head[u];i;i=Next[i]){
        int v=to[i];
        if(dfn[v])
            continue;
        dfs(v);
        sz[u]+=sz[v];
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i].num;
        arr[i].id=i;
    }
    for(int i=2;i<=n;i++){
        int u;
        cin>>u;
        addedge(u,i);
    }
    dfs(1);
    sort(arr+1,arr+n+1,cmp);//将能力从高到低排序
    //树状数组查询自己的下级中已经有多少能力比自己强的填了上去
    for(int i=1;i<=n;i++){
        arr[i].sub=dfn[arr[i].id];//改为dfn排名
        ans[arr[i].id]=sum(arr[i].sub+sz[arr[i].id]-1)-sum(arr[i].sub);
        add(arr[i].sub,1);
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
