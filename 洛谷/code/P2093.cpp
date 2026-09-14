// 查询第k远的点，C++版
// 一共n个点，编号1~n，每个点给定坐标(x, y)
// 一共m条查询，格式 qx qy qk，查询距离(qx, qy)第qk远的点，打印该点的编号
// 如果多个点到(qx, qy)的距离相同，那么编号较小的点认为距离更远
// 1 <= n <= 10^5
// 1 <= m <= 10^4
// 1 <= qk <= 20
// -10^9 <= 坐标值 <= +10^9
// 测试链接 : https://www.luogu.com.cn/problem/P2093
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int INF = 2e18;

int n,m;

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

struct node{
    int dist,id;
};
struct comparenode{
    // 这个堆 距离dist维持小根堆 通过数量表示需要最远的k个
    // id维持大根堆 根据题目需要
    bool operator()(const node &a,const node &b){
        if(a.dist!=b.dist){
            return a.dist>b.dist;
        }
        return a.id<b.id;
    }
};
priority_queue<node,vector<node>,comparenode>heap;

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

int dist(int x1,int y1,int x2,int y2){
    int dx=x1-x2;
    int dy=y1-y2;
    return dx*dx+dy*dy;
}

int guess(int qx,int qy,int i){
    if(i==0){
        return 0;
    }
    int dx = max(abs(qx - xmin[i]), abs(qx - xmax[i]));
    int dy = max(abs(qy - ymin[i]), abs(qy - ymax[i]));
    return dx * dx + dy * dy;
}

void updateAns(int qx,int qy,int qk,int i){
    if(i==0){
        return ;
    }
    heap.push({dist(qx,qy,x[i],y[i]),i});
    if(heap.size()>qk){
        heap.pop();
    }
    int gl=guess(qx,qy,ls[i]);
    int gr=guess(qx,qy,rs[i]);
    if(gl>gr){
        if (heap.size() < qk || gl >= heap.top().dist) {
            updateAns(qx, qy, qk, ls[i]);
        }
        if (heap.size() < qk || gr >= heap.top().dist) {
            updateAns(qx, qy, qk, rs[i]);
        }
    }
    else{
        if (heap.size() < qk || gr >= heap.top().dist) {
            updateAns(qx, qy, qk, rs[i]);
        }
        if (heap.size() < qk || gl >= heap.top().dist) {
            updateAns(qx, qy, qk, ls[i]);
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

    cin>>m;
    for(int i=1,qx,qy,qk;i<=m;i++){
        cin>>qx>>qy>>qk;
        while(!heap.empty()){
            heap.pop();
        }
        updateAns(qx,qy,qk,root);
        cout<<heap.top().id<<endl;
    }
    return 0;
}