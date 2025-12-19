#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;
int nums[MAXN];

double sine[MAXN<<2];
double cosi[MAXN<<2];
long long tag[MAXN<<2];

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

void up(int i){
    sine[i]=sine[i<<1]+sine[i<<1|1];
    cosi[i]=cosi[i<<1]+cosi[i<<1|1];
}

void build(int l,int r,int i){
    tag[i]=0;
    if(l==r){
        sine[i]=sin(nums[l]);
        cosi[i]=cos(nums[l]);
    }
    else{
        int mid=(l+r)/2;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void lazy(int i,long long v){
    tag[i]+=v;
    double s=sine[i],c=cosi[i];
    sine[i]=s*cos(v)+c*sin(v);
    cosi[i]=c*cos(v)-s*sin(v);
}

void down(int i){
    if(tag[i]){
        lazy(i<<1,tag[i]);
        lazy(i<<1|1,tag[i]);
        tag[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        lazy(i,jobv);
    }
    else{
        int mid=(l+r)/2;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

double query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sine[i];
    }
    else{
        int mid=(l+r)/2;
        down(i);
        double ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    build(1,n,1);
    m=read();
    for(int i=1;i<=m;i++){
        int op,x,y,v;
        op=read(),x=read(),y=read();
        if(op==1){
            v=read();
            add(x,y,v,1,n,1);
        }
        else{
            printf("%.1lf\n",query(x,y,1,n,1));
        }
    }
    return 0;
}