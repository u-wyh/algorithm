// https://www.luogu.com.cn/problem/P8666
// 题意：输入 A, B, C, m
// 第二行按 ((i-1)*B+(j-1))*C+(k-1)+1 顺序给出
// A*B*C 个点 (i, j, k) 的生命值 d(i, j, k)
// 随后 m 轮攻击
// 每行给出 (la_t, ra_t, lb_t, rb_t,
// lc_t, rc_t, h_t)，
// 对长方体区间内所有点累计加上 h_t 伤害；
// 当某点累计伤害严格大于 d(i, j, k) 时爆炸（保证一定存在），
// 输出第一艘战舰是在第几轮后爆炸的。
// 数据范围：1 <= A*B*C <= 10^6，1 <= m <= 10^6
// 0 <= d(i, j, k),
// h_t <= 10^9
// （原文数据约定漏印字母 d，
// 写作 0 <= (i,j,k), h_t <= 10^9）。
// 算法标签：二分答案、三维差分、前缀和
#include<bits/stdc++.h>
#define N 1000005
using namespace std;

int A,B,C,m,s[N];
int X1[N],X2[N],Y1[N],Y2[N],Z1[N],Z2[N];
int d[N],sub[N];

int change(int x,int y,int z){
	if(x>A||y>B||z>C)return 0;
	return ((x-1)*B+y-1)*C+z;
}//将三维转化成一维

void fun(int x,int y,int z,int d){
    sub[change(x,y,z)]+=d;
}

bool build(){
	//三个方向计算前缀和
	for(int i=1;i<=A;i++)
		for(int j=1;j<=B;j++)
			for(int k=1;k<=C;k++)
                fun(i,j,k+1,sub[change(i,j,k)]);
	for(int i=1;i<=A;i++)
		for(int k=1;k<=C;k++)
			for(int j=1;j<=B;j++)
                fun(i+1,j,k,sub[change(i,j,k)]);
	for(int j=1;j<=B;j++)
		for(int k=1;k<=C;k++)
			for(int i=1;i<=A;i++)
                fun(i,j+1,k,sub[change(i,j,k)]);
	for(int i=1;i<=A*B*C;i++)
		if(sub[i]>s[i])
            return 1;
	return 0;
}

bool check(int x){
	memset(sub,0,sizeof(sub));//记住这里要清空，不然之前的还会留在数组中
	for(int i=1;i<=x;i++){
		fun(X1[i],Y1[i],Z1[i],d[i]);
		fun(X2[i]+1,Y1[i],Z1[i],-d[i]);
		fun(X1[i],Y1[i],Z2[i]+1,-d[i]);
		fun(X2[i]+1,Y1[i],Z2[i]+1,d[i]);
		fun(X1[i],Y2[i]+1,Z1[i],-d[i]);
		fun(X2[i]+1,Y2[i]+1,Z1[i],d[i]);
		fun(X1[i],Y2[i]+1,Z2[i]+1,d[i]);
		fun(X2[i]+1,Y2[i]+1,Z2[i]+1,-d[i]);
	}//对sub数组进行差分
	return build();
}

int main()
{
	cin>>A>>B>>C>>m;
	for(int i=1;i<=A*B*C;i++)
        cin>>s[i];
	for(int i=1;i<=m;i++)
        cin>>X1[i]>>X2[i]>>Y1[i]>>Y2[i]>>Z1[i]>>Z2[i]>>d[i];
	int l=1,r=m,ans=m;
	while(l<=r){//二分答案，取临界点
		int mid=(l+r)/2;
		if(check(mid)){
            ans=mid;
            r=mid-1;
		}else
            l=mid+1;
	}
	cout<<ans;
	return 0;
}
