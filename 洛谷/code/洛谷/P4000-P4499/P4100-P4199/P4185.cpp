// https://www.luogu.com.cn/problem/P4185
// 题意：给一棵 N 个点的带权树，两点间的相关度定义为路径上最小边权；
// 有 Q 次询问，每次给 k_i 和 v_i，
// 求树上有多少个其他点与 v_i 的相关度大于等于 k_i。
// 数据范围：1 <= N, Q <= 1e5，
// 1 <= r_i, k_i <= 1e9，
// 1 <= p_i, q_i, v_i <= N。
// 算法标签：并查集、离线处理
#include<bits/stdc++.h>
using namespace std;

int n,m;
int fa[100005];
int sz[100005];
struct question{
    int k,v,i;
    int ans;
}nums[100005];
struct node{
    int u,v,w;
}edge[200005];

bool cmp(node a,node b){
    return a.w>b.w;
}

bool compare(question a,question b){
    return a.k>b.k;
}

bool comp(question a,question b){
    return a.i<b.i;
}

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y)
{
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx] = fy;
        sz[fy]+=sz[fx];
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
    for(int i=1;i<n;i++){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
    }
    sort(edge+1,edge+n,cmp);
    for(int i=1;i<=m;i++){
        cin>>nums[i].k>>nums[i].v;
        nums[i].i=i;
    }
    int k=1;
    sort(nums+1,nums+m+1,compare);
    for(int i=1;i<=m;i++){
        while(k<n&&edge[k].w>=nums[i].k){
            un(edge[k].u,edge[k].v);
            k++;
        }
        nums[i].ans=sz[find(nums[i].v)];
    }
    sort(nums+1,nums+m+1,comp);
    for(int i=1;i<=m;i++){
        cout<<nums[i].ans-1<<endl;
    }
    return 0;
}
