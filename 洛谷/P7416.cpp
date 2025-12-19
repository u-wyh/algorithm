#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;

int arr[MAXN];
struct node{
    int l,r,id;
}nums[MAXN];

int last[MAXN];//记录上次颜色出现的位置
int pre[MAXN];//记录当前节点i的颜色是由哪里来的  如果是本身 设置为0
//比如  1 2 2 3 2 1  ：0 0 2 0 3 1
int ans[MAXN];//用于记录答案

//线段树部分
//注意：这次叶子结点管控范围是0~n  更准确的来说是0~n-1  表示的是pre数组在i位置结束的点的个数
int tree[MAXN<<2];

//查询区间最小值  线段树
int segtree[MAXN<<2];

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

//以下部分是区间最小值线段树的操作
void upmin(int i){
    segtree[i]=min(segtree[i<<1],segtree[i<<1|1]);
}

void update(int pos,int v,int l,int r,int i){
    if(l==r){
        segtree[i]=v;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            update(pos,v,l,mid,i<<1);
        }
        else{
            update(pos,v,mid+1,r,i<<1|1);
        }
        upmin(i);
    }
}

int querymin(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return segtree[i];
    }
    else{
        int ans=INT_MAX;
        int mid=(l+r)/2;
        if(jobl<=mid){
            ans=min(ans,querymin(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=min(ans,querymin(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

//将查询数组按照右端点排序
bool cmp(node a,node b){
    return a.r<b.r;
}

//以下函数是线段树的操作
void up(int i){
    tree[i]=tree[i<<1]+tree[i<<1|1];
}

void add(int pos,int v,int l,int r,int i){
    if(l==r){
        tree[i]+=v;
    }
    else{
        int mid=(l+r)/2;
        if(pos<=mid){
            add(pos,v,l,mid,i<<1);
        }
        else{
            add(pos,v,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)/2;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
        update(i,arr[i],1,n,1);
        if(last[arr[i]]==0){
            //如果上一个颜色不存在 那么就是0
            pre[i]=0;
        }
        else{
            if(querymin(last[arr[i]]+1,i,1,n,1)<arr[i]){
                //表示中间存在比他颜色更小的
                pre[i]=0;
            }
            else{
                pre[i]=last[arr[i]];
            }
        }
        last[arr[i]]=i;
    }
    for(int i=1;i<=m;i++){
        nums[i].l=read(),nums[i].r=read();
        nums[i].id=i;
    }
    sort(nums+1,nums+m+1,cmp);
    int r=0;//表示现在移动到哪里了
    for(int i=1;i<=m;i++){
        while(r<nums[i].r){
            r++;
            add(pre[r],1,0,n,1);
        }
        int tmp=query(0,nums[i].l-1,0,n,1);
        ans[nums[i].id]=tmp-(nums[i].l-1);
    }
    for(int i=1;i<=m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
