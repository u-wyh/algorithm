// https://www.luogu.com.cn/problem/P7028
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e4+5;
const int MAXB = 305;
const int INF = 4e18;

int n,m;
int val[MAXN];
int P,N;

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];
int sumx[MAXB];
int sumy[MAXB];

struct Point{
    int x,y,id;
};
Point hull[MAXB][MAXB];
int cnt[MAXB];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

int calc(Point p){
    return N*p.x-P*p.y;
}

void build(int b){
    cnt[b]=0;
    int x=0,y=0;
    for(int i=bl[b];i<=br[b];i++){
        if(val[i]>0){
            x+=val[i];
        }
        else{
            y-=val[i];
        }

        Point p={x,y,i};
        if(cnt[b]&&hull[b][cnt[b]].x==p.x){
            continue;
        }
        while(cnt[b]>=2 && cross(hull[b][cnt[b]]-hull[b][cnt[b]-1],p-hull[b][cnt[b]-1])<=0){
            cnt[b]--;
        }
        hull[b][++cnt[b]]=p;
    }
    sumx[b]=x;
    sumy[b]=y;
}

Point query(int b){
    int l=1,r=cnt[b];
    while(l<r){
        int mid=(l+r)>>1;
        if(calc(hull[b][mid])<calc(hull[b][mid+1])){
            l=mid+1;
        }
        else{
            r=mid;
        }
    }
    return hull[b][l];
}

int solve(){
    int x=0,y=0;
    int maxx=-INF,ans=0;
    for(int b=1;b<=bnum;b++){
        Point p=query(b);
        int res=calc(p)+N*x-P*y;
        if(res>maxx){
            maxx=res;
            ans=p.id;
        }
        x+=sumx[b];
        y+=sumy[b];
    }
    return ans;
}

void update(int p,int v){
    if(val[p]>0){
        P-=val[p];
    }
    else{
        N+=val[p];
    }
    val[p]=v;
    if(val[p]>0){
        P+=val[p];
    }
    else{
        N-=val[p];
    }
    build(bi[p]);
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        if(val[i]>0){
            P+=val[i];
        }
        else{
            N-=val[i];
        }
    }

    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int b=1;b<=bnum;b++){
        bl[b]=(b-1)*blen+1;
        br[b]=min(n,b*blen);
        build(b);
    }

    cout<<solve()<<endl;
    while(m--){
        int p,v;
        cin>>p>>v;
        update(p,v);
        cout<<solve()<<endl;
    }
    return 0;
}
