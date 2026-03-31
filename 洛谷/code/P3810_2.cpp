#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;

int n,k;
struct node{
    int i,a,b,c;
};
node arr[MAXN];

int ans[MAXN];
int cnt[MAXN];

int tree[MAXM];

bool cmpabc(node x,node y){
    if(x.a!=y.a){
        return x.a<y.a;
    }
    else if(x.b!=y.b){
        return x.b<y.b;
    }
    else if(x.c!=y.c){
        return x.c<y.c;
    }
    return x.i<y.i;
}

bool cmp(node x,node y){
    return x.b<y.b;
}

int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=k){
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

void merge(int l,int mid,int r){
    int p1,p2;
    for(p1=l-1,p2=mid+1;p2<=r;p2++){
        while(p1+1<=mid&&arr[p1+1].b<=arr[p2].b){
            p1++;
            add(arr[p1].c,1);
        }
        ans[arr[p2].i]+=query(arr[p2].c);
    }
    for(int i=l;i<=p1;i++){
        add(arr[i].c,-1);
    }
    sort(arr+l,arr+r+1,cmp);
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

void compute(){
    sort(arr+1,arr+n+1,cmpabc);
    for(int i=n;i>=1;i--){
        if((arr[i+1].a==arr[i].a)&&(arr[i+1].b==arr[i].b)&&(arr[i+1].c==arr[i].c)){
            ans[arr[i].i]+=ans[arr[i+1].i]+1;
        }
    }

    cdq(1,n);

    for(int i=1;i<=n;i++){
        cnt[ans[i]]++;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>k;
    for(int i=1;i<=n;i++){
        arr[i].i=i;
        cin>>arr[i].a>>arr[i].b>>arr[i].c;
    }

    compute();

    for(int i=1;i<=n;i++){
        cout<<cnt[i-1]<<endl;
    }
    return 0;
}