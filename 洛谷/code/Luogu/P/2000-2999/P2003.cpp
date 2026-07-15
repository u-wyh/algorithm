#include<iostream>
#include<cstdio>
#include<algorithm>
#define LL long long
#define INF 0x7fffffff
using namespace std;
const int N=1e2+5;
struct leb{
	int y,x1,x2;
}a[N];
LL ans=0;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	int n=read();
	for(int i=1;i<=n;++i){
		a[i].y=read();
		a[i].x1=read();
		a[i].x2=read();
	}
	for(int i=1;i<=n;++i){
		int c1=INF,c2=INF,f1=0,f2=0;
		double l=a[i].x1+0.5,r=a[i].x2-0.5;
		for(int j=1;j<=n;++j){
			if(i==j)continue;
			int ll=a[j].x1,rr=a[j].x2;
			if(l>ll&&l<rr&&a[i].y>a[j].y)c1=min(c1,a[i].y-a[j].y),f1=1;
			if(r>ll&&r<rr&&a[i].y>a[j].y)c2=min(c2,a[i].y-a[j].y),f2=1;
		}
		if(!f1)c1=min(c1,a[i].y);
		if(!f2)c2=min(c2,a[i].y);
		ans+=(c1+c2);
	}
	printf("%lld\n",ans);
	return 0;
}
