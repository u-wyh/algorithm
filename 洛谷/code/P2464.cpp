#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXT = MAXN * 80;

int n, m;
// 原始数组
int arr[MAXN];
//用于离散化的数组
int help[MAXN<<1];
int tot,t;

struct node {
    char op;
    int l,r,v;
}nums[MAXN];

// 可持久化线段树
int root[MAXN<<1];//表示 离散化后编号为i的书 的线段树
//初始时最多有MAXN个编号  再加上后续修改操作的个数
int ls[MAXT];
int rs[MAXT];
// 可持久化线段树的节点空间计数
int cnt = 0;
int tree[MAXT];

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

int getrank(int val){
    int l=1,r=t,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(help[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

// 建树，返回头节点编号
int build(int l, int r) {
    int rt = ++cnt;
    if (l == r) {
        tree[rt] = 0;
    } else {
        int mid = (l + r) >> 1;
        ls[rt] = build(l, mid);
        rs[rt] = build(mid + 1, r);
    }
    return rt;
}

//增加位置jobi的数目为jobv
int update(int jobi, int jobv, int l, int r, int i) {
    int rt = ++cnt;//新建一个节点（沿途节点）
    ls[rt] = ls[i];
    rs[rt] = rs[i];
    tree[rt] = tree[i]+jobv;
    //拷贝原有信息
    if (l == r) {
        //到达了要修改的节点位置
        //tree[rt] += jobv;
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            ls[rt] = update(jobi, jobv, l, mid, ls[rt]);
        } else {
            rs[rt] = update(jobi, jobv, mid + 1, r, rs[rt]);
        }
    }
    return rt;
}

// 线段树范围l~r，信息在i号节点里
// 返回l~r范围上jobi位置的值
int query(int jobl,int jobr, int l, int r, int i) {
	if(jobl<=l&&r<=jobr){
        return tree[i];
	}
	else{
        int mid=(l+r)/2;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,ls[i]);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,rs[i]);
        }
        return ans;
	}
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        help[++tot]=arr[i];
    }
    for(int i=1;i<=m;i++){
        cin>>nums[i].op;
        if(nums[i].op=='Q'){
            nums[i].l=read(),nums[i].r=read(),nums[i].v=read();
            help[++tot]=nums[i].v;
        }
        else{
            nums[i].l=read(),nums[i].r=read();
            help[++tot]=nums[i].r;
        }
    }
    sort(help+1,help+tot+1);
    for(int i=1;i<=tot;i++){
        if(help[i]!=help[i-1]){
            help[++t]=help[i];
        }
    }
    root[0]=build(1,n);
    for(int i=1;i<=n;i++){
        int k=getrank(arr[i]);
        arr[i]=k;
        if(root[k]==0){
            root[k]=update(i,1,1,n,root[0]);
        }
        else{
            root[k]=update(i,1,1,n,root[k]);
        }
    }
    for(int i=1;i<=m;i++){
        if(nums[i].op=='Q'){
            cout<<query(nums[i].l,nums[i].r,1,n,root[getrank(nums[i].v)])<<endl;
        }
        else{
            root[arr[nums[i].l]]=update(nums[i].l,-1,1,n,root[arr[nums[i].l]]);
            int k=getrank(nums[i].r);
            arr[nums[i].l]=k;
            if(root[k]==0){
                root[k]=update(nums[i].l,1,1,n,root[0]);
            }
            else{
                root[k]=update(nums[i].l,1,1,n,root[k]);
            }
        }
    }
    return 0;
}
