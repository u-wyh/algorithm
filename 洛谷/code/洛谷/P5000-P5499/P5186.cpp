// https://www.luogu.com.cn/problem/P5186
// 题意：N 块宽 1 高 h_i 的木板排成一行，
// 每次用宽 X 的滚筒从底往上刷连续 X 块木板至其中最低高度；
// 求必须手涂的最小剩余面积，以及在此前提下最少的滚筒刷次数。
// 数据范围：1 <= N <= 10^6，1 <= X <= 10^5，
// 1 <= h_i <= 10^6。
// 算法标签：单调队列、贪心
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e6+5;
int maxc[N],h[N],q[N],a[N];
int len,n,ans,cnt,head,tail;

inline int read()
{
    int a=0,f=1; char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1; c=getchar();}
    while (c>='0'&&c<='9') {a=a*10+c-'0'; c=getchar();}
    return a*f;
}//快读比 scanf 好打多了

signed main()
{
	n=read(),len=read();
	for(int i=1;i<=n;++i)
        a[i]=read();
	head=1,tail=0;
	for(int i=1;i<=n;++i){
		while(head<=tail&&q[head]<=i-len)
            head++;
		while(head<=tail&&a[q[tail]]>a[i])
            tail--;
		tail++;
		q[tail]=i;
		if(i-len+1>=0)
            h[i-len+1]=a[q[head]];
	}
	head=1,tail=0;
	for(int i=1;i<=n;++i)
	{
		while(head<=tail&&q[head]<=i-len)
            head++;
		while(head<=tail&&h[q[tail]]<h[i])
            tail--;
		tail++;
		q[tail]=i;
		maxc[i]=h[q[head]];
	}
	for(int i=1;i<=n;++i)
		ans+=a[i]-maxc[i];
	printf("%lld\n",ans);
	int hnow=0,bj=0;
	for(int i=1;i<=n;++i){
		if(maxc[i]!=hnow||bj<i){
			hnow=maxc[i];
			bj=i+len-1;
			cnt++;
		}
	}
	printf("%lld",cnt);
	return 0;
}
