#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;
const int INF = 1e18;

int n;
struct node{
    int a,b,c,d;
    int v;
    int i;
    bool left;
};
node arr[MAXN];
int len;
int sorted[MAXN];

int dp[MAXN];

node tmp1[MAXN];
node tmp2[MAXN];

int tree[MAXN];

int find(int val){
    int l=1,r=len,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

bool cmp1(node a,node b){
    if(a.a!=b.a){
        return a.a<b.a;
    }
    else if(a.b!=b.b){
        return a.b<b.b;
    }
    else if(a.c!=b.c){
        return a.c<b.c;
    }
    else if(a.d!=b.d){
        return a.d<b.d;
    }
    return a.v>b.v;
}

bool cmp2(node a,node b){
    if(a.b!=b.b)
        return a.b<b.b;
    return a.i<b.i;
}

bool cmp3(node a,node b){
    if(a.c!=b.c){
        return a.c<b.c;
    }
    return a.i<b.i;
}

int lowbit(int x){
    return x&-x;
}

void more(int x,int val){
    while(x<=len){
        tree[x]=max(tree[x],val);
        x+=lowbit(x);
    }
}

int query(int x){
    int ans=0;
    while(x){
        ans=max(ans,tree[x]);
        x-=lowbit(x);
    }
    return ans;
}

void clear(int x){
    while(x<=len){
        tree[x]=-INF;
        x+=lowbit(x);
    }
}

void merge(int l,int mid,int r){
    for(int i=l;i<=r;i++){
        tmp2[i]=tmp1[i];
    }
    sort(tmp2+l,tmp2+mid+1,cmp3);
    sort(tmp2+mid+1,tmp2+r+1,cmp3);

    int p1,p2;
    for(p1=l-1,p2=mid+1;p2<=r;p2++){
        while(p1+1<=mid&&tmp2[p1+1].c<=tmp2[p2].c){
            p1++;
            if(tmp2[p1].left){
                more(tmp2[p1].d,dp[tmp2[p1].i]);
            }
        }
        if(!tmp2[p2].left){
            dp[tmp2[p2].i]=max(dp[tmp2[p2].i],query(tmp2[p2].d)+tmp2[p2].v);
        }
    }

    for(int i=l;i<=p1;i++){
        if(tmp2[i].left){
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
        tmp1[i]=arr[i];
        tmp1[i].left=(i<=mid);
    }
    sort(tmp1+l,tmp1+r+1,cmp2);
    cdq2(l,r);
    cdq1(mid+1,r);
}

void compute(){
    for(int i=1;i<=n;i++){
        sorted[i]=arr[i].d;
    }
    sort(sorted+1,sorted+n+1);
    len=1;
    for(int i=2;i<=n;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }
    for(int i=1;i<=n;i++){
        arr[i].d=find(arr[i].d);
    }

    sort(arr+1,arr+n+1,cmp1);
    int m=1;
    for(int i=2;i<=n;i++){
        if(arr[m].a==arr[i].a&&arr[m].b==arr[i].b&&arr[i].c==arr[m].c&&arr[i].d==arr[m].d){
            if(arr[i].v>0){
                arr[m].v+=arr[i].v;
            }
        }
        else{
            arr[++m]=arr[i];
        }
    }
    n=m;

    for(int i=1;i<=n;i++){
        arr[i].i=i;
        dp[i]=arr[i].v;
    }
    for(int i=1;i<=len;i++){
        tree[i]=-INF;
    }

    cdq1(1,n);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i].a>>arr[i].b>>arr[i].c>>arr[i].d>>arr[i].v;
    }
    compute();

    int ans=-INF;
    for(int i=1;i<=n;i++){
        ans=max(ans,dp[i]);
    }
    cout<<ans<<endl;
    return 0;
}