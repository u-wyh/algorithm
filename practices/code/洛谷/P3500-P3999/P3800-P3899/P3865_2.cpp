// https://www.luogu.com.cn/problem/P3865
// 题意：第一行输入数列长度 N 和询问数 M，
// 第二行输入 N 个整数 a_1..a_N，
// 随后 M 行输入查询区间 [l_i, r_i]。
// 对每次询问求出区间 [l_i, r_i] 内所有数字的最大值。
// 输出 M 行，每行一个整数表示对应区间最大值。
// 数据范围：对于 100% 的数据，1 <= N <= 10^5，
// 1 <= M <= 2 * 10^6，0 <= a_i <= 10^9
// 1 <= l_i <= r_i <= N（时限 0.8s）。
// 算法标签：ST表
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int f[100001][40],a,x,LC,n,m,p,len,l,r;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a);
        f[i][0]=a;
    }
    LC=(int)(log(n)/log(2));
    for(int j=1;j<=LC;j++)
        for (int i=1;i<=n-(1<<j)+1;i++)
    		f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&l,&r);
  		p=(int)(log(r-l+1)/log(2));
        printf("%d\n",max(f[l][p],f[r-(1<<p)+1][p]));
    }
    return 0;
}
