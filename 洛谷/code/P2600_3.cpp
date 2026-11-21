// https://www.luogu.com.cn/problem/P2600
#include<bits/stdc++.h>
using namespace std;
#define int long long
using i128=__int128_t;

const int MAXN=305;
const long double INF=1e100L;

int n;
struct Point{
    int x,y;
};
Point p[MAXN];

int dx[MAXN],dy[MAXN],c[MAXN];
int ord[MAXN],st[MAXN],top;

long double xs[MAXN*2];
int cntx;
long double ans=INF;

i128 getA(int i,int j){
    return (i128)c[i]*dx[j]-(i128)c[j]*dx[i];
}

i128 getB(int i,int j){
    return (i128)dy[j]*dx[i]-(i128)dy[i]*dx[j];
}

long double getx(int i,int j){
    return (long double)getA(i,j)/getB(i,j);
}

bool cmp(int i,int j){
    i128 v=(i128)dy[i]*dx[j]-(i128)dy[j]*dx[i];
    if(v!=0) return v<0;
    return (i128)c[i]*dx[j]>(i128)c[j]*dx[i];
}

bool check(int i,int j,int k){
    return getA(i,j)*getB(j,k)>=getA(j,k)*getB(i,j);
}

long double height(int i,long double x){
    return p[i].y+(x-p[i].x)*(long double)dy[i]/dx[i];
}

void compute(){
    sort(ord+1,ord+n,cmp);

    // 单调栈构造上包络线
    for(int i=1;i<n;i++){
        int id=ord[i];

        if(top && (i128)dy[id]*dx[st[top]]==
                  (i128)dy[st[top]]*dx[id]){
            continue;
        }

        while(top>=2 && check(st[top-1],st[top],id)){
            top--;
        }
        st[++top]=id;
    }

    // 收集原山体顶点
    for(int i=1;i<=n;i++){
        xs[++cntx]=p[i].x;
    }

    // 收集上包络线折点
    for(int i=1;i<top;i++){
        long double x=getx(st[i],st[i+1]);
        if(x>=p[1].x && x<=p[n].x){
            xs[++cntx]=x;
        }
    }

    sort(xs+1,xs+cntx+1);

    // 双指针扫描上下两条折线
    int j=1,r=1;

    for(int i=1;i<=cntx;i++){
        long double x=xs[i];

        while(j<n-1 && x>p[j+1].x){
            j++;
        }

        while(r<top && x>=getx(st[r],st[r+1])){
            r++;
        }

        ans=min(ans,height(st[r],x)-height(j,x));
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i].x;
    for(int i=1;i<=n;i++) cin>>p[i].y;

    for(int i=1;i<n;i++){
        dx[i]=p[i+1].x-p[i].x;
        dy[i]=p[i+1].y-p[i].y;
        c[i]=p[i].y*dx[i]-p[i].x*dy[i];
        ord[i]=i;
    }

    compute();

    cout<<fixed<<setprecision(3)
        <<max(0.0L,ans)<<'\n';

    return 0;
}
