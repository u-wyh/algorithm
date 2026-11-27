// https://www.luogu.com.cn/problem/P3755
// 题意：输入基站数 n 和查询数 m，
// 接着 n 个互不重合基站的坐标与功率 (x_i, y_i, p_i)
// 再输入 m 个矩形查询区域 (x_1, y_1, x_2, y_2)。
// 对每个边平行于坐标轴的闭矩形区域（含边界），
// 计算区域内所有基站的功率总和（无基站则输出 0）。
// 输出 m 行，对应每次查询的结果。
// 数据范围：1 <= n, m <= 10^5，
// -2^31 <= x_i, y_i, p_i, x_1, y_1, x_2,
// y_2 < 2^31
// x_1 <= x_2，y_1 <= y_2。
// 算法标签：CDQ分治、二维偏序、容斥原理
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 1e5+5;

int n,m;

struct node{
    int x,y,v,id;
}nums[MAXN];
int cnt;

node tmp[MAXN];

long long ans[MAXM];

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
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.id<b.id;//让添加操作类型在前面
}

void merge(int l,int mid,int r){
    int p1,p2;
    long long sum=0;
    for(p1=l-1,p2=mid+1;p2<=r;p2++){
        while(p1+1<=mid&&nums[p1+1].y<=nums[p2].y){
            p1++;
            if(nums[p1].id==0){
                sum+=nums[p1].v;
            }
        }
        ans[nums[p2].id]+=nums[p2].v*sum;
    }

    p1=l,p2=mid+1;
    int i=l;
    while(p1<=mid&&p2<=r){
        tmp[i++]=nums[p1].y<nums[p2].y?nums[p1++]:nums[p2++];
    }
    while(p1<=mid){
        tmp[i++]=nums[p1++];
    }
    while(p2<=r){
        tmp[i++]=nums[p2++];
    }
    for(int i=l;i<=r;i++){
        nums[i]=tmp[i];
    }
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    merge(l,mid,r);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[++cnt].x=read();
        nums[cnt].y=read();
        nums[cnt].v=read();
    }
    for(int i=1;i<=m;i++){
        int a,b,c,d;
        a=read(),b=read(),c=read(),d=read();
        nums[++cnt]={c,d,1,i};
        nums[++cnt]={a-1,b-1,1,i};
        nums[++cnt]={a-1,d,-1,i};
        nums[++cnt]={c,b-1,-1,i};
    }
    sort(nums+1,nums+cnt+1,cmp);
    cdq(1,cnt);
    for(int i=1;i<=m;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}