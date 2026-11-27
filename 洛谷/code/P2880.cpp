// https://www.luogu.com.cn/problem/P2880
// 题意：输入牛的数量 n、询问次数 q，n 头牛各自的身高 h_i，以及 q 个区间询问 [a, b]。
// 对每次询问，求队列中第 a 头牛到第 b 头牛这一连续区间内最高身高与最低身高的差值。
// 依次回答全部 q 个询问。
// 输出共 q 行，每行一个整数表示对应区间内最高和最低牛的身高差。
// 数据范围：对于 100% 的数据，1 <= n <= 5*10^4，1 <= q <= 1.8*10^5
// 1 <= h_i <= 10^6（1 <= i <= n）。
#include<bits/stdc++.h>
// 算法标签：ST表、RMQ
using namespace std;
const int MAXN = 50010;

int n,q,h[MAXN],log_2[MAXN],rmax[MAXN][18],rmin[MAXN][18];

void init(){
    for(int i=1;i<=n;i++)
        rmax[i][0]=rmin[i][0]=h[i];
    for(int j=1;(1<<j)<=n;j++){
        for(int i=1;i<=n-(1<<j)+1;i++){
            rmax[i][j]=max(rmax[i][j-1],rmax[i+(1<<j-1)][j-1]);
            rmin[i][j]=min(rmin[i][j-1],rmin[i+(1<<j-1)][j-1]);
        }
    }
}

int query_max(int A,int B){
    int x=log_2[B-A+1];
    return max(rmax[A][x],rmax[B-(1<<x)+1][x]);
}

int query_min(int A,int B){
    int x=log_2[B-A+1];
    return min(rmin[A][x],rmin[B-(1<<x)+1][x]);
}

int main()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++)
        cin>>h[i];
    for(int i=2;i<=n;i++)
        log_2[i]=log_2[i>>1]+1;
    init();
    while(q--){
        int A,B;
        cin>>A>>B;
        cout<<query_max(A,B)-query_min(A,B)<<endl;
    }
    return 0;
}
