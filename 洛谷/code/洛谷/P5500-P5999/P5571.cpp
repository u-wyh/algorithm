// https://www.luogu.com.cn/problem/P5571
// 题意：平面上有 n 个坐标互异的高塔，
// 任选 3 个高塔组成三角形（允许面积为 0），求第 k 小三角形面积的 2 倍。
// 输入 n, k 及各高塔坐标；输出第 k 小面积的 2 倍（必为整数）。
// 数据范围：n <= 800，1 <= k <= C(n, 3)，
// 1 <= x_i, y_i <= 10^6。
// 算法标签：计算几何、枚举、值域分块
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 805;
const int MAXB = 1<<20;

int n,k;
struct Point{
    int x,y;
};
Point p[MAXN];
int cnt[MAXB];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

int cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

signed main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>p[i].x>>p[i].y;
    }

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=j+1;k<=n;k++){
                int s=abs(cross(p[j]-p[i],p[k]-p[i]));
                cnt[s>>20]++;
            }
        }
    }

    int id=0;
    while(k>cnt[id]){
        k-=cnt[id];
        id++;
    }

    memset(cnt,0,sizeof(cnt));
    
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=j+1;k<=n;k++){
                int s=abs(cross(p[j]-p[i],p[k]-p[i]));
                if((s>>20)==id){
                    cnt[s&(MAXB-1)]++;
                }
            }
        }
    }

    int pos=0;
    while(k>cnt[pos]){
        k-=cnt[pos];
        pos++;
    }

    cout<<id*MAXB+pos<<'\n';
    return 0;
}