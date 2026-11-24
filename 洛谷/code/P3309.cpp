// https://www.luogu.com.cn/problem/P3309
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e5+5;
const int MAXV = MAXN<<2;
const int MAXM = MAXN*20;
const int INF = 4e18;

int n,sgn;

struct Point{
    int x,y;
};
Point p[MAXN];
Point temp[MAXN];
int cntp;

Point up[MAXM];
Point dn[MAXM];
int uplen,dnlen;
int stup[MAXV];
int enup[MAXV];
int stdn[MAXV];
int endn[MAXV];

int lastans;

inline int decode(int x) {   
    if(sgn==0){
        return x;
    } 
    return x ^ (lastans & 0x7fffffff);
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

int dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

void build(int l,int r,int rt){
    int cnt=r-l+1;
    for(int i=l;i<=r;i++){
        temp[i-l+1]=p[i];
    }
    sort(temp+1,temp+cnt+1,cmp);

    int len=0;
    for(int i=1;i<=cnt;i++){
        if(len==0||temp[i].x!=temp[len].x||temp[i].y!=temp[len].y){
            temp[++len]=temp[i];
        }
    }

    stup[rt]=uplen+1;
    for(int i=1;i<=len;i++){
        while(uplen>stup[rt] && cross(up[uplen]-up[uplen-1],temp[i]-up[uplen-1])>=0){
            uplen--;
        }
        up[++uplen]=temp[i];
    }
    enup[rt]=uplen;

    stdn[rt]=dnlen+1;
    for(int i=1;i<=len;i++){
        while(dnlen>stdn[rt]&& cross(dn[dnlen]-dn[dnlen-1],temp[i]-dn[dnlen-1])<=0){
            dnlen--;
        }
        dn[++dnlen]=temp[i];
    }
    endn[rt]=dnlen;
}

void update(int pos,int l,int r,int i){
    if(l==r){
        build(l,r,i);
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,l,mid,i<<1);
        }
        else{
            update(pos,mid+1,r,i<<1|1);
        }

        if(pos==r){
            build(l,r,i);
        }
    }
}

int find(Point *a,int l,int r,Point v){
    while(l<r){
        int mid=(l+r)>>1;

        if(dot(a[mid],v)<=dot(a[mid+1],v)){
            l=mid+1;
        }
        else{
            r=mid;
        }
    }

    return dot(a[l],v);
}

int calc(int rt,Point jobv){
    if(jobv.y>0){
        return find(up,stup[rt],enup[rt],jobv);
    }
    else{
        return find(dn,stdn[rt],endn[rt],jobv);
    }
}

int query(int jobl,int jobr,Point jobv,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return calc(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        int ans=-INF;
        if(jobl<=mid){
            ans=max(ans,query(jobl,jobr,jobv,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,query(jobl,jobr,jobv,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

signed main()
{
    char s;
    cin>>n>>s;
    sgn=(s!='E')?1:0;

    for(int i=1;i<=n;i++){
        char op;
        int x,y;
        cin>>op>>x>>y;
        x=decode(x);
        y=decode(y);
        Point v={x,y};
        if(op=='A'){
            p[++cntp]=v;
            update(cntp,1,n,1);
        }
        else{
            int l,r;
            cin>>l>>r;
            l=decode(l);
            r=decode(r);
            lastans=query(l,r,v,1,n,1);
            cout<<lastans<<endl;
        }
    }
    return 0;
}