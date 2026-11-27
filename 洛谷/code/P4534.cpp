// https://www.luogu.com.cn/problem/P4534
// 输入：第一行一个正整数 n，表示模板凸多边形的顶点数。
// 输入：接下来 n 行，按逆时针顺序每行两个实数 x, y，表示模板顶点坐标。
// 输入：接下来一行一个正整数 m，表示零件凸多边形的顶点数。
// 输入：接下来 m 行，按逆时针顺序每行两个实数 x, y，表示零件顶点坐标。
// 题意：零件完全固定在模板内部。
// 题意：除零件相邻两条边外，零件任意两条边的延长线交点都在模板之外。
// 题意：每次切割必须沿着零件某条边所在直线将当前模板一刀切成两部分，保留包含零件的那部分继续切割。
// 题意：每切一刀的费用等于该直线在当前模板上的切痕线段长度。
// 题意：求出完整切割出该零件所需的最小总费用。
// 输出：输出一个整数，表示最小总费用四舍五入到整数后的值。
// 数据范围：3 <= n, m <= 2000
// 数据范围：|x|, |y| <= 10^9
#include<bits/stdc++.h>
// 算法标签：计算几何、双指针、贪心
using namespace std;
#define int long long
const int MAXN = 4e3+5;
const long double eps = 1e-9L;
const long double INF = 1e30L;

int n,m;

struct Point{
    long double x,y;
};
Point p[MAXN],v[MAXN];

long double l[MAXN],r[MAXN],d[MAXN];
int in[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

long double cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

long double len(Point a){
    return sqrtl(a.x*a.x+a.y*a.y);
}

int nxt(int i){
    return i==n?1:i+1;
}

int prv(int i){
    return i==1?n:i-1;
}

long double side(int i,int j){
    return cross(v[i+1]-v[i],p[j]-v[i]);
}

// 判断零件边是否与模板边重合
bool border(int i,int j){
    Point a=v[i+1]-v[i];
    Point b=p[nxt(j)]-p[j];

    return fabsl(cross(a,b))<=eps*d[i]*len(b)
        && fabsl(cross(b,v[i]-p[j]))<=1e-7L*len(b);
}

// 计算点 a 到两直线交点的距离
long double getlen(Point a,Point dir,int j){
    Point e=p[nxt(j)]-p[j];
    return fabsl(cross(p[j]-a,e)/cross(dir,e))*len(dir);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }

    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>v[i].x>>v[i].y;
    }
    v[m+1]=v[1];

    int a=1,b=1,c=1;

    // 初始化叉积最小的模板顶点
    for(int j=2;j<=n;j++){
        if(side(1,j)<side(1,c)){
            c=j;
        }
    }

    for(int i=1;i<=m;i++){
        Point dir=v[i+1]-v[i];
        d[i]=len(dir);

        // 维护叉积最小的顶点
        while(cross(dir,p[nxt(c)]-p[c])<=0){
            c=nxt(c);
        }

        // 已经在模板边界上
        if(border(i,c)||border(i,prv(c))){
            d[i]=0;
            continue;
        }

        // 处理左边
        while(!(side(i,a)>=0&&side(i,nxt(a))<0)){
            a=nxt(a);
        }

        // 处理右边
        while(!(side(i,b)<0&&side(i,nxt(b))>=0)){
            b=nxt(b);
        }

        l[i]=getlen(v[i],dir,a);
        r[i]=getlen(v[i+1],dir,b);
    }

    long double ans=0,res=INF;

    for(int i=1;i<=m;i++){
        ans+=d[i];

        int j=i%m+1;

        if(r[i]<l[j]){
            ans+=r[i];
            in[j]++;
        }
        else{
            ans+=l[j];
            in[i]++;
        }

        res=min(res,fabsl(r[i]-l[j]));
    }

    bool flag=false;
    for(int i=1;i<=m;i++){
        if(in[i]==0){
            flag=true;
            break;
        }
    }

    if(!flag){
        ans+=res;
    }

    cout<<llroundl(ans)<<endl;
    return 0;
}