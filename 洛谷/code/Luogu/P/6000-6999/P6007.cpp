#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const long long INF = 1e12;

int n,p,cnt;

int m=1;
int arr[MAXN<<1];

int to[MAXN<<1];
int val[MAXN<<1];

long long tree[MAXN<<1];

long long ans;

long long f[MAXN<<1];

struct node{
    int x,y,id;
}nums[MAXN<<1];

node tmp[MAXN<<1];

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

bool cmp1(node a,node b){
    if(a.x!=b.x) return a.x<b.x;
    if(a.y!=b.y) return a.y<b.y;
    return a.id<b.id;
}

bool cmp2(node a,node b){
    return a.y<b.y;
}

int find(int val){
    int l=1,r=m,ans;
    while(l<=r){
        int mid=(l+r)/2;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

inline int lowbit(int x){
    return x&-x;
}

void update(int x,long long val){
    while(x<=m){
        tree[x]=min(tree[x],val);
        x+=lowbit(x);
    }
}

long long query(int x){
    long long ans=INF;
    while(x){
        ans=min(ans,tree[x]);
        x-=lowbit(x);
    }
    return ans;
}

void clear(int x){
    while(x<=m){
        tree[x]=INF;
        x+=lowbit(x);
    }
}

void merge(int l,int mid,int r){
    for(int i=l;i<=r;i++){
        tmp[i]=nums[i];
    }
    sort(tmp+l,tmp+mid+1,cmp2);
    sort(tmp+mid+1,tmp+r+1,cmp2);
    int p1=l-1,p2=mid+1;
    for(;p2<=r;p2++){
        while(p1+1<=mid&&tmp[p1+1].y<=tmp[p2].y){
            p1++;
            update(tmp[p1].y,f[tmp[p1].id]);
        }
        f[tmp[p2].id]=min(f[tmp[p2].id],query(tmp[p2].y));
    }
    for(int i=l;i<=p1;i++){
        clear(tmp[i].y);
    }
}

void cdq(int l,int r){
    if(l==r){
        if(to[nums[l].id]){
            f[to[nums[l].id]]=min(f[to[nums[l].id]],f[nums[l].id]+val[nums[l].id]);
        }
        return ;
    }
    int mid=(l+r)/2;
    cdq(l,mid);
    merge(l,mid,r);
    cdq(mid+1,r);
}

int main()
{
    n=read(),p=read();
    nums[++cnt]={0,0,1};
    for(int i=1;i<=p;i++){
        nums[++cnt].x=read();nums[cnt].y=read();nums[cnt].id=cnt;
        nums[++cnt].x=read();nums[cnt].y=read();nums[cnt].id=cnt;

        to[cnt-1]=cnt;
        val[cnt-1]=(nums[cnt-1].x+nums[cnt-1].y)-(nums[cnt].x+nums[cnt].y);
    }
    for(int i=1;i<=cnt;i++){
        arr[i]=nums[i].y;
    }
    for(int i=1;i<=cnt;i++){
        f[i]=INF;
    }
    f[1]=0;
    sort(arr+1,arr+cnt+1);
    for(int i=2;i<=cnt;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=cnt;i++){
        nums[i].y=find(nums[i].y);
    }
    for(int i=1;i<=m;i++){
        tree[i]=INF;
    }
    sort(nums+1,nums+cnt+1,cmp1);
    int st=1;
    if(nums[2].x+nums[2].y==0){
        f[nums[2].id]=0;
        st=2;
    }
    cdq(st,cnt);
    for(int i=1;i<=cnt;i++){
        ans=min(ans,f[i]);
    }
    ans+=2*n;
    cout<<ans<<endl;
    return 0;
}