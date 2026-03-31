#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXM = 5e4+5;

int n,m;
int val[MAXN];
int pos[MAXN];
int del[MAXN];

struct node{
    int val,pos,d,t;
};
node arr[MAXN+MAXM];

int ans[MAXN];

int tree[MAXN];

int lowbit(int x){
    return x&-x;
}

int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

bool cmp(node a,node b){
    return a.pos<b.pos;
}

void merge(int l,int mid,int r){
    int p1,p2;
    for(p1=l-1,p2=mid+1;p2<=r;p2++){
        while(p1+1<=mid&&arr[p1+1].pos<arr[p2].pos){
            p1++;
            add(arr[p1].val,arr[p1].d);
        }
        ans[arr[p2].t]+=(query(n)-query(arr[p2].val))*arr[p2].d;
    }
    for(int i=l;i<=p1;i++){
        add(arr[i].val,-arr[i].d);
    }

    for(p1=mid+1,p2=r;p2>mid;p2--){
        while(p1-1>=l&&arr[p1-1].pos>arr[p2].pos){
            p1--;
            add(arr[p1].val,arr[p1].d);
        }
        ans[arr[p2].t]+=query(arr[p2].val-1)*arr[p2].d;
    }
    for(int i=mid;i>=p1;i--){
        add(arr[i].val,-arr[i].d);
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
    cdq(1,n+m);

    for(int i=1;i<=m;i++){
        ans[i]+=ans[i-1];
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        pos[val[i]]=i;
    }
    for(int i=1;i<=m;i++){
        cin>>del[i];
    }

    for(int i=1;i<=n;i++){
        arr[i]={val[i],i,1,0};
    }
    for(int i=1;i<=m;i++){
        arr[n+i]={del[i],pos[del[i]],-1,i};
    }

    compute();

    for(int i=0;i<m;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}