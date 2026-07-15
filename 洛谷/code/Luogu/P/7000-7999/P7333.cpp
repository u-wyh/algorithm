#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
const int N=1e5+9;
const int M=23;
int Max[N*3][M+1];//a[i]的最大值
//处理中间一个复制的环的时候向左右挪动可能会发生数组越界，
//所以直接三倍，只处理中间一环即可。
//当一个端点确定是，该区间扩展时，最大值非严格单调递增，用二分，+st表维护
int Log[N];
int a[N],b[3*N];
int n;
int f[N];
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
int max(int a,int b)
{
	if(a>b) return a;
	else return b;
}
int min(int a,int b)
{
	if(a<b) return a;
	else return b;
}
int RMQ(int l,int r)
{
	int k=Log[r-l+1];
	return max(Max[l][k],Max[r-(1ll<<k)+1][k]);
}
void prepare()
{
	for(int i=1;i<=n;i++)//每次二分最长为一个链，不需要处理过多
		Log[i]=log2(i);
	for(int j=1;j<M;j++)
		for(int i=1;i+(1ll<<j)-1<=3*n;i++)
			Max[i][j]=max(Max[i][j-1],Max[i+(1ll<<(j-1))][j-1]);
}
void erfen()
{
	int len=n/2;
	for(int i=n+1;i<=n+n;i++)
	{
		int ans=0x3f3f3f3f;
		if(RMQ(i-len,i-1)>=b[i])// 找左边 |i-len+1-----i-1|//注意没有i！！！
		{
			int l=i-len;
			int r=i-1;//Wrong，最后不能有i这个位置
			while(l<=r)
			{
				int mid=(l+r)>>1;
				int cal=RMQ(mid,i-1);
				//printf("l= %d , r= %d , mid= %d , cal= %d\n",l,r,mid,cal);
				if(cal>=b[i])//Wrong在这个范围内有，缩小范围
				{
					//std::cout<<"b[i]= "<<b[i]<<std::endl;
					ans=min(ans,i-mid);
					l=mid+1;
				}
				else r=mid-1;//扩大范围继续找
			}
		}
		if(RMQ(i+1,i+len)>=b[i])// 找右边 |i+1------i+len-1|，不要包含i！！！
		{
			int l=i+1;
			int r=i+len;
			while(l<=r)
			{
				int mid=(l+r)>>1;
				int cal=RMQ(i+1,mid);//Wrong
				//printf("l= %d , r= %d , mid= %d , cal= %d\n",l,r,mid,cal);
				if(cal>=b[i])
				{
					ans=min(ans,mid-i);
					r=mid-1;
				}
				else l=mid+1;
			}
		}
		if(ans!=0x3f3f3f3f)
			printf("%d ",ans);
		else printf("-1 ");
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		Max[i][0]=Max[i+n][0]=Max[i+n+n][0]=read();
	for(int i=1;i<=n;i++)
		b[i]=b[i+n]=b[i+n+n]=read();
	prepare();
	erfen();
	return 0;
}
