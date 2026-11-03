// https://www.luogu.com.cn/problem/P4357
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int INF = 2e9;

int n,k;

int x[MAXN];
int y[MAXN];
int arr[MAXN];

int root;
int ls[MAXN];
int rs[MAXN];
int xmin[MAXN];
int xmax[MAXN];
int ymin[MAXN];
int ymax[MAXN];

priority_queue<int,vector<int>,greater<int>> heap;

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

void updateAns(int qx,int qy,int i){
    if(i==0){
        return;
    }

    int d=dist(qx,qy,x[i],y[i]);

    // 全局维护前2K大的距离
    if(heap.size()<2*k){
        heap.push(d);
    }
    else if(d>heap.top()){
        heap.pop();
        heap.push(d);
    }

    int gl=guess(qx,qy,ls[i]);
    int gr=guess(qx,qy,rs[i]);

    if(gl>gr){
        if(heap.size()<2*k || gl>heap.top()){
            updateAns(qx,qy,ls[i]);
        }
        if(heap.size()<2*k || gr>heap.top()){
            updateAns(qx,qy,rs[i]);
        }
    }
    else{
        if(heap.size()<2*k || gr>heap.top()){
            updateAns(qx,qy,rs[i]);
        }
        if(heap.size()<2*k || gl>heap.top()){
            updateAns(qx,qy,ls[i]);
        }
    }
}

signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
        arr[i]=i;
    }
    xmin[0]=ymin[0]=INF;
    xmax[0]=ymax[0]=-INF;
    root=build(1,n,0);

    for(int i=1;i<=n;i++){
        updateAns(x[i],y[i],root);
    }
    cout<<heap.top()<<endl;
    return 0;
}