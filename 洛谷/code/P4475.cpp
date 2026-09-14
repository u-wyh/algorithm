// 巧克力王国，C++版
// 一共n个点，每个点有坐标(x, y)，还有点权v
// 一共m条查询，格式 a b c，含义如下
// 满足 a * x + b * y < c 的所有点，打印点权累加和
// 1 <= n、m <= 5 * 10^4
// -10^9 <= a、b、x、y <= +10^9
// 测试链接 : https://www.luogu.com.cn/problem/P4475
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;
const int INF = 2e18;

int n,m;

int val[MAXN];
int x[MAXN];
int y[MAXN];
int arr[MAXN];

int root;
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

// 更新、维持i节点的信息
void maintain(int i){
    sum[i]=val[i]+sum[ls[i]]+sum[rs[i]];
    xmin[i]=min(x[i],min(xmin[ls[i]],xmin[rs[i]]));
    xmax[i]=max(x[i],max(xmax[ls[i]],xmax[rs[i]]));
    ymin[i]=min(y[i],min(ymin[ls[i]],ymin[rs[i]]));
    ymax[i]=max(y[i],max(ymax[ls[i]],ymax[rs[i]]));
}

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

int query(int a,int b,int c,int i){
    if(i==0){
        return 0;
    }
    int ax1=xmin[i]*a;
    int ax2=xmax[i]*a;
    int by1=ymin[i]*b;
    int by2=ymax[i]*b;
    int minv=min(ax1,ax2)+min(by1,by2);
    int maxv=max(ax1,ax2)+max(by1,by2);
    if(minv>=c){
        return 0;
    }
    if(maxv<c){
        return sum[i];
    }

    int ans=0;
    if(a*x[i]+b*y[i]<c){
        ans+=val[i];
    }
    ans+=query(a,b,c,ls[i]);
    ans+=query(a,b,c,rs[i]);
    return ans;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i]>>val[i];
        arr[i]=i;
    }
    xmin[0]=ymin[0]=INF;
    xmax[0]=ymax[0]=-INF;
    root=build(1,n,0);
    int a,b,c;
    for(int i=1;i<=m;i++){
        cin>>a>>b>>c;
        cout<<query(a,b,c,root)<<endl;
    }
    return 0;
}