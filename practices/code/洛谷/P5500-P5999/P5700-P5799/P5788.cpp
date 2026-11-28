// https://www.luogu.com.cn/problem/P5788
// 题意：给定长为 n 的整数序列 a，
// 对每个位置 i 求出它
// 之后第一个严格大于 a_i 的元素下标（不存在则记为 0）。
// 输入 n 及序列 a；输出 n 个整数表示每个位置的答案。
// 数据范围：1 <= n <= 3*10^6，1 <= a_i <= 10^9。
// 难度评分：1100（洛谷分级换算）
// 算法标签：单调栈
#include<bits/stdc++.h>
using namespace std;

int st[3000005];
int n,r=0;
int nums[3000005],R[3000005];

int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-')	f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x*f;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        nums[i]=read();
    int cur;
    for(int i=1;i<=n;i++){
        while(r>0&&nums[st[r-1]]<=nums[i]){
            cur=st[--r];
            R[cur]=i;
        }
        st[r++]=i;
    }

    while (r > 0) {
        cur = st[--r];
        R[cur] = 0;
    }

    for(int i=n-2;i>=0;i--){
        if(R[i]!=0&&nums[i]==nums[R[i]])
            R[i]=R[R[i]];
    }
    for(int i=1;i<=n;i++)
        cout<<R[i]<<' ';
    return 0;
}
