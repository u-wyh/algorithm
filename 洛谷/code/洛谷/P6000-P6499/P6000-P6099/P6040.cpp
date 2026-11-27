// https://www.luogu.com.cn/problem/P6040
// 题意：有 n 个学生排成一列，解决第 i 个学生的问题需花费 a_i 精力；
// 从第 p 个跳到第 q 个（1 <= q - p <= x）需额外花费
// k + (q - p - 1) * d 精力。
// 求从第 1 个出发解决第 n
// 个学生问题所需的最小总精力
// （tp=1 时 a 由 Seed 与给定 rnd() 生成）。
// 数据范围：1 <= n <= 10^7，
// 0 <= k, d, a_i <= 10^9，1 <= x <= n - 1。
// 算法标签：动态规划、单调队列
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e7+5;

int n,m,d,x,tp;
int arr[MAXN],Seed;
int f[MAXN];
int q[MAXN],head,tail;

inline int rnd () {
	static const int MOD = 1e9;
	return Seed = ( 1LL * Seed * 0x66CCFF % MOD + 20120712 ) % MOD;
}

signed main()
{
    cin>>n>>m>>d>>x>>tp;
    if(tp==0){
        for(int i=1;i<=n;i++){
            cin>>arr[i];
        }
    }else{
        cin>>Seed;
        for(int i=1;i<=n;i++){
            arr[i]=rnd();
            //cout<<arr[i]<<' ';
        }
    }
    for(int i=1;i<=n;i++){
        f[i]=1e16;
    }
    f[1]=arr[1];
    head=1,tail=2;
    q[head]=1;
    f[1]=f[1]-2*d;
    for(int i=2;i<=n;i++){
        while(head<tail&&q[head]<i-x){
            head++;
        }
        while(head<tail&&f[q[tail-1]]>=f[i-1]){
            tail--;
        }
        q[tail++]=i-1;
        if(i==n)
            f[i]=f[q[head]]+arr[i]+m+i*d;
        else
            f[i]=f[q[head]]+arr[i]+m+i*d-(i+1)*d;
    }
    cout<<f[n]<<endl;
    return 0;
}
