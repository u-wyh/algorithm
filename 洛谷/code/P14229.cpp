// https://www.luogu.com.cn/problem/P14229
#include<bits/stdc++.h>
using namespace std;
#define int long long 
using i128 = __int128_t;
const int MAXN = 1e5+5;

int n;
struct Point{
    int x,y;
};
Point p[MAXN<<1];
Point C;
int r;
i128 pre[MAXN<<1];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

i128 cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

i128 dot(Point a,Point b){
    return (i128)a.x*b.x+(i128)a.y*b.y;
}

bool check(int i,int j){
    Point a=p[j]-p[i];
    Point b=C-p[i];

    i128 c=cross(a,b);
    if(c<=0) return false;

    return c*c>=(i128)r*r*dot(a,a);
}

void print(i128 x){
    if(x>=10) print(x/10);
    putchar(x%10+'0');
}

void solve(){
    cin>>n;
    cin>>C.x>>C.y>>r;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
        p[n+i]=p[i];
    }

    for(int i=1;i<2*n;i++){
        pre[i+1]=pre[i]+cross(p[i],p[i+1]);
    }

    int j=2;
    i128 ans=0;
    for(int i=1;i<=n;i++){
        j=max(j,1+i);
        while(j+1<i+n &&check(i,j+1)){
            j++;
        }
        if(check(i,j)){
            i128 sum=pre[j]-pre[i]+cross(p[j],p[i]);
            ans=max(ans,sum);
        }
    }
    print(ans);
    cout<<endl;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}