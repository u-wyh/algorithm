#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e5+5;
const int INF = 2e15;

int n;
struct node{
    int x,y;
}nums[MAXN];
int tmp[MAXN];
int cnt=0;

bool cmp(node a,node b){
    return (a.x==b.x)?(a.y<b.y):(a.x<b.x);
}

bool cmp1(int a,int b){
    return nums[a].y<nums[b].y;
}

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

inline int dist(int i,int j){
    int x=1ll*(nums[i].x-nums[j].x)*(nums[i].x-nums[j].x);
    int y=1ll*(nums[i].y-nums[j].y)*(nums[i].y-nums[j].y);
    return x+y;
}

int merge(int l,int r){
    int d=INF;
    if(l==r){
        return d;
    }
    if(r==l+1){
        return dist(l,r);
    }
    int mid=(l+r)>>1;
    d=min(merge(l,mid),merge(mid+1,r));
    cnt=0;
    for(int i=l;i<=r;i++){
        if((nums[mid].x-nums[i].x)*(nums[mid].x-nums[i].x)<=d){
            tmp[++cnt]=i;
        }
    }
    sort(tmp+1,tmp+cnt+1,cmp1);
    for(int i=1;i<=cnt;i++){
        for(int j=i+1;j<=cnt&&((nums[tmp[j]].y-nums[tmp[i]].y)*(nums[tmp[j]].y-nums[tmp[i]].y)<=d);j++){
            d=min(d,dist(tmp[i],tmp[j]));
        }
    }
    return d;
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i].x=read();
        nums[i].y=read();
    }
    sort(nums+1,nums+n+1,cmp);
    printf("%lld\n",merge(1,n));
    return 0;
}