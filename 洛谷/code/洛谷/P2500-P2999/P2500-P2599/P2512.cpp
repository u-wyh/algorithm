// https://www.luogu.com.cn/problem/P2512
// 题意：n 个小朋友围成一圈，每人有 a_i 个糖果，
// 每次可向左右传递 1 个糖果（代价 1）。
// 求使所有人糖果数相等的最小总代价。
// 输出最小代价。
// 数据范围：1 <= n <= 10^6，
// 1 <= a_i <= 1.5*10^9，sum(a_i) 是 n 的倍数。
// 算法标签：贪心、前缀和、中位数
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e6+5;

int n;
int nums[MAXN];
int all,b;
int c[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
        all+=nums[i];
    }
    b=all/n;
    c[1]=0;
    for(int i=2;i<=n;i++){
        c[i]=c[i-1]+(nums[i-1]-b);
    }
    sort(c+1,c+n+1);
    int t=c[(n+1)/2];
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=abs(c[i]-t);
    }
    cout<<ans<<endl;
    return 0;
}