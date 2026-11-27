// https://www.luogu.com.cn/problem/P7164
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 2e5+5;
const int MAXV = MAXN<<2;
const int MAXM = MAXN*20;

int n,ans;
int a[MAXN];
int b[MAXN];
int mina[MAXN];
int minb[MAXN];

struct Point{
    int x,y;
};
Point hull[MAXM];
int cnt;

int st[MAXV];
int cur[MAXV];

void same(int l,int mid,int r){
    int j=mid;
    for(int i=mid;i>=l;i--){
        while(j<r && mina[j+1]>=mina[i]&&minb[j+1]>=minb[i]){
            j++;
        }
        if(j>mid){
            ans=max(ans,(j-i+1)*mina[i]*minb[i]);
        }
    }

    int i=mid+1;
    for(int j=mid+1;j<=r;j++){
        while(i>l && mina[i-1]>=mina[j]&&minb[i-1]>=minb[j]){
            i--;
        }
        if(i<=mid){
            ans=max(ans,(j-i+1)*mina[j]*minb[j]);
        }
    }
}

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

int calc(Point p,int k){
    return k*p.x+p.y;
}

void build(int l,int r,int *y,int u){
    st[u]=cnt+1;
    for(int i=l;i<=r;i++){
        Point p={y[i],i*y[i]};
        if(cnt>=st[u]&&hull[cnt].x==p.x){
            cnt--;
        }
        while(cnt>st[u]&&cross(hull[cnt]-hull[cnt-1],p-hull[cnt])<=0){
            cnt--;
        }
        hull[++cnt]=p;
    }
    cur[u]=cnt;
    if(l==r){
        return ;
    }
    int mid=(l+r)>>1;
    build(l,mid,y,u<<1);
    build(mid+1,r,y,u<<1|1);
}

int query(int jobl,int jobr,int jobk,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        while(cur[i]>st[i]&&calc(hull[cur[i]-1],jobk)>=calc(hull[cur[i]],jobk)){
            cur[i]--;
        }
        return calc(hull[cur[i]],jobk);
    }
    int mid=(l+r)>>1;
    int res=0;
    if(jobl<=mid){
        res=max(res,query(jobl,jobr,jobk,l,mid,i<<1));
    }
    if(jobr>mid){
        res=max(res,query(jobl,jobr,jobk,mid+1,r,i<<1|1));
    }
    return res;
}

void mixed(int l,int mid,int r,int *x,int *y){
    cnt=0;
    int p=mid+1,q=mid;
    build(mid+1,r,y,1);
    for(int i=mid;i>=l;i--){
        while(p<=r && y[p]>y[i]){
            p++;
        }
        while(q<r && x[q+1]>=x[i]){
            q++;
        }

        if(p<=q){
            int res=query(p,q,(1-i),mid+1,r,1);
            ans=max(ans,res*x[i]);
        }
    }
}

void solve(int l,int r){
    if(l==r){
        ans=max(ans,a[l]*b[l]);
        return ;
    }

    int mid=(l+r)>>1;
    solve(l,mid);
    solve(mid+1,r);

    mina[mid]=a[mid];
    minb[mid]=b[mid];
    for(int i=mid-1;i>=l;i--){
        mina[i]=min(mina[i+1],a[i]);
        minb[i]=min(minb[i+1],b[i]);
    }

    mina[mid+1]=a[mid+1];
    minb[mid+1]=b[mid+1];
    for(int i=mid+2;i<=r;i++){
        mina[i]=min(mina[i-1],a[i]);
        minb[i]=min(minb[i-1],b[i]);
    }

    same(l,mid,r);
    mixed(l,mid,r,mina,minb);
    mixed(l,mid,r,minb,mina);
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    solve(1,n);
    cout<<ans<<endl;
    return 0;
}
