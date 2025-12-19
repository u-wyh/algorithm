#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;
const int MAXM = 1e5+5;

int n,m,need;
int mid;
struct node{
    int u,v,w,col;
};

node nums[MAXM];

int fa[MAXN];

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
    if((a.w+(1-a.col)*mid)!=(b.w+(1-b.col)*mid)) return (a.w+(1-a.col)*mid)<(b.w+(1-b.col)*mid);
    return a.col<b.col;
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

bool check(){
    int cnt=0;
    sort(nums+1,nums+m+1,cmp);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    int k=0;
    for(int i=1;i<=m;i++){
        int x=nums[i].u;
        int y=nums[i].v;
        int fx=find(x),fy=find(y);
        if(fx!=fy){
            fa[fx]=fy;
            if(nums[i].col==0){
                cnt++;
            }
            k++;
            if(k==n-1){
                break;
            }
        }
    }
    return cnt>=need;
}

int main()
{
    n=read(),m=read(),need=read();
    for(int i=1;i<=m;i++){
        nums[i].u=read()+1,nums[i].v=read()+1,nums[i].w=read(),nums[i].col=read();
    }
    int l=-105,r=105,ans;
    while(l<=r){
        mid=(l+r)>>1;
        if(check()){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    mid=ans;
    int all=0;
    sort(nums+1,nums+m+1,cmp);
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(int i=1;i<=m;i++){
        int x=nums[i].u;
        int y=nums[i].v;
        int fx=find(x),fy=find(y);
        if(fx!=fy){
            fa[fx]=fy;
            all+=((1-nums[i].col)*mid+nums[i].w);
        }
    }
    all-=mid*need;
    // cout<<mid<<endl;
    printf("%d\n",all);
    return 0;
}