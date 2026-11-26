// https://www.luogu.com.cn/problem/P3217
// 输入：第一行一个正整数 N，表示平面上点的个数。
// 输入：接下来 N 行，每行两个整数 X_i, Y_i，表示第 i 个点的坐标。
// 题意：从这 N 个点中挑选出 4 个点，要求存在一个矩形恰好以这 4 个点为四个顶点。
// 题意：求出能构成的最大矩形面积。
// 输出：输出一行一个非负整数，表示最大的矩形面积。
// 数据范围：N <= 1500
// 数据范围：-10^8 <= X_i, Y_i <= 10^8
// 数据范围：输入数据保证答案存在
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
