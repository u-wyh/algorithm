// https://www.luogu.com.cn/problem/P4049
// 题意：第一行输入原材料种数 m 和用户需求合金种数 n；
// 接下来 m 行输入每种原材料的铁铝锡比重 a_i, b_i, c_i，再接下来 n 行输入每种需求合金的比重 d_i, e_i, f_i。
// 将所购原材料按非负比例熔合，要求能同时配出全部 n 种需求合金，求最少需订购的原材料种类数。
// 输出最少原材料种数；若无解输出 -1。
// 数据范围：对于全部测试点，1 <= m, n <= 500
// 0 <= a_i, b_i, c_i, d_i, e_i, f_i <= 1 且 a_i + b_i + c_i = 1
// d_i + e_i + f_i = 1
// 小数点后最多 6 位。
#include<bits/stdc++.h>
// 算法标签：计算几何、Floyd
using namespace std;
#define int long long
const int MAXN = 505;
const int MAXV = 1000000;
const int INF = 1e9;

int n,m;
struct Point{
    int x,y;
};
Point p[MAXN];
Point v[MAXN];

int dis[MAXN][MAXN];
int f[MAXN][MAXN];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

int dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

bool check(int s,int t){
    for(int i=1;i<=m;i++){
        int val=cross(p[t]-p[s],v[i]-p[s]);

        if(val<0){
            return false;
        }

        // 共线时，目标点必须在线段 st 上
        if(val==0&&dot(v[i]-p[s],v[i]-p[t])>0){
            return false;
        }
    }
    return true;
}

void floyd(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(f[i][j]){
                dis[i][j]=1;
            }
            else{
                dis[i][j]=INF;
            }
        }
    }

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
            }
        }
    }
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        double x,y,z;
        cin>>x>>y>>z;
        p[i]={(int)MAXV*x,(int)MAXV*y};
    }
    for(int i=1;i<=m;i++){
        double x,y,z;
        cin>>x>>y>>z;
        v[i]={(int)MAXV*x,(int)MAXV*y};
    }

    for(int i=1;i<=n;i++){
        bool flag=true;
        for(int j=1;j<=m;j++){
            if(p[i].x!=v[j].x||p[i].y!=v[j].y){
                flag=false;
                break;
            }
        }
        if(flag){
            cout<<1<<endl;
            return 0;
        }
    }
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i!=j){
                if(check(i,j)){
                    f[i][j]=1;
                }
            }
        }
    }

    floyd();

    int ans=INF;
    for(int i=1;i<=n;i++){
        ans=min(ans,dis[i][i]);
    }

    if(ans>n){
        cout<<-1<<endl;
    }
    else{
        cout<<ans<<endl;
    }
    return 0;
}