#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXM = 2e6+5;
const int MAXQ = 1e4+5;

int w;

struct node{
    int x,y,v,id;
}nums[MAXN];
int cnte;
int cntq;

int ans[MAXQ];

int tree[MAXM];

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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=w){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

bool cmp(node a,node b){
    return a.x<b.x;
}

void merge(int l,int mid,int r){
    int p1,p2;
    for(p1=l-1,p2=mid+1;p2<=r;p2++){
        while(p1+1<=mid&&nums[p1+1].x<=nums[p2].x){
            p1++;
            if(nums[p1].id==0){
                add(nums[p1].y,nums[p1].v);
            }
        }
        ans[nums[p2].id]+=nums[p2].v*query(nums[p2].y);
    }
    for(int i=l;i<=p1;i++){
        if(nums[i].id==0){
            add(nums[i].y,-nums[i].v);
        }
    }
    sort(nums+l,nums+r+1,cmp);
}

void cdq(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)/2;
    cdq(l,mid);
    cdq(mid+1,r);
    merge(l,mid,r);
}

int main()
{
    int op;
    op=read(),w=read();
    w++;
    op=read();
    while(op!=3){
        if(op==1){
            nums[++cnte].x=read()+1;
            nums[cnte].y=read()+1;
            nums[cnte].v=read();
        }
        else{
            int a,b,c,d;
            cntq++;
            a=read(),b=read(),c=read(),d=read();
            a++,b++,c++,d++;
            nums[++cnte]={c,d,1,cntq};
            nums[++cnte]={a-1,b-1,1,cntq};
            nums[++cnte]={a-1,d,-1,cntq};
            nums[++cnte]={c,b-1,-1,cntq};
        }
        op=read();
    }
    cdq(1,cnte);
    for(int i=1;i<=cntq;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}