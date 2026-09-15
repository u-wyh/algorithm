#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 2e5+5;
const int INF = 1e9+5;

int n,m;

int lt[MAXN];
int rt[MAXN];

int x[MAXM];
int y[MAXM];

int root;
int ls[MAXM];
int rs[MAXM];

int xmin[MAXM];
int xmax[MAXM];
int ymin[MAXM];
int ymax[MAXM];

int arr[MAXM];
int cur[MAXM];
int ans[MAXM];

struct tag{
    int first,last,maxx;
    bool clear;
};
tag lazy[MAXM];

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

tag merge(tag a,tag b){
    if(!a.clear){
        if(!b.clear){
            return {a.first+b.first,0,0,false};
        }
        return {a.first+b.first,b.last,b.maxx,true};
    }
    else if(!b.clear){
        return {a.first,a.last+b.first,max(a.maxx,a.last+b.first),true};
    }
    else{
        return {a.first,b.last,max(a.maxx,max(b.maxx,a.last+b.first)),true};
    }
}

void taglazy(int i,tag t){
    if(i==0){
        return ;
    }
    if(!t.clear){
        ans[i]=max(ans[i],cur[i]+t.first);
        cur[i]+=t.first;
    }
    else{
        ans[i]=max(ans[i],cur[i]+t.first);
        ans[i]=max(ans[i],t.maxx);
        cur[i]=t.last;
    }
    lazy[i]=merge(lazy[i],t);
}

void down(int i){
    if(!lazy[i].clear&&lazy[i].first==0){
        return ;
    }
    taglazy(ls[i],lazy[i]);
    taglazy(rs[i],lazy[i]);
    lazy[i]={0,0,0,false};
}

tag addtag={1,0,0,false};
tag cleartag={0,0,0,true};

void modify(int ql,int qr,int i){
    if(i==0){
        return ;
    }
    if(xmax[i]<=qr&&ql<=ymin[i]){
        taglazy(i,addtag);
        return ;
    }
    if(xmin[i]>qr||ymax[i]<ql){
        taglazy(i,cleartag);
        return ;
    }
    down(i);
    if(x[i]<=qr&&y[i]>=ql){
        cur[i]++;
        ans[i]=max(ans[i],cur[i]);
    }
    else{
        cur[i]=0;
    }
    modify(ql,qr,ls[i]);
    modify(ql,qr,rs[i]);
}

void dfs(int u){
    if(u==0){
        return ;
    }
    down(u);
    dfs(ls[u]);
    dfs(rs[u]);
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>lt[i]>>rt[i];
    }
    xmin[0]=ymin[0]=INF;
    xmax[0]=ymax[0]=-INF;
    for(int i=1;i<=m;i++){
        cin>>x[i]>>y[i];
        arr[i]=i;
        xmin[i]=xmax[i]=x[i];
        ymin[i]=ymax[i]=y[i];
    }
    root=build(1,m,0);
    for(int i=1;i<=n;i++){
        modify(lt[i],rt[i],root);
    }
    dfs(root);
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}