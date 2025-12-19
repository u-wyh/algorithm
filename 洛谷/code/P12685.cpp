#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXT = MAXN*320;
const int INF = 1e9+1;

int n,q,m;
int val[MAXN];
int arr[MAXN];

int root[MAXN];

int ls[MAXT];
int rs[MAXT];
int sum[MAXT];
int cnt;
long long ans;

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

int find(int val){
    int l=1,r=m,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
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

int inquery(int jobl,int jobr,int l,int r,int i){
    if(i==0){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int ans=0;
        int mid=(l+r)>>1;
        if(jobl<=mid){
            ans+=inquery(jobl,jobr,l,mid,ls[i]);
        }
        if(jobr>mid){
            ans+=inquery(jobl,jobr,mid+1,r,rs[i]);
        }
        return ans;
    }
}

int inadd(int jobi,int jobv,int l,int r,int i){
    if(i==0){
        i=++cnt;
    }
    if(l==r){
        sum[i]+=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(jobi<=mid){
            ls[i]=inadd(jobi,jobv,l,mid,ls[i]);
        }
        else{
            rs[i]=inadd(jobi,jobv,mid+1,r,rs[i]);
        }
        sum[i]=sum[ls[i]]+sum[rs[i]];
    }
    return i;
}

void add(int x,int v){
    for(int i=x;i<=n;i+=lowbit(i)){
        root[i]=inadd(val[x],v,1,m,root[i]);
    }
}

int query(int l,int r,int jobl,int jobr){
    int ans=0;
    for(int i=r;i;i-=lowbit(i)){
        ans+=inquery(jobl,jobr,1,m,root[i]);
    }
    for(int i=l-1;i;i-=lowbit(i)){
        ans-=inquery(jobl,jobr,1,m,root[i]);
    }
    return ans;
}

void compute(int a,int b){
    if(val[a]==val[b]){
        return ;
    }
    ans-=query(a+1,b-1,1,val[a]-1);
    ans+=query(a+1,b-1,val[a]+1,m);
    ans-=query(a+1,b-1,val[b]+1,m);
    ans+=query(a+1,b-1,1,val[b]-1);
    if(val[a]<val[b]){
        ans++;
    }
    else{
        ans--;
    }
    add(a,-1);
    add(b,-1);
    swap(val[a],val[b]);
    add(a,1);
    add(b,1);
}

void prepare(){
    int len=n;
    for(int i=1;i<=n;i++){
        arr[i]=val[i];
    }
    arr[++len]=INF;
    arr[++len]=-INF;
    sort(arr+1,arr+len+1);
    m=1;
    for(int i=2;i<=len;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
        add(i,1);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    prepare();
    for(int i=2;i<=n;i++){
        ans+=query(1,i-1,val[i]+1,m);
    }
    printf("%lld\n",ans);
    q=read();
    for(int i=1;i<=q;i++){
        int a,b;
        a=read(),b=read();
        if(a>b){
            swap(a,b);
        }
        compute(a,b);
        printf("%lld\n",ans);
    }
    return 0;
}