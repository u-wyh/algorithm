// 平面最近点对，C++版
// 一共n个点，每个点给定坐标(x, y)，输出最近两个点的距离，保留四位小数
// 2 <= n <= 2 * 10^5
// 0 <= x、y <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P1429
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int INF = 3e18;

int n;

// 点的坐标，arr数组是用于方便后面查询一些点的中间位置，仅仅是辅助作用
int x[MAXN];
int y[MAXN];
int arr[MAXN];

// KD tree相关
// 分别表示左右儿子节点，以及这个节点覆盖的范围最值
int root;
int ls[MAXN];
int rs[MAXN];
int xmin[MAXN];
int xmax[MAXN];
int ymin[MAXN];
int ymax[MAXN];

int ans;

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

// 求出两点之间的距离平方
int dist(int qi,int i){
    int dx=x[qi]-x[i];
    int dy=y[qi]-y[i];
    return dx*dx+dy*dy;
}

// 针对qi这个点，对于KD树上的i号节点管辖的点  估计一下最近距离
int guess(int qi,int i){
    if(i==0){
        return INF;
    }
    int qx=x[qi];
    int qy=y[qi];
    int dx = qx < xmin[i] ? (xmin[i] - qx) : (qx > xmax[i] ? (qx - xmax[i]) : 0);
    int dy = qy < ymin[i] ? (ymin[i] - qy) : (qy > ymax[i] ? (qy - ymax[i]) : 0);
    return dx * dx + dy * dy;
}

void updateAns(int qi,int i){
    if(i==0){
        return ;
    }
    if(qi!=i){
        ans=min(ans,dist(qi,i));
    }
    int gl=guess(qi,ls[i]);
    int gr=guess(qi,rs[i]);
    // 先走可能比较近的  尽量优化ans方便剪枝
    if(gl<gr){
        // 如果最近距离都无法更新的话，那么完全可以剪枝
        if(gl<ans){
            updateAns(qi,ls[i]);
        }
        if(gr<ans){
            updateAns(qi,rs[i]);
        }
    }
    else{
        if(gr<ans){
            updateAns(qi,rs[i]);
        }
        if(gl<ans){
            updateAns(qi,ls[i]);
        }
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
        arr[i]=i;
    }
    xmin[0]=ymin[0]=INF;
    xmax[0]=ymax[0]=-INF;
    root=build(1,n,0);
    // 这里是提前赋值，方便剪枝
    // 完全可以初始化为一个极大值
    ans=dist(1,2);
    for(int i=1;i<=n;i++){
        // 将每个点从根节点开始向下遍历，尝试更新答案
        updateAns(i,root);
        if(ans==0){
            break;
        }
    }
    printf("%.4f\n", sqrt((double) ans));
    return 0;
}