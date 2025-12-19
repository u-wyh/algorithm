#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 5e5+5;

int n,m;

struct node{
    int x,y,v,id;
}nums[4*MAXN+MAXM];
int cnt;

node tmp[4*MAXN+MAXM];

int ans[MAXM];

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

bool cmp(node a,node b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.id<b.id;//让添加操作类型在前面
}

void merge(int l,int mid,int r){
    int p1,p2,tree=0;
    for(p1=l-1,p2=mid+1;p2<=r;p2++){
        while(p1+1<=mid&&nums[p1+1].y<=nums[p2].y){
            p1++;
            if(nums[p1].id==0){
                tree++;
            }
        }
        ans[nums[p2].id]+=nums[p2].v*tree;
    }

    p1=l,p2=mid+1;
    int i=l;
    while(p1<=mid&&p2<=r){
        tmp[i++]=nums[p1].y<nums[p2].y?nums[p1++]:nums[p2++];
    }
    while(p1<=mid){
        tmp[i++]=nums[p1++];
    }
    while(p2<=r){
        tmp[i++]=nums[p2++];
    }
    for(int i=l;i<=r;i++){
        nums[i]=tmp[i];
    }
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq(l,mid);
    cdq(mid+1,r);
    merge(l,mid,r);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[++cnt].x=read();
        nums[cnt].y=read();
    }
    for(int i=1;i<=m;i++){
        int a,b,c,d;
        a=read(),b=read(),c=read(),d=read();
        nums[++cnt]={c,d,1,i};
        nums[++cnt]={a-1,b-1,1,i};
        nums[++cnt]={a-1,d,-1,i};
        nums[++cnt]={c,b-1,-1,i};
    }
    sort(nums+1,nums+cnt+1,cmp);
    cdq(1,cnt);
    for(int i=1;i<=m;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}