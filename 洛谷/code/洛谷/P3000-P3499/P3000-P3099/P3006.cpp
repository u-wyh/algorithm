// https://www.luogu.com.cn/problem/P3006
// 题意：输入田地数 N、询问数 K，
// 每个非 1 号点 i 的父节点 P_i、初始奶牛数 C_i、单位时间通往 P_i
// 的流量上限 M_i
// 以及 K 个时间询问 T_i。
// 奶牛以 1 号田地为根形成树；
// 每个离散单位时间内，每头牛可停留或沿树边向 1 号点移动任意多条边，
// 但每条边 i->P_i 每单位时间最多通过 M_i
// 头牛（到 1 号点后不再离开）。
// 对每个询问时间 T_i，
// 求在 T_i 单位时间内最多有多少头奶牛能到达 1 号田地。
// 输出共 K 行，
// 第 i 行一个整数表示 T_i 时间内能到达田地 1 的最大奶牛数。
// 数据范围：对于 100% 的数据，1 <= P_i <= N <= 10^5，
// 1 <= C_i, T_i <= 10^9，0 <= M_i <= 10^9
// 1 <= K <= 10^4。
// 算法标签：优先队列、并查集、离线算法
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 1e4+5;

int n,q;

struct QUERY{
    int t,id;
};
QUERY query[MAXM];
int ans[MAXM];

struct node{
    int t,pos;
};
struct compare{
    bool operator()(node a,node b){
        return a.t>b.t;
    }
};
priority_queue<node,vector<node>,compare>heap;

int fa[MAXN];
int f[MAXN];
int val[MAXN];
int pass[MAXN];

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

bool cmp(QUERY a,QUERY b){
    return a.t<b.t;
}

signed main()
{
    n=read(),q=read();
    for(int i=2;i<=n;i++){
        f[i]=read();
        val[i]=read();
        int limit=read();
        pass[f[i]]-=limit;
        pass[i]+=limit;
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=q;i++){
        query[i].t=read();
        query[i].id=i;
    }
    sort(query+1,query+q+1,cmp);
    for(int i=2;i<=n;i++){
        if(pass[i]>0){
            heap.push({val[i]/pass[i],i});
        }
    }
    int lt=1;
    while(!heap.empty()&&lt<=q){
        node u=heap.top();
        heap.pop();
        while(lt<=q&&query[lt].t<=u.t){
            ans[query[lt].id]=val[1]-pass[1]*query[lt].t;
            lt++;
        }
        if(u.pos!=find(u.pos)){
            continue;
        }
        int fx=find(f[u.pos]);
        val[fx]+=val[u.pos];
        pass[fx]+=pass[u.pos];
        fa[u.pos]=fx;
        if(pass[fx]>0){
            heap.push({val[fx]/pass[fx],fx});
        }
    }
    for(int i=1;i<=q;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}