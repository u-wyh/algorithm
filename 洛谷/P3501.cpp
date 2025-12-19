#include<iostream>
#include<cstdio>
#include<cstring>
#define ull unsigned long long
using namespace std;
const int N=5e5+10;
char s[N],t[N];
int n,p=13331;
long long ans;
unsigned long long pp[N],f[N],g[N];
inline void work(int x){
	int l=0,r=min(x,n-x);
	while(l<r){
		int mid=(l+r+1)>>1;
		if((ull)(f[x]-f[x-mid]*pp[mid])==(ull)(g[x+1]-g[x+1+mid]*pp[mid])){
			l=mid;
		}else r=mid-1;
	}
	ans+=l;
}
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	pp[0]=1;
	for(int i=1;i<=n;i++){
		if(s[i]=='1') t[i]='0';
		else t[i]='1';
	}
	for(int i=1;i<=n;i++)pp[i]=pp[i-1]*p;
	for(int i=1;i<=n;i++)f[i]=f[i-1]*p+(s[i]-'0'+12);
	for(int i=n;i>=1;i--)g[i]=g[i+1]*p+(t[i]-'0'+12);

	for(int i=1;i<n;i++){
		if(s[i]==s[i+1])continue;
	     work(i);
	}
	printf("%lld\n",ans);
	return 0;
}
