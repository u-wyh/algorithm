// https://www.luogu.com.cn/problem/P4756
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,m;

struct Point{
    int x,y;
};
Point p[MAXN];

Point up[MAXN];
Point dn[MAXN];
int cntup;
int cntdn;

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

void Andrew(){
    for(int i=0;i<=n;i++){
        while(cntup>=2 && cross(up[cntup]-up[cntup-1],p[i]-up[cntup])>=0){
            cntup--;
        }
        up[++cntup]=p[i];

        while(cntdn>=2 && cross(dn[cntdn]-dn[cntdn-1],p[i]-dn[cntdn])<=0){
            cntdn--;
        }
        dn[++cntdn]=p[i];
    }
}

int calc(Point p,int x){
    return p.x*x+p.y;
}

int querymax(int x){
    int l=1,r=cntup;
    while(l<r){
        int mid=(l+r)>>1;
        if(calc(up[mid],x)<=calc(up[mid+1],x)){
            l=mid+1;
        }
        else{
            r=mid;
        }
    }
    return calc(up[l],x);
}

int querymin(int x){
    int l=1,r=cntdn;
    while(l<r){
        int mid=(l+r)>>1;
        if(calc(dn[mid],x)>calc(dn[mid+1],x)){
            l=mid+1;
        }
        else{
            r=mid;
        }
    }
    return calc(dn[l],x);
}

signed main()
{
    cin>>n>>m;

    p[0]={0,0};
    for(int i=1;i<=n;i++){
        int a;
        cin>>a;
        p[i]={i,a+p[i-1].y};
    }

    Andrew();

    int pre=0;
    while(m--){
        int x;
        cin>>x;
        x=(x+pre)%(4*n+1)-2*n;
        pre=querymax(x)-querymin(x);
        cout<<pre<<endl;
    }
    return 0;
}
