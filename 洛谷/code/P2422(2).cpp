#include <cstdio>
#include <iostream>
using namespace std;

const int N = 100005;

inline int read()
{
	int x = 0 , f = 1;	char ch = getchar();
	while(ch < '0' || ch > '9')	{if(ch == '-')	f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}

int n , top;
int a[N] , st[N] , l[N] , r[N];
long long sum[N];
long long ans;

int main()
{
	n = read();
	for(int i = 1;i <= n;i ++)
        sum[i] = sum[i-1] + (a[i] = read());
	for(int i = 1;i <= n;i ++){
		while(top && a[st[top]] >= a[i])
            top --;
		l[i] = st[top];
		st[++top] = i;
	}
	top = 0;
	st[0] = n+1;
	for(int i = n;i >= 1;i --)
	{
		while(top && a[st[top]] >= a[i])
            top --;
		r[i] = st[top] - 1;
		st[++top] = i;
 	}
 	for(int i = 1;i <= n;i ++)
        ans = max(ans,(sum[r[i]] - sum[l[i]]) * a[i]);
 	return printf("%lld\n",ans) , 0;
}
