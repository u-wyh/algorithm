// 简单题，二进制分组的方式，C++版
// 有一个n * n的平面区域，初始时没有点，有若干条操作，类型如下
// 操作 1 a b c   : 平面里增加一个点，坐标(a, b)，点权为c
// 操作 2 a b c d : 查询(a, b)为左下角、(c, d)为右上角的区域中，所有点的点权和
// 操作 3         : 终止，以后没有操作了
// 本题要求强制在线，得到操作参数的规则，打开测试链接查看
// 1 <= n <= 5 * 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P4148
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MAXP = 19;
const int INF = 2e18;

int n;

// 点的信息
int x[MAXN];
int y[MAXN];
int v[MAXN];
int arr[MAXN];

int cntkdt;
// 每个组的根节点
int root[MAXP];
int ls[MAXN];
int rs[MAXN];
int sum[MAXN];
int xmin[MAXN];
int xmax[MAXN];
int ymin[MAXN];
int ymax[MAXN];

int compare(int i,int j,int dimension){
    int v1=dimension==0?x[i]:y[i];
    int v2=dimension==0?x[j]:y[j];
    return v1==v2?0:v1<v2?-1:1;
}

struct cmp{
    int dimension;
    bool operator()(int a,int b)const{
        return compare(a,b,dimension)<0;
    }
};

void maintain(int i){
    sum[i]=sum[ls[i]]+sum[rs[i]]+v[i];
    xmin[i]=min(x[i],min(xmin[ls[i]],xmin[rs[i]]));
    xmax[i]=max(x[i],max(xmax[ls[i]],xmax[rs[i]]));
    ymin[i]=min(y[i],min(ymin[ls[i]],ymin[rs[i]]));
    ymax[i]=max(y[i],max(ymax[ls[i]],ymax[rs[i]]));
}

// 将编号范围为l到r的点按照dimension维度排序
int build(int l,int r,int dimension){
    if(l>r){
        return 0;
    }
    int mid=(l+r)>>1;
    // 在区间arr[l ... r]中，参数分别是l mid  r+1
    // 按照 Cmp{dimension} 这个比较规则，把第 mid-l+1 小的元素放到 arr[mid]
    // mid前面的小于它  mid后面的大于它
    nth_element(arr+l,arr+mid,arr+r+1,cmp{dimension});
    int rt=arr[mid];
    ls[rt]=build(l,mid-1,dimension^1);
    rs[rt]=build(mid+1,r,dimension^1);
    maintain(rt);
    return rt;
}

void add(int qx,int qy,int qv){
    cntkdt++;
    x[cntkdt]=qx;
    y[cntkdt]=qy;
    v[cntkdt]=qv;
    arr[cntkdt]=cntkdt;
    // 找到第一个根节点为空的组
    // 因为非空的组都是满的
    int p=0;
    while(root[p]!=0){
        root[p++]=0;
    }
    // 第一个非空的组，将会把前面所有组的值全部收集上来
    // 实际上，他们的编号都是固定的  一定都是最后的几个
    root[p]=build(cntkdt-(1<<p)+1,cntkdt,0);
}

int query(int x1,int y1,int x2,int y2,int i){
    if(i==0){
        return 0;
    }
    if(xmax[i]<x1||xmin[i]>x2||ymax[i]<y1||ymin[i]>y2){
        return 0;
    }
    if(x1<=xmin[i]&&xmax[i]<=x2&&y1<=ymin[i]&&ymax[i]<=y2){
        return sum[i];
    }
    int ans=0;
    if(x1<=x[i]&&x[i]<=x2&&y1<=y[i]&&y[i]<=y2){
        ans+=v[i];
    }
    ans+=query(x1,y1,x2,y2,ls[i]);
    ans+=query(x1,y1,x2,y2,rs[i]);
    return ans;
}

int query(int x1,int y1,int x2,int y2){
    int ans=0;
    for(int p=0;p<MAXP;p++){
        ans+=query(x1,y1,x2,y2,root[p]);
    }
    return ans;
}

signed main()
{
    cin>>n;
    // 0号节点作为空儿子使用
    xmin[0]=ymin[0]=INF;
    xmax[0]=ymax[0]=-INF;
    int op,a,b,c,d,lastans;
    cin>>op;
    lastans=0;
    while(op!=3){
        cin>>a>>b>>c;
        a^=lastans;
        b^=lastans;
        c^=lastans;
        if(op==1){
            add(a,b,c);
        }
        else{
            cin>>d;
            d^=lastans;
            lastans=query(a,b,c,d);
            cout<<lastans<<endl;
        }
        cin>>op;
    }
    return 0;
}