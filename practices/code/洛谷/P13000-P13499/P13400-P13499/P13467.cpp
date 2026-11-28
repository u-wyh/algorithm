// https://www.luogu.com.cn/problem/P13467
// 题意：共 T 组数据，每组给 N, M, A。
// 求网格内三个整点 (x_i, y_i)，满足
// 0 <= x_i <= N 且 0 <= y_i <= M，
// 使三角形的面积恰好等于 A / 2。
// 输出：Case #tc: 接六个坐标或 IMPOSSIBLE。
// 数据范围：0 <= T <= 1000，1 <= A <= 10^8。
// 1 <= N, M <= 10^4。A > N * M 时无解。
// 难度评分：1600（洛谷分级换算）
// 算法标签：构造、计算几何
#include<bits/stdc++.h>
using namespace std;
#define int long long

int T,n,m,a;

signed main(){
    cin>>T;
    for(int tc=1;tc<=T;tc++){
        cin>>n>>m>>a;

        cout<<"Case #"<<tc<<": ";

        if(a>n*m){
            cout<<"IMPOSSIBLE\n";
            continue;
        }

        int y=(a+n-1)/n;
        int x=n*y-a;

        cout<<0<<" "<<0<<" ";
        cout<<n<<" "<<1<<" ";
        cout<<x<<" "<<y<<"\n";
    }
    return 0;
}