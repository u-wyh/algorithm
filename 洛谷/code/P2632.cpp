#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

int fa[MAXN<<1];
int ax,ay,bx,by;
int cx,cy,dx,dy;
double a[MAXN];
double b[MAXN];

double k1,d1,k2,d2;

struct node{
    int u,v;
    double w;
}nums[MAXN*6];
int cnt;

bool cmp(node a,node b){
    return a.w<b.w;
}

int find1(double x,int op){
    //查找第一个大于等于的编号
    if(op==1){
        int l=1,r=m,ans=m+1;
        while(l<=r){
            int mid=(l+r)/2;
            if(b[mid]>=x){
                ans=mid;
                r=mid-1;
            }
            else{
                l=mid+1;
            }
        }
        return ans;
    }
    else{
        int l=1,r=n,ans=n+1;
        while(l<=r){
            int mid=(l+r)/2;
            if(a[mid]>=x){
                ans=mid;
                r=mid-1;
            }
            else{
                l=mid+1;
            }
        }
        return ans;
    }
}

int find2(double x,int op){
    //查找最后一个小于它的元素编号
    if(op==1){
        int l=1,r=m,ans=0;
        while(l<=r){
            int mid=(l+r)/2;
            if(b[mid]<x){
                ans=mid;
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        return ans;
    }
    else{
        int l=1,r=n,ans=0;
        while(l<=r){
            int mid=(l+r)/2;
            if(a[mid]<x){
                ans=mid;
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        return ans;
    }
}

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

bool un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
        return true;
    }
    return false;
}

double dist(int i,int j){
    //接受两个参数 a数组的小标i  b数组的下标j
    double x1=a[i],x2=a[j];
    double y1=k1*x1+d1,y2=k2*x2+d2;
    return sqrt(1ll*(x1-x2)*(x1-x2)+1ll*(y1-y2)*(y1-y2));
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n+m;i++){
        fa[i]=i;
    }
    scanf("%d %d %d %d %d %d %d %d",&ax,&ay,&bx,&by,&cx,&cy,&dx,&dy);
    for(int i=1;i<=n;i++){
        scanf("%lf",&a[i]);
    }
    for(int i=1;i<=m;i++){
        scanf("%lf",&b[i]);
    }
    k1=(ay-by)*1.0/(ax-bx);
    d1=by-k1*bx;
    k2=(cy-dy)*1.0/(cx-dx);
    d2=dy-k2*dx;
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    for(int i=1;i<n;i++){
        nums[++cnt]={i,i+1,sqrt(k1*k1+1)*(a[i+1]-a[i])};
    }
    for(int i=1;i<m;i++){
        nums[++cnt]={i+n,i+n+1,sqrt(1+k2*k2)*(b[i+1]-b[i])};
    }
    for(int i=1;i<=n;i++){
        double x;
        x=(k1*a[i]+1.0/k2*a[i]+d1-d2);
        int pos=find1(x,1);
        if(pos==m+1){
            continue;
        }
        nums[++cnt]={i,pos+n,dist(i,pos)};
        pos=find2(x,1);
        if(pos==0){
            continue;
        }
        nums[++cnt]={i,pos+n,dist(i,pos)};
    }
    for(int i=1;i<=m;i++){
        double x;
        x=(k2*b[i]+1.0/k1*b[i]+d2-d1);
        int pos=find1(x,2);
        if(pos==n+1){
            continue;
        }
        nums[++cnt]={pos,i+n,dist(pos,i)};
        pos=find2(x,2);
        if(pos==0){
            continue;
        }
        nums[++cnt]={pos,i+n,dist(pos,i)};
    }
    sort(nums+1,nums+cnt+1,cmp);
    double ans=0;
    for(int i=1;i<=cnt;i++){
        int u=nums[i].u,v=nums[i].v;
        if(un(u,v)){
            ans+=nums[i].w;
        }
    }
    printf("%.3lf",ans);
    return 0;
}