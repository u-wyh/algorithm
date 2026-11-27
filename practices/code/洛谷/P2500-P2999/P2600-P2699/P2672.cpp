// https://www.luogu.com.cn/problem/P2672
// 题意：死胡同中有 N 家住户，第 i 家距入口 S_i（不降），
// 推销疲劳 A_i，每走 1 米疲劳 1。
// 对 X = 1..N，求向 X 家推销并返回入口最多能积累的疲劳值。
// 输出 N 行，第 X 行对应 X 家的答案。
// 数据范围：1 <= N <= 10^5，0 <= S_i < 10^8，
// 1 <= A_i < 1000。
// 算法标签：贪心、排序、前缀和
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

int n,sum[100010],q[100010],h[100010];//n 疲劳前缀和 前i个最大值 后i个最大值
struct node{
    int s;//距离
    int a;//疲劳
}v[100010];

bool cmp(node x,node y){return x.a>y.a;}

int main()
{	scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&v[i].s);
    for(int i=1;i<=n;i++)scanf("%d",&v[i].a);
    sort(v+1,v+1+n,cmp);//按疲劳排序
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+v[i].a;
    for(int i=1;i<=n;i++)q[i]=max(q[i-1],2*v[i].s);//前i个最大值
    for(int i=n;i>=1;i--)h[i]=max(h[i+1],2*v[i].s+v[i].a);//后i个最大值
    for(int i=1;i<=n;i++)printf("%d\n",max(sum[i]+q[i],sum[i-1]+h[i]));
    return 0;
}
