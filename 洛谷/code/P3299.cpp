// https://www.luogu.com.cn/problem/P3299
// 题意：
// 共有 n 关，给定关数 n、僵尸间距 d，及每关参数 A_i, X_i。
// 第 i 关队列共有 i 只僵尸，第 1 只血量 A_i 距房 X_i，其余依次隔 d 米排后。
// 所有僵尸速度为 1m/s 同时前进，植物仅攻击最前活僵尸（子弹飞行耗时为 0）。
// 每关需选最小攻击力 y_i 使没有任何僵尸能到达房子。
// 输出 n 关最小攻击力之和，四舍五入到个位整数。
// 数据范围：
// 1 <= n <= 10^5
// 1 <= d, X_i, A_i <= 10^{12}
#include<bits/stdc++.h>
using namespace std;
#define int long long
using i128 = __int128_t;
const int MAXN = 1e5+5;

int n,d;
int sum[MAXN];

struct Point{
    int x,y;
};
Point sta[MAXN];
int top;

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

i128 cross(Point a,Point b){
    return (i128)a.x*b.y-(i128)a.y*b.x;
}

// 计算两点之间的斜率
long double slope(Point a,Point b){
    return (long double)(b.y-a.y)/(b.x-a.x);
}

// 单调栈维护下凸包
void insert(Point p){
    while(top>=2&&cross(sta[top]-sta[top-1],p-sta[top-1])<=0){
        top--;
    }
    sta[++top]=p;
}

// 在下凸包上二分查询与 p 连线的最大斜率
long double query(Point p){
    int l=1,r=top;
    while(l<r){
        int mid=(l+r)>>1;

        // 若下一个点与 p 连线的斜率更大，则向右寻找
        if(cross(sta[mid+1]-sta[mid],p-sta[mid])>=0){
            l=mid+1;
        }
        else{
            r=mid;
        }
    }
    return slope(sta[l],p);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>d;

    long double ans=0;

    for(int i=1;i<=n;i++){
        int a,x;
        cin>>a>>x;
        sum[i]=sum[i-1]+a;

        // 将当前候选点加入下凸包
        Point p={i*d,sum[i-1]};
        insert(p);

        // 构造当前关卡的查询点
        Point q={i*d+x,sum[i]};

        // 累加当前关卡的最小攻击力
        ans+=query(q);
    }

    cout<<fixed<<setprecision(0)<<roundl(ans)<<'\n';

    return 0;
}