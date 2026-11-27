// https://www.luogu.com.cn/problem/P5545
// 题意：x 轴上方有 D 个敌人，下方有 S 个发射源和 T 个激光塔，若存在两塔相连的线段与某发射源到某敌人的线段相交则可发起超级射线
// 求合法四元组 {T_i, T_j, S_k, D_l} 数量。
// 输入 D, S, T 及三类点的坐标；输出合法方案总数。
// 数据范围：1 <= D, S, T <= 800，dy_i > 0，sy_i, ty_i < 0，坐标绝对值不超过 10^9，无重点及三点共线。
#include<bits/stdc++.h>
// 算法标签：计算几何、极角排序、双指针
using namespace std;
#define int long long
using i128 = __int128_t;
const int MAXN = 805;
const int MAXM = 1605;

int n,m,k;
int ans;

struct Point{
    int x,y;
    int op;
};
Point d[MAXN];
Point s[MAXN];
Point t[MAXN];
Point p[MAXM<<1];
int pred[MAXM<<1];
int pret[MAXM<<1];
int sumd[MAXM<<1];

Point operator-(Point a,Point b){
    return {(i128)a.x-b.x,a.y-b.y,a.op};
}

int half(Point a){
    return (a.y>0 || (a.y==0&&a.x>0))?0:1;
}

i128 cross(Point a,Point b){
    return (i128)a.x*b.y-(i128)a.y*b.x;
}

bool cmp(Point a,Point b){
    int ha=half(a),hb=half(b);
    if(ha!=hb){
        return ha<hb;
    }
    return cross(a,b)>0;
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>d[i].x>>d[i].y;
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>s[i].x>>s[i].y;
    }
    cin>>k;
    for(int i=1;i<=k;i++){
        cin>>t[i].x>>t[i].y;
        t[i].op=1;
    }

    for(int u=1;u<=m;u++){
        int cnt=0;
        for(int i=1;i<=n;i++){
            p[++cnt]=d[i]-s[u];
        }
        for(int i=1;i<=k;i++){
            p[++cnt]=t[i]-s[u];
        }
        sort(p+1,p+cnt+1,cmp);

        for(int i=1;i<=cnt;i++){
            p[i+cnt]=p[i];
        }

        for(int i=1;i<=cnt*2;i++){
            pred[i]=pred[i-1]+1-p[i].op;
            pret[i]=pret[i-1]+p[i].op;
            sumd[i]=sumd[i-1]+((p[i].op==1)?pred[i]:0);
        }

        int r=1;
        for(int i=1;i<=cnt;i++){
            r=max(r,i);
            while((r+1)<cnt+i && cross(p[i],p[r+1])>0){
                r++;
            }
            if(p[i].op==1){
                ans+=sumd[r]-sumd[i]-(pret[r]-pret[i])*pred[i];
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}