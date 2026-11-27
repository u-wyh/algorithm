// https://www.luogu.com.cn/problem/P2323
// 题意：n 个点 m-1 条备选边，
// 每条边修一级花费 c_1、修二级花费 c_2（c_2 <= c_1）。
// 选 n-1 条边建生成树，要求至少有 k 条一级公路，使最大单边花费尽量小。
// 输出最小的最大花费及所选边的编号与等级（Special Judge）。
// 数据范围：1 <= n <= 10000，
// 0 <= k <= n-1，n <= m <= 20000，
// 1 <= c_2 <= c_1 <= 30000。
// 算法标签：Kruskal、贪心、并查集
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e4+5;
const int MAXM = 2e4+5;

int n,k,m;
struct node{
    int u,v,val1,val2,id;
}nums[MAXM];
int fa[MAXN];
int choose[MAXM];

bool cmp1(node a,node b){
    return a.val1<b.val1;
}

bool cmp2(node a,node b){
    return a.val2<b.val2;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

bool un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        return true;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>k>>m;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<m;i++){
        cin>>nums[i].u>>nums[i].v>>nums[i].val1>>nums[i].val2;
        nums[i].id=i;
    }
    sort(nums+1,nums+m,cmp1);
    int ans=0;
    int cnt=0;
    for(int i=1;i<m;i++){
        if(cnt==k){
            break;
        }
        if(un(nums[i].u,nums[i].v)){
            cnt++;
            choose[nums[i].id]=1;
            ans=max(ans,nums[i].val1);
        }
    }
    sort(nums+1,nums+m,cmp2);
    for(int i=1;i<m;i++){
        if(cnt==n-1){
            break;
        }
        if(un(nums[i].u,nums[i].v)){
            cnt++;
            choose[nums[i].id]=2;
            ans=max(ans,nums[i].val2);
        }
    }
    cout<<ans<<endl;
    for(int i=1;i<m;i++){
        if(choose[i]){
            cout<<i<<' '<<choose[i]<<endl;
        }
    }
    return 0;
}
