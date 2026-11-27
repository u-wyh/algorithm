// https://www.luogu.com.cn/problem/P6010
// 输入：第一行一个整数 N，表示世界数量。
// 输入：第二行 N 个空格分隔的整数 A_1, A_2, ..., A_N，表示时刻 0 各世界的 y 坐标（初始 y 坐标互不相同）。
// 输入：第三行 N 个空格分隔的整数 Q_1, Q_2, ..., Q_N（Q_i != i），表示第 i 个世界的奶牛想去的世界编号。
// 题意：世界 i 初始位于 x = i, y = A_i。
// 题意：从时刻 0 起，世界 i 沿着 y 轴负方向以每秒 i 个单位的速度下落（即时刻 t 的纵坐标为 A_i - i*t）。
// 题意：在任意时刻（可以是实数时刻），若两个世界的 y 坐标相同，它们同步，位于其中一个世界的奶牛可以瞬间传送到另一个世界。
// 题意：对每头奶牛，求其以最优方案从世界 i 到达世界 Q_i 所需的最短时间。
// 输出：输出 N 行，第 i 行表示奶牛 i 的最短时间。
// 输出：若能到达，输出最简分数 a/b（a, b 为互质正整数）；若不可到达，输出 -1。
// 数据范围：2 <= N <= 2 * 10^5
// 数据范围：1 <= A_i <= 10^9
// 算法标签：凸包、二分查找
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n;
struct Point{
    int x,y,id;
};
Point p[MAXN];
Point hull[MAXN];
int cnt;

int q[MAXN];
int id[MAXN];
int ansa[MAXN];
int ansb[MAXN];
int pos[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

bool cmp(Point a,Point b){
    return a.x<b.x;
}

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int query(Point p){
    int l=1,r=cnt;
    while(l<r){
        int mid=(l+r)>>1;
        if(cross(hull[mid+1]-hull[mid],p-hull[mid])>=0){
            l=mid+1;
        }
        else{
            r=mid;
        }
    }
    return l;
}

void solve(){
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<=n;i++){
        pos[p[i].id]=i;
    }
    cnt=0;
    for(int i=1;i<=n;i++){
        int s=p[i].id;
        int t=q[s];

        while(cnt>=2 && cross(hull[cnt]-hull[cnt-1],p[i]-hull[cnt-1])<=0){
            cnt--;
        }
        hull[++cnt]=p[i];

        if(p[pos[t]].x<=p[i].x){
            continue;
        }
        int res=query(p[pos[t]]);
        int a=p[pos[t]].x-hull[res].x;
        int b=p[pos[t]].y-hull[res].y;
        if(b<=0){
            continue;
        }
        int g=gcd(a,b);
        ansa[s]=a/g;
        ansb[s]=b/g;
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x;
        p[i].y=i;
        p[i].id=i;
    }
    for(int i=1;i<=n;i++){
        cin>>q[i];
    }

    solve();

    for(int i=1;i<=n;i++){
        p[i].x=-p[i].x;
        p[i].y=-p[i].y;
    }
    solve();

    for(int i=1;i<=n;i++){
        if(ansb[i]==0){
            cout<<-1<<endl;
        }
        else{
            cout<<ansa[i]<<'/'<<ansb[i]<<endl;
        }
    }
    return 0;
}
