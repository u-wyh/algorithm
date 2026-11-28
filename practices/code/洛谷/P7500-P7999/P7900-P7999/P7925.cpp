// https://www.luogu.com.cn/problem/P7925
// 题意：给定一棵 n 个点、1 号点为根的有根树，
// 初始在根结点 1 且口袋中有 s 个苹果。
// 每个结点有权重 a_i：首次访问某点时，
// 若 a_i > 0 则获得 a_i 个苹果；
// 若 a_i < 0 则需给出 |a_i|
// 个苹果（若当前口袋苹果不足 |a_i| 则不能走向该结点）；
// 若 a_i = 0 无操作；
// 重复经过同一结点不再触发摘/给苹果（根结点首次也需执行）。
// 沿树边任意移动（可回头），求最终能拥有的最多苹果数。
// 第一行输入 n, s，
// 第二行 n-1 个整数 p_2..p_n（第 i 个数为结点 i+1 的父亲），
// 第三行 n 个整数 a_1..a_n。
// 输出一行一个整数。
// 数据范围：1 <= n <= 6000，
// 1 <= p_i < i（指结点父编号小于子编号），|a_i| <= 10^9，
// 0 <= s <= 10^9。
// 难度评分：1700（洛谷分级换算）
// 算法标签：贪心、深度优先搜索、优先队列
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 6005;
const int INF = 1e18;

int n,m;
int val[MAXN];
int need[MAXN];//表示来到这个节点为首的子树上 最低有多少个苹果就可以赚钱

int cnt=1;
int head[MAXN];
int nxt[MAXN];
int to[MAXN];

struct node{
    int need,id;
};
struct cmp{
    bool operator()(node a,node b){
        return a.need>b.need;
    }
};
priority_queue<node,vector<node>,cmp>q;

void addedge(int u,int v){
    nxt[cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt++;
}

inline void clear(){
    while(!q.empty()){
        q.pop();
    }
}

inline void dfs(int u){
    clear();
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        dfs(v);
    }
    if(val[u]>=0){
        //如果这个位置是苹果  那么肯定直接就是赚钱的
        need[u]=0;
        return ;
    }
    clear();
    for(int i=head[u];i;i=nxt[i]){
        int v=to[i];
        q.push({need[v],v});//所有子节点入队
    }
    need[u]-=val[u];//这是目前的最低花费
    bool flag=false;
    int tot=0;//这是目前拥有的苹果数量
    while(!q.empty()){
        if(tot-need[u]>=0){
            //表示苹果已经比需要的多了 那么就是赚了
            flag=true;
            break;
        }
        node x=q.top();
        q.pop();
        if(tot<need[x.id]){
            //表示现在有的苹果数量无法进入这个子树赚钱
            need[u]+=need[x.id]-tot;//那么至少要进入这个子树赚钱  因为这已经是最容易的了
            tot=need[x.id];//将拥有的苹果数量变为此时的要求
        }
        tot+=val[x.id];
        for(int i=head[x.id];i;i=nxt[i]){
            int v=to[i];
            q.push({need[v],v});
        }
    }
    if(tot-need[u]>=0){
        flag=true;
    }
    if(!flag){
        need[u]=INF;
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=2;i<=n;i++){
        int u;
        cin>>u;
        addedge(u,i);
    }
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    dfs(1);
    clear();
    q.push({need[1],1});
    int ans=m;
    while(!q.empty()){
        node x=q.top();
        q.pop();
        if(ans<need[x.id]){
            break;
        }
        ans+=val[x.id];
        for(int i=head[x.id];i;i=nxt[i]){
            int v=to[i];
            q.push({need[v],v});
        }
    }
    cout<<ans<<endl;
    return 0;
}