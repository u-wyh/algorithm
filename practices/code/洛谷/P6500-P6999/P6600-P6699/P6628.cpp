// https://www.luogu.com.cn/problem/P6628
// 题意：n 个顶点的完全无向图，i 与 j 间边权为 |i-j|，
// 给定 m 条必经道路。
// n 个朋友从 s 出发，
// 第 i 个朋友须经过所有 m 条必经道路各至少一次并最终停在 i，
// 求每个朋友的最小总时间。
// 数据范围：n <= 2500，
// 1 <= s <= n，m <= n(n-1)/2，
// 1 <= u, v <= n 且 u != v（无重边）。
// 难度评分：2900（洛谷分级换算）
// 算法标签：欧拉路径、最小生成树、并查集
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2505;

int n,m,s;
long long sum=0;
int degree[MAXN];
int fa[MAXN];
int belong[MAXN];

struct node{
    int u,v,w;
};
int cnt;
node nums[MAXN];

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

int find(int x){
    return fa[x]==x?x:fa[x]=find(fa[x]);
}

long long compute(int s,int t){
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    degree[s]++,degree[t]++;
    long long ans=sum;
    fa[find(s)]=find(t);
    int pre=0;
    for(int i=1;i<=n;i++){
        if(degree[i]&1){
            if(pre){
                ans+=i-pre;
                for(int j=pre;j<i;j++){
                    fa[find(belong[j])]=find(belong[i]);
                }
                pre=0;
            }
            else{
                pre=i;
            }
        }
    }
    cnt=0;
    pre=0;
    for(int i=1;i<=n;i++){
        if(degree[i]){
            if(pre&&find(belong[i])!=find(belong[pre])){
                nums[++cnt]={belong[i],belong[pre],i-pre};
            }
            pre=i;
        }
    }
    sort(nums+1,nums+cnt+1,cmp);
    for(int i=1;i<=cnt;i++){
        if(find(nums[i].u)!=find(nums[i].v)){
            fa[find(nums[i].u)]=find(nums[i].v);
            ans+=nums[i].w*2;
        }
    }
    degree[s]--,degree[t]--;
    return ans;
}

int main()
{
    n=read(),m=read(),s=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        u=read(),v=read();
        degree[u]++,degree[v]++;
        sum+=abs(u-v);
        fa[find(u)]=find(v);
    }
    for(int i=1;i<=n;i++){
        belong[i]=find(i);
    }
    for(int t=1;t<=n;t++){
        cout<<compute(s,t)<<' ';
    }
    return 0;
}