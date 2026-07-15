#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXM = 1e6+5;
const int INF = 1e9;

int n,m,v;

int cnt;
struct node{
    int op,x,y,id;
};
node nums[MAXN<<1];
node tmp[MAXN<<1];

int cntq;
int ans[MAXN];

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

bool cmp(node a,node b){
    return a.x<b.x;
}

inline int lowbit(int x){
    return x&-x;
}

void update(int x,int val){
    while(x<=v){
        tree[x]=max(tree[x],val);
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=-INF;
    while(x){
        ans=max(ans,tree[x]);
        x-=lowbit(x);
    }
    return ans;
}

void clear(int x){
    while(x<=v){
        tree[x]=-INF;
        x+=lowbit(x);
    }
}

void merge(int l,int mid,int r){
    int p1=l-1,p2=mid+1;
    for(;p2<=r;p2++){
        while(p1+1<=mid&&tmp[p1+1].x<=tmp[p2].x){
            p1++;
            if(tmp[p1].op==1){
                update(tmp[p1].y,tmp[p1].x+tmp[p1].y);
            }
        }
        if(tmp[p2].op==2){
            ans[tmp[p2].id]=min(ans[tmp[p2].id],tmp[p2].x+tmp[p2].y-query(tmp[p2].y));
        }
    }
    for(int i=l;i<=p1;i++){
        if(tmp[i].op==1){
            clear(tmp[i].y);
        }
    }
    sort(tmp+l,tmp+r+1,cmp);
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

void to1(){
    for(int i=1;i<=cnt;i++){
        tmp[i]=nums[i];
    }
    cdq(1,cnt);
}

void to2(){
    for(int i=1;i<=cnt;i++){
        tmp[i]=nums[i];
        tmp[i].x=v-tmp[i].x;
    }
    cdq(1,cnt);
}

void to3(){
    for(int i=1;i<=cnt;i++){
        tmp[i]=nums[i];
        tmp[i].x=v-tmp[i].x;
        tmp[i].y=v-tmp[i].y;
    }
    cdq(1,cnt);
}

void to4(){
    for(int i=1;i<=cnt;i++){
        tmp[i]=nums[i];
        tmp[i].y=v-tmp[i].y;
    }
    cdq(1,cnt);
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        int x,y;
        x=read(),y=read();
        x++,y++;
        nums[++cnt]={1,x,y,0};
        v=max(v,max(x,y));
    }
    for(int i=1;i<=m;i++){
        ++cnt;
        nums[cnt].op=read(),nums[cnt].x=read()+1,nums[cnt].y=read()+1;
        if(nums[cnt].op==2){
            nums[cnt].id=++cntq;
        }
        v=max(v,max(nums[cnt].x,nums[cnt].y));
    }
    v++;
    for(int i=1;i<=v;i++){
        tree[i]=-INF;
    }
    for(int i=1;i<=cntq;i++){
        ans[i]=INF;
    }
    to1();
    to2();
    to3();
    to4();
    for(int i=1;i<=cntq;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}