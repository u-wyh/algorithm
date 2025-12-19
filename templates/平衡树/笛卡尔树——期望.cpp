// 砖块消除
// 给定一个长度为n的数组arr，arr[i]为i号砖块的重量
// 选择一个没有消除的砖块进行消除，收益为被消除砖块联通区域的重量之和，比如arr = {3,5,2,1}
// 如果先消除5，那么获得3+5+2+1的收益，arr = {3,X,2,1}
// 如果再消除1，那么获得2+1的收益，arr = {3,X,2,X}
// 如果再消除2，那么获得2的收益，arr = {3,X,X,X}
// 如果再消除3，那么获得3的收益，arr = {X,X,X,X}
// 一共有n!种消除方案，返回所有消除方案的收益总和，答案对 1000000007 取模
// 1 <= n <= 10^5    1 <= arr[i] <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/AT_agc028_b
// 测试链接 : https://atcoder.jp/contests/agc028/tasks/agc028_b
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
// 这道题没有建立笛卡尔树  但是实际上是通过笛卡尔树来进行分析
// 题目要求我们算出所有的方案的答案  其实这种类型的问题可以直接想到一定是和期望相关的
// 每一种方案都对应一种笛卡尔树的结构  在给定一个树的情况下  计算答案实际就是再求每个节点的贡献次数
// 每个节点的贡献次数就是他在这棵树中的深度*自身的权值  我们可以算出每个节点的期望深度  然后乘上n!
// 期望深度=期望祖先节点的数量+1  那么我们求出每个节点的期望祖先节点数量
// 对于节点i而言  祖先节点可能是 1~i-1   i+1~n  对于x（属于1~i-1）  计算他可以是i的祖先的可能性
// ((i-x)!*其余随便填)/((i-x+1)!*其余随便填)   如果x是i的祖先 那么他必须在x+1 x+2  x+3  i之前填好
// 有效方案就是((i-x)!*其余随便填) 表示 x+1 x+2  x+3  i它们的位置随意  剩余的数字（不包括x）随便填的方案
// ((i-x+1)!*其余随便填) 总方案可以写成这个形式 即x~i随便填  剩下的也随便填
// 那么求出i的期望是 1/(i-x+1) x从1到i-1  +  1/(x-i+1) x从i+1到n
// 我们令f(i)表示1+1/2+1/3+ +1/i  那么i的期望就是  f[i]+f[n-i+1]-1
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1e5+5;

int n;
int inv[MAXN];
int sum[MAXN];
int val[MAXN];

void build(){
    inv[1]=1;
    for(int i=2;i<=n;i++){
        inv[i]=(MOD-inv[MOD%i]*(MOD/i)%MOD)%MOD;
    }
    for(int i=1;i<=n;i++){
        sum[i]=(sum[i-1]+inv[i])%MOD;
    }
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    build();
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=(ans+(sum[i]+sum[n-i+1]-1)*val[i]%MOD)%MOD;
    }
    for(int i=1;i<=n;i++){
        ans=(ans*i)%MOD;
    }
    cout<<ans<<endl;
    return 0;
}