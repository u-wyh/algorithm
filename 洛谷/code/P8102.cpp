// https://www.luogu.com.cn/problem/P8102
// 题意：给定长为 n 的序列 a_1..a_n 以及整数 m, A。
// 将 A 插入到序列 a 的任意位置（可插在最前、最后或任意两元素间，共 n + 1 种位置）形成新序列 b
// 求插入后新序列的所有长度为 m 的连续子区间的最大值之和（即 ∑_{i=1}^{(n+1)-m+1} max_{i<=j<=i+m-1} b_j）的最大值。
// 第一行输入 n, m, A，第二行输入 n 个整数 a_i。
// 输出一行一个整数。
// 数据范围：1 <= m <= n <= 5*10^6，0 <= a_i, A <= 100。
#include<bits/stdc++.h>
using namespace std;

int n,m,A,h,t;
int arr[5000005];
int q1[5000005],q2[5000005],b[5000005],c[5000005],s2[5000005],s1[5000005];
int sum=0,maxn;

inline int rd(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
	return x*f;
}

int main()
{
    n=rd(),m=rd(),A=rd();
    for(int i=1;i<=n;i++){
        arr[i]=rd();
    }
    h=t=0;
    for(int i=1;i<=n;i++){
        while(h<t&&i-q1[h]>=m){
            h++;
        }
        while(h<t&&arr[q1[t-1]]<arr[i]){
            t--;
        }
        q1[t++]=i;
        if(i>=m){
            sum+=arr[q1[h]];
            b[i-m+1]=arr[q1[h]];
        }
    }
    m--;
    h=t=0;
    for(int i=1;i<=n;i++){
        while(h<t&&i-q2[h]>=m){
            h++;
        }
        while(h<t&&arr[q2[t-1]]<arr[i]){
            t--;
        }
        q2[t++]=i;
        if(i>=m){
            c[i-m+1]=arr[q2[h]];
        }
    }
    for(int i=1;i<=n-m+1;i++)
        c[i]=max(c[i],A);
	for(int i=1;i<=n;i++)
        s2[i]=s2[i-1]+c[i];
	m++;
	for(int i=1;i<=n;i++)
        s1[i]=s1[i-1]+b[i];
	for(int i=0;i<=n;i++){
		int ret=c[i+1];
		ret-=s1[i];
        ret+=s1[max(0,i-m+1)];
		ret+=(s2[i]-s2[max(0,i-m+1)]);
		maxn=max(maxn,ret);
	}
	cout<<sum+maxn<<endl;
    return 0;
}
