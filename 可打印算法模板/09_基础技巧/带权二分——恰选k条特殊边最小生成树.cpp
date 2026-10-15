// 用途：求恰好含 need 条白边的最小生成树。
// 时间：O(m log m log C)，C 是罚值搜索范围（本题 211 个整数）。
// 空间：O(n+m)。
// 注意：原题保证图连通且有解，边权 1..100；col=0 是白边，点编号从 0 开始。
// 例题：https://www.luogu.com.cn/problem/P2619
// 题意：在黑白边组成的图中，求恰选 need 条白边的最小生成树权值。
// 思路：白边统一加罚值，二分“仍能选够白边”的最大罚值，再扣除罚值×need。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 1e5+5;

int n,m,need;
int mid;
struct node{
    int u,v,w,col;
};

node nums[MAXM];

int fa[MAXN];
int siz[MAXN];

// 快速读整数；这里保留负号处理，便于复用。
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

// Kruskal 按修改后边权排序：白边 w+mid，黑边 w。
// 修改后边权相等时白边优先，使当前最小生成树的白边数尽量大。
bool cmp(const node& a,const node& b){
    if((a.w+(1-a.col)*mid)!=(b.w+(1-b.col)*mid)) return (a.w+(1-a.col)*mid)<(b.w+(1-b.col)*mid);
    return a.col<b.col;
}

// 并查集找连通块代表元；路径压缩避免反复沿父指针上跳。
int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

// 每次 Kruskal 都要从 n 个单点连通块重新开始。
void initDsu(){
    for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;
}

// 不在同一块时合并；按大小合并使递归 find 的深度保持很浅。
bool merge(int x,int y){
    x=find(x),y=find(y);
    if(x==y) return false;
    if(siz[x]<siz[y]) swap(x,y);
    fa[y]=x;
    siz[x]+=siz[y];
    return true;
}

// 返回当前罚值下，最小生成树最多能否选出 need 条白边。
// 罚值越大，白边越不易入树，因此这个判断具有二分所需的单调性。
bool check(){
    int cnt=0;
    sort(nums+1,nums+m+1,cmp);
    initDsu();
    int k=0;
    for(int i=1;i<=m;i++){
        if(merge(nums[i].u,nums[i].v)){ // 只选连接不同连通块的边，防止成环。
            if(nums[i].col==0){
                cnt++;
            }
            k++;
            if(k==n-1){
                break;
            }
        }
    }
    return cnt>=need;
}

int main()
{
    n=read(),m=read(),need=read();
    for(int i=1;i<=m;i++){
        nums[i].u=read()+1,nums[i].v=read()+1,nums[i].w=read(),nums[i].col=read();
    }
    // 边权仅 1..100，±105 已足以把白边放到黑边前/后；题目保证可行。
    int l=-105,r=105,ans=-105;
    while(l<=r){
        mid=l+(r-l)/2;
        if(check()){ // 能选够白边，就继续加大白边罚值。
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    // 在临界罚值下重新求修改后最小生成树权值。
    mid=ans;
    long long all=0;
    sort(nums+1,nums+m+1,cmp);
    initDsu();
    for(int i=1;i<=m;i++){
        if(merge(nums[i].u,nums[i].v)){
            all+=((1-nums[i].col)*mid+nums[i].w);
        }
    }
    // 每条目标白边都被加过 mid，减去 mid*need 还原原始最优权值。
    all-=1LL*mid*need;
    printf("%lld\n",all);
    return 0;
}
