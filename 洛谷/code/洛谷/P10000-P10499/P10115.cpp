// https://www.luogu.com.cn/problem/P10115
// 题意：给长为 n 的括号串和数列 a，把整个串切成若干连续非空段。
// 若一段 [l,r] 自己是合法括号串，得分是 a[r]-a[l]，
// 否则得 0 分。
// 输出最大总分。
// 数据范围：n ≤ 3 × 10^6，1 ≤ a[i] ≤ 10^9。
// 算法标签：动态规划、栈

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+5,inf=1e18;
int n,a[N],lst[N],r;
int f[N],st[N],c[N];
bool b[N];
string S;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>S;
    for(int i=1; i<=n; ++i)
        cin>>a[i],b[i]=(S[i-1]=='(');
    for(int i=1; i<=n; ++i)
        if(!b[i]&&r)lst[i]=st[r--];
        else if(b[i])st[++r]=i;
    for(int i=0; i<=n; ++i)
        f[i]=c[i]=-inf;f[0]=0;
    for(int i=1; i<=n; ++i){
        f[i]=f[i-1];
        if(lst[i]){
            c[i]=max(c[lst[i]-1],f[lst[i]-1]-a[lst[i]]);
            f[i]=max(c[i]+a[i],f[i]);
        }
    }cout<<f[n];
    return 0;
}
