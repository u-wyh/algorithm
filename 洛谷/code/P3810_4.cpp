// https://www.luogu.com.cn/problem/P3810
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXP = 18;
const int INF = 1e9;

int n,k;

struct node{
    int a,x,y;
};
bool acmp(node &a,node &b){
    return a.a<b.a;
}

node nums[MAXN];

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
int sz[MAXN];
int xmin[MAXN];
int xmax[MAXN];
int ymin[MAXN];
int ymax[MAXN];

int ans[MAXN];

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
    sz[i]=sz[ls[i]]+sz[rs[i]]+1;
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

void add(int qx,int qy){
    cntkdt++;
    x[cntkdt]=qx;
    y[cntkdt]=qy;
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

int query(int qx,int qy,int i){
    if(i==0){
        return 0;
    }
    if(xmin[i]>qx||ymin[i]>qy){
        return 0;
    }
    if(xmax[i]<=qx&&ymax[i]<=qy){
        return sz[i];
    }
    int ans=0;
    if(x[i]<=qx&&y[i]<=qy){
        ans++;
    }
    ans+=query(qx,qy,ls[i]);
    ans+=query(qx,qy,rs[i]);
    return ans;
}

int query(int qx,int qy){
    int ans=0;
    for(int i=0;i<MAXP;i++){
        ans+=query(qx,qy,root[i]);
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>nums[i].a>>nums[i].x>>nums[i].y;
    }
    sort(nums+1,nums+n+1,acmp);

    xmin[0]=ymin[0]=INF;
    xmax[0]=ymax[0]=-INF;

    for(int l=1,r=1;l<=n;l=++r){
        while(r+1<=n&&nums[r+1].a==nums[l].a){
            r++;
        }
        for(int i=l;i<=r;i++){
            add(nums[i].x,nums[i].y);
        }
        for(int i=l;i<=r;i++){
            int fi=query(nums[i].x,nums[i].y)-1;
            ans[fi]++;
        }
    }
    for(int d=0;d<n;d++){
        cout<<ans[d]<<endl;
    }
    return 0;
}