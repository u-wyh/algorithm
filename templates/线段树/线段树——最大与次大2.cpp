//P4087
// 这道题目使用最大值和次大值之间的关系  可以很方便的统计答案
// 在什么时候答案会加呢
// 1.rk1产奶量变化了（原来的rk1不一定rk1了）
// （1：rk1还是那头牛（不是变化）
// （2：rk1不是那头牛（显然要换照片！）
// （3：rk1数量变多（rk1掉分了，和后面的牛并列）
// 2.rk1产奶量没变（原来的rk1还是rk1）
// （1：rk1数量没变（不是变化）
// （2：rk1数量变了（下面的牛奋起直追，要多挂照片，所以变化）
// 总结一下 答案变化就是要么第一名的牛变多了  要么第一名的个数还是一个  但是牛变了
// 因为每次最多只会增加一头牛的产量
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,g;
struct node{
    int pos;
    int mmax;
    int maxnum;
    int mmin;
    int minnum;//表示最大的数字和次大的数字 以及数目
}tree[MAXN<<2];
struct node1{
    int t,pos,v;
}nums[MAXN];
int m=1;
int tmp[MAXN];

bool cmp(node1 a,node1 b){
    return a.t<b.t;
}

int getrank(int v){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)/2;
        if(tmp[mid]>=v){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void up(int i){
    if(tree[i<<1].mmax>tree[i<<1|1].mmax){
        tree[i].pos=tree[i<<1].pos;
        tree[i].mmax=tree[i<<1].mmax;
        tree[i].maxnum=tree[i<<1].maxnum;
        if(tree[i<<1].mmin>tree[i<<1|1].mmax){
            tree[i].mmin=tree[i<<1].mmin;
            tree[i].minnum=tree[i<<1].minnum;
        }
        else if(tree[i<<1].mmin==tree[i<<1|1].mmax){
            tree[i].mmin=tree[i<<1].mmin;
            tree[i].minnum=tree[i<<1].minnum+tree[i<<1|1].maxnum;
        }
        else{
            tree[i].mmin=tree[i<<1|1].mmax;
            tree[i].minnum=tree[i<<1|1].maxnum;
        }
    }
    else if(tree[i<<1].mmax<tree[i<<1|1].mmax){
        tree[i].pos=tree[i<<1|1].pos;
        tree[i].mmax=tree[i<<1|1].mmax;
        tree[i].maxnum=tree[i<<1|1].maxnum;
        if(tree[i<<1|1].mmin>tree[i<<1].mmax){
            tree[i].mmin=tree[i<<1|1].mmin;
            tree[i].minnum=tree[i<<1|1].minnum;
        }
        else if(tree[i<<1|1].mmin==tree[i<<1].mmax){
            tree[i].mmin=tree[i<<1|1].mmin;
            tree[i].minnum=tree[i<<1|1].minnum+tree[i<<1].maxnum;
        }
        else{
            tree[i].mmin=tree[i<<1].mmax;
            tree[i].minnum=tree[i<<1].maxnum;
        }
    }
    else {
        tree[i].pos=tree[i<<1].pos;
        tree[i].mmax=tree[i<<1].mmax;
        tree[i].maxnum=tree[i<<1].maxnum+tree[i<<1|1].maxnum;
        if(tree[i<<1].mmin>tree[i<<1|1].mmin){
            tree[i].mmin=tree[i<<1].mmin;
            tree[i].minnum=tree[i<<1].minnum;
        }
        else if(tree[i<<1].mmin==tree[i<<1|1].mmin){
            tree[i].mmin=tree[i<<1].mmin;
            tree[i].minnum=tree[i<<1].minnum+tree[i<<1|1].minnum;
        }
        else{
            tree[i].mmin=tree[i<<1|1].mmin;
            tree[i].minnum=tree[i<<1|1].minnum;
        }
    }
}

void build(int l,int r,int i){
    if(l==r&&l==m+1){
        tree[i].pos=l;
        tree[i].mmax=g;
        tree[i].maxnum=1;
        tree[i].mmin=-1;
        tree[i].minnum=0;
        return ;
    }
    if(l==r){
        tree[i].pos=l;
        tree[i].mmax=g;
        tree[i].maxnum=1;
        tree[i].mmin=0;
        tree[i].minnum=0;
        return;
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void add(int pos,int v,int l,int r,int i){
    if(l==r){
        tree[i].mmax+=v;
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

int main()
{
    cin>>n>>g;
    for(int i=1;i<=n;i++){
        cin>>nums[i].t>>nums[i].pos>>nums[i].v;
        tmp[i]=nums[i].pos;
    }
    sort(tmp+1,tmp+n+1);
    sort(nums+1,nums+n+1,cmp);
    // 离散化
    for(int i=2;i<=n;i++){
        if(tmp[i]!=tmp[i-1]){
            tmp[++m]=tmp[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].pos=getrank(nums[i].pos);
    }
    m++;
    build(1,m,1);
    int ans=0,prenum=0,premax=0,prepos;
    for(int i=1;i<=n;i++){
        prepos=tree[1].pos;
        premax=tree[1].mmax;
        prenum=tree[1].maxnum;
        add(nums[i].pos,nums[i].v,1,m,1);
        if(prenum!=tree[1].maxnum){
            ans++;
        }
        else if(prenum==1&&prepos!=tree[1].pos){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
//最大的那个牛的产量发生了变化  如果还是最大的  实际上是不增加答案的