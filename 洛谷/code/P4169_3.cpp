#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 6e5+5;
const int MAXP = 21;
const int INF = 2e18;

int n,m;
int x[MAXN];
int y[MAXN];
int arr[MAXN];

int cntkdt;
// 每个组的根节点
int root[MAXP];
int ls[MAXN];
int rs[MAXN];
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

int ans;

int guess(int qx,int qy,int i){
    if (i == 0) {
        return INF;
    }
    int ans = qx < xmin[i] ? xmin[i] - qx : qx > xmax[i] ? qx - xmax[i] : 0;
    ans += qy < ymin[i] ? ymin[i] - qy : qy > ymax[i] ? qy - ymax[i] : 0;
    return ans;
}

void updateAns(int qx,int qy,int i){
    if(i==0){
        return ;
    }
    ans=min(ans,abs(qx-x[i])+abs(qy-y[i]));
    int gl=guess(qx,qy,ls[i]);
    int gr=guess(qx,qy,rs[i]);
    if(gl<gr){
        if(gl<ans){
            updateAns(qx,qy,ls[i]);
        }
        if(gr<ans){
            updateAns(qx,qy,rs[i]);
        }
    }
    else{
        if(gr<ans){
            updateAns(qx,qy,rs[i]);
        }
        if(gl<ans){
            updateAns(qx,qy,ls[i]);
        }
    }
}

void updateAns(int qx,int qy){
    for(int p=0;p<MAXP;p++){
        updateAns(qx,qy,root[p]);
    }
}

signed main()
{
    cin>>n>>m;
    xmin[0]=ymin[0]=INF;
    xmax[0]=ymax[0]=-INF;
    for(int i=1;i<=n;i++){
        int qx,qy;
        cin>>qx>>qy;
        add(qx,qy);
    }
    for(int i=1,op,qx,qy;i<=m;i++){
        cin>>op>>qx>>qy;
        if(op==1){
            add(qx,qy);
        }
        else{
            ans=INF;
            updateAns(qx,qy);
            cout<<ans<<endl;
        }
    }
    return 0;
}