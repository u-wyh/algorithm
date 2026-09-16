// https://www.luogu.com.cn/problem/P6224
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int INF = 6e9;

int n,m;
int maxv;

struct node{
    int op,x,y,id;
};
bool nodecmp(node &a,node &b){
    return a.x<b.x;
}
node tim[MAXN];
node arr[MAXN];
int cnte;
int cntq;

int tree1[MAXN];
int tree2[MAXN];
int ans[MAXN];

int sorted[MAXN];
int len;

int lowbit(int x){
    return x&-x;
}

void update(int i,int v){
    while(i<=len){
        tree1[i]=max(tree1[i],v);
        tree2[i]=min(tree2[i],v);
        i+=lowbit(i);
    }
}

int ans1,ans2;
void query(int x){
    ans1=-INF;
    ans2=INF;
    while(x){
        ans1=max(ans1,tree1[x]);
        ans2=min(ans2,tree2[x]);
        x-=lowbit(x);
    }
}

void clear(int x){
    while(x<=len){
        tree1[x]=-INF;
        tree2[x]=INF;
        x+=lowbit(x);
    }
}

void merge(int l,int mid,int r){
    int p1,p2;
    for(p1=l-1,p2=mid+1;p2<=r;p2++){
        while(p1+1<=mid&&arr[p1+1].x<=arr[p2].x){
            p1++;
            if(arr[p1].op==0){
                update(arr[p1].y,sorted[arr[p1].y]+arr[p1].x);
            }
        }
        if(arr[p2].op){
            query(arr[p2].y);
            int val=sorted[arr[p2].y]+arr[p2].x;
            if(arr[p2].op==1){
                ans[arr[p2].id]=min(ans[arr[p2].id],val-ans1);
            }
            else{
                ans[arr[p2].id]=max(ans[arr[p2].id],val-ans2);
            }
        }
    }
    for(int i=l;i<=p1;i++){
        if(arr[i].op==0){
            clear(arr[i].y);
        }
    }
    sort(arr+l,arr+r+1,nodecmp);
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

int find(int x){
    int l=1,r=len,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=x){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void prepare(){
    for(int i=1;i<=cnte;i++){
        sorted[i]=arr[i].y;
    }
    sort(sorted+1,sorted+cnte+1);
    len=1;
    for(int i=2;i<=cnte;i++){
        if(sorted[i]!=sorted[i-1]){
            sorted[++len]=sorted[i];
        }
    }
    for(int i=1;i<=cnte;i++){
        arr[i].y=find(arr[i].y);
    }
    for(int i=1;i<=len;i++){
        tree1[i]=-INF;
        tree2[i]=INF;
    }
}

void to1(){
    for(int i=1;i<=cnte;i++){
        arr[i]=tim[i];
    }
    prepare();
    cdq(1,cnte);
}

void to2(){
    for(int i=1;i<=cnte;i++){
        arr[i]=tim[i];
        arr[i].x=-arr[i].x;
    }
    prepare();
    cdq(1,cnte);
}

void to3(){
    for(int i=1;i<=cnte;i++){
        arr[i]=tim[i];
        arr[i].x=-arr[i].x;
        arr[i].y=maxv-arr[i].y;
    }
    prepare();
    cdq(1,cnte);
}

void to4(){
    for(int i=1;i<=cnte;i++){
        arr[i]=tim[i];
        arr[i].y=maxv-arr[i].y;
    }
    prepare();
    cdq(1,cnte);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    maxv=0;
    int len1=0;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        tim[++cnte]={0,x,y};
        maxv=max(maxv,y);
        maxv=max(maxv,x);
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        maxv=max(maxv,y);
        maxv=max(maxv,x);
        if(op==0){
            tim[++cnte]={0,x,y};
        }
        else if(op==1){
            tim[++cnte]={1,x,y,++cntq};
            ans[cntq]=INF;
        }
        else{
            tim[++cnte]={2,x,y,++cntq};
            ans[cntq]=-INF;
        }
    }
    to1();
    to2();
    to3();
    to4();
    for(int i=1;i<=cntq;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}