#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;
const int MAXK = 5e5+5;
const int INF = 2e18;

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

int ans[MAXK];

priority_queue<int>heap;

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

int dist(int j,int i){
    return abs(x[i]-x[j])+abs(y[i]-y[j]);
}

int guess(int p,int i){
    if(i==0){
        return INF;
    }
    int dx=0;
    int dy=0;
    if(x[p]<xmin[i]){
        dx=xmin[i]-x[p];
    }
    else if(x[p]>xmax[i]){
        dx=x[p]-xmax[i];
    }

    if(y[p]<ymin[i]){
        dy=ymin[i]-y[p];
    }
    else if(y[p]>ymax[i]){
        dy=y[p]-ymax[i];
    }
    return dx+dy;
}

void updateAns(int p,int i){
    if(i==0){
        return ;
    }
    if(i!=p){
        int d=dist(p,i);
        heap.push(d);
        if(heap.size()>2*k){
            heap.pop();
        }
    }

    int gl=guess(p,ls[i]);
    int gr=guess(p,rs[i]);
    if(gl<gr){
        if(heap.size()<2*k || gl<heap.top()){
            updateAns(p,ls[i]);
        }

        if(heap.size()<2*k || gr<heap.top()){
            updateAns(p,rs[i]);
        }
    }
    else{
        if(heap.size()<2*k || gr<heap.top()){
            updateAns(p,rs[i]);
        }

        if(heap.size()<2*k || gl<heap.top()){
            updateAns(p,ls[i]);
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
        updateAns(i,root);
    }
    for(int i=2*k;i>=1;i--){
        ans[i]=heap.top();
        heap.pop();
    }
    for(int i=1;i<=2*k;i+=2){
        cout<<ans[i]<<endl;
    }
    return 0;
}