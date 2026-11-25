// https://www.luogu.com.cn/problem/P3222
#include<bits/stdc++.h>
using namespace std;
#define int long long
using i128 = __int128_t;
const int MAXN = 2e5+5;
const int INF = 1e9+7;

int n,lcnt;

struct Node{
    int x,y1,y2,id;
};
Node a[MAXN];

struct Line{
    int a,b,c;
};
Line l[MAXN],q[MAXN];

struct Point{
    i128 x,y,d;
};




bool cmp(Node a,Node b){
    return a.x>b.x;
}
// 两条有向直线方向向量的叉积
i128 cross(Line a,Line b){
    return (i128)a.a*b.b-(i128)a.b*b.a;
}

// 求两条直线的交点
Point getNode(Line a,Line b){
    i128 d=cross(a,b);
    i128 x=(i128)a.c*b.b-(i128)a.b*b.c;
    i128 y=(i128)a.a*b.c-(i128)a.c*b.a;

    if(d<0){
        x=-x;
        y=-y;
        d=-d;
    }
    return {x,y,d};
}

// 判断 b、c 的交点是否违反 a 的半平面限制
bool right(Line a,Line b,Line c){
    Point p=getNode(b,c);
    return (i128)a.a*p.x+(i128)a.b*p.y<(i128)a.c*p.d;
}

bool half_plane(){
    int h=1,t=0;

    for(int i=1;i<=lcnt;i++){
        while(t-h+1>=2 && right(l[i],q[t-1],q[t])){
            t--;
        }

        while(t-h+1>=2 && right(l[i],q[h],q[h+1])){
            h++;
        }

        if(t>=h && cross(q[t],l[i])==0){
            return false;
        }

        q[++t]=l[i];
    }

    while(t-h+1>=3 && right(q[h],q[t-1],q[t])){
        t--;
    }

    while(t-h+1>=3 && right(q[t],q[h],q[h+1])){
        h++;
    }

    int k=t-h+1;
    if(k<3){
        return false;
    }

    bool flag=false;

    for(int i=0;i<k;i++){
        Line a=q[h+i];
        Line b=q[h+(i+1)%k];

        // 有界交域的相邻方向夹角必须小于 PI
        if(cross(a,b)<=0){
            return false;
        }

        Point p=getNode(a,b);

        // 抛物线的二次项系数必须严格小于零
        if(p.x<0){
            flag=true;
        }
    }

    return flag;
    // return true;
}

bool check(int limit){
    lcnt=0;
    
    int lst=0;
    for(int i=1;i<=n;i++){
        if(a[i].id>limit){
            continue;
        }
        if(lst&&a[i].x==a[lst].x){
            continue;
        }
        lst=i;
        int x=a[i].x;
        l[++lcnt]={x*x,x,a[i].y1};
    }
    l[++lcnt]={-1,0,0};
    for(int i=1;i<=n;i++){
        if(a[i].id>limit){
            continue;
        }
        int x=a[i].x;
        l[++lcnt]={-x*x,-x,-a[i].y2};
    }

    return half_plane();
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y1>>a[i].y2;
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);

    int l=1,r=n,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    return 0;
}