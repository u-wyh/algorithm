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
