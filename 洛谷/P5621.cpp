#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const long long INF = 1e18+1;

int n;

struct node{
    int a,b,c,d;
    long long val;
    int id;
    bool left;
};

int m=1;
int help[MAXN];

node nums[MAXN];
node tmp1[MAXN];
node tmp2[MAXN];

long long dp[MAXN];

long long tree[MAXN];

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
    if(a.a!=b.a) return a.a<b.a;
    if(a.b!=b.b) return a.b<b.b;
    if(a.c!=b.c) return a.c<b.c;
    if(a.d!=b.d) return a.d<b.d;
    return a.val>b.val;
}

bool cmp2(node a,node b){
    if(a.b!=b.b) return a.b<b.b;
    return a.id<b.id;
}

bool cmp3(node a,node b){
    if(a.c!=b.c) return a.c<b.c;
    return a.id<b.id;
}

int find(int val){
    int l=1,r=m,ans=1;
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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,long long val){
    while(x<=m){
        tree[x]=max(tree[x],val);
        x+=lowbit(x);
    }
}

long long query(int x){
    long long ans=0;
    while(x){
        ans=max(ans,tree[x]);
        x-=lowbit(x);
    }
    return ans;
}

void clear(int x){
    while(x<=m){
        tree[x]=-INF;
        x+=lowbit(x);
    }
}

void prepare(){
    for(int i=1;i<=n;i++){
        help[i]=nums[i].d;
    }
    sort(help+1,help+n+1);
    for(int i=2;i<=n;i++){
        if(help[i]!=help[i-1]){
            help[++m]=help[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i].d=find(nums[i].d);
    }
    int u=1;
    sort(nums+1,nums+n+1,cmp1);
    for(int i=2;i<=n;i++){
        if(nums[u].a==nums[i].a&&nums[u].b==nums[i].b&&nums[u].c==nums[i].c&&nums[u].d==nums[i].d){
            if(nums[i].val>0){
                nums[u].val+=nums[i].val;
            }
        }
        else{
            nums[++u]=nums[i];
        }
    }
    n=u;
    for(int i=1;i<=n;i++){
        dp[i]=nums[i].val;
        nums[i].id=i;
    }
    for(int i=1;i<=m;i++){
        tree[i]=-INF;
    }
}

void merge(int l,int mid,int r){
    for(int i=l;i<=r;i++){
        tmp2[i]=tmp1[i];
    }
    sort(tmp2+l,tmp2+mid+1,cmp3);
    sort(tmp2+mid+1,tmp2+r+1,cmp3);
    int p1=l-1,p2=mid+1;
    for(;p2<=r;p2++){
        while(p1+1<=mid&&tmp2[p1+1].c<=tmp2[p2].c){
            p1++;
            if(tmp2[p1].left){
                add(tmp2[p1].d,dp[tmp2[p1].id]);
            }
        }
        if(!tmp2[p2].left){
            dp[tmp2[p2].id]=max(dp[tmp2[p2].id],query(tmp2[p2].d)+tmp2[p2].val);
        }
    }
    for (int i = l; i <= p1; i++) {
        if (tmp2[i].left) {
            clear(tmp2[i].d);
        }
    }
}

void cdq2(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq2(l,mid);
    merge(l,mid,r);
    cdq2(mid+1,r);
}

void cdq1(int l,int r){
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    cdq1(l,mid);
    for(int i=l;i<=r;i++){
        tmp1[i]=nums[i];
        tmp1[i].left=(i<=mid);
    }
    sort(tmp1+l,tmp1+r+1,cmp2);
    cdq2(l,r);
    cdq1(mid+1,r);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i].a=read(),nums[i].b=read(),nums[i].c=read(),nums[i].d=read();
        nums[i].val=read();
    }
    prepare();
    cdq1(1,n);
    long long ans=-INF;
    for(int i=1;i<=n;i++){
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}