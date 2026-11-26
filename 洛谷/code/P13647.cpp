// https://www.luogu.com.cn/problem/P13467
// 题意：统计 N*M 的 0/1 网格中全 0 且面积至少为 K 的子矩形个数。
// 输入：首行 N, M, K，后 N 行每行 M 个 0/1 整数（1 表示有洞）。
// 规则：沿网格线裁剪矩形，不能含 1 且格子总数 >= K。
// 输出：输出一行一个整数，表示合法子矩形总方案数。
// 数据范围：1 <= N, M <= 2000，1 <= K <= N*M，s_{xy} in {0, 1}。
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