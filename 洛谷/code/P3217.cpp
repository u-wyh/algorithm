// https://www.luogu.com.cn/problem/P3217
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1505;
const int MAXM = MAXN*MAXN/2;

int n,cnt,ans;

struct Point{
    int x,y;
};
Point p[MAXN];

struct Line{
    int x,y,d;
    Point v;
};
Line l[MAXM];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

int dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

bool cmp(Line a,Line b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    if(a.y!=b.y){
        return a.y<b.y;
    }
    if(a.d!=b.d){
        return a.d<b.d;
    }
    return cross(a.v,b.v)>0;
}

bool same(Line a,Line b){
    return (a.x==b.x)&&(a.y==b.y)&&(a.d==b.d);
}

void solve(int lt,int rt){
    int j=lt+1;
    for(int i=lt;i<=rt;i++){
        j=max(i+1,j);

        while(j<=rt && dot(l[i].v,l[j].v)>0){
            j++;
        }

        if(j<=rt){
            ans=max(ans,abs(cross(l[i].v,l[j].v))/2);
        }
        if(j-1>i){
            ans=max(ans,abs(cross(l[i].v,l[j-1].v))/2);
        }
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            Point v=p[j]-p[i];

            if(v.x==0&&v.y==0){
                continue;
            }

            if(v.y<0||(v.y==0&&v.x<0)){
                v.x=-v.x;
                v.y=-v.y;
            }

            l[++cnt]={p[i].x+p[j].x,p[i].y+p[j].y,dot(v,v),v};
        }
    }

    sort(l+1,l+cnt+1,cmp);

    for(int i=1,j=1;i<=cnt;i++){
        j=i+1;
        while(j<=cnt && same(l[i],l[j])){
            j++;
        }
        solve(i,j-1);
    }

    cout<<ans<<endl;
    return 0;
}
