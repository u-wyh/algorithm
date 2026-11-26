// https://www.luogu.com.cn/problem/P3291
// 输入：第一行一个整数 n，表示妖怪数量。
// 输入：接下来 n 行，每行两个整数 atk_i, dnf_i，表示第 i 只妖怪的基础攻击力和防御力。
// 题意：环境 (a,b) 由两个正实数 a, b 定义。
// 题意：在环境 (a,b) 中，妖怪可以取任意实数 k，把属性调整为 (atk - k*a, dnf + k*b)，但必须始终保持 atk >= 0 且 dnf >= 0。
// 题意：某妖怪在环境 (a,b) 中的战斗力定义为它在该环境下能达到的最大攻击力与最大防御力之和。
// 题意：求在最不利的环境（即存在正实数 a, b 使 n 只妖怪中战斗力最大值最小）下，最强妖怪的最低战斗力值。
// 输出：输出一行一个实数，保留 4 位小数。
// 数据范围：1 <= n <= 10^6
// 数据范围：0 < atk_i, dnf_i <= 10^8
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n,cnt;
struct Point{
    int x,y;
};
Point p[MAXN];
Point q[MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}

long double calc(Point p,long double t){
    return p.x+p.y+p.y*t+p.x/t;
}

long double gett(Point a,Point b){
    return (long double)(a.x-b.x)/(b.y-a.y);
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }
    sort(p+1,p+n+1,cmp);

    for(int i=n;i>=1;i--){
        if(cnt&&p[i].y<=q[cnt].y){
            continue;
        }

        while(cnt>=2 && cross(q[cnt]-q[cnt-1],p[i]-q[cnt])<=0){
            cnt--;
        }
        q[++cnt]=p[i];
    }

    long double ans=1e100l;
    for(int i=1;i<=cnt;i++){
        long double t=sqrtl((long double)q[i].x/q[i].y);

        if(i>1){
            t=max(t,gett(q[i-1],q[i]));
        }
        if(i<cnt){
            t=min(t,gett(q[i],q[i+1]));
        }
        ans=min(ans,calc(q[i],t));
    }

    cout<<fixed<<setprecision(4)<<ans<<endl;
    return 0;
}