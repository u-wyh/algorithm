// https://www.luogu.com.cn/problem/P10854
// 题意：给一串 0 和 1。
// 每次可翻转首尾位置，或翻转两侧邻居不同的内部位置。
// 要求在 r 步内变成全 0 或全 1，输出步数和每步的下标，步数无须最小。
// 无法完成时按题目格式报告无解。
// 数据范围：2 ≤ n ≤ 2000，
// 元素只可能为 0 或 1，r 为 10^6 或 2 × 10^6。
// 难度评分：1400（洛谷分级换算）
// 算法标签：构造、递归

#include<bits/stdc++.h>
using namespace std;
const int N = 2e3+5;

int n,a[N],r,ans,op[2000005],limit;

inline void change(int x,int o){
    //o的作用是向左递归还是向右递归
	if(x==1||x==n||a[x-1]!=a[x+1]) 
        return a[x]^=1,op[++ans]=x,void(0);
	if(o) 
        change(x-1,o),a[x]^=1,op[++ans]=x;
	else 
        change(x+1,o),a[x]^=1,op[++ans]=x;
}

int main(){
	scanf("%d%d",&n,&limit);
	for(int i=1;i<=n;i++) 
        scanf("%d",&a[i]);
	int l=n>>1,r=l+1;
	if(a[l]!=a[r]) 
        change(l,1);
	l--,r++;
	while(l>=1) 
        a[l]!=a[l+1]?change(l,1),l--:l--;
	while(r<=n) 
        a[r]!=a[r-1]?change(r,0),r++:r++;
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++) 
        printf("%d ",op[i]);
	return 0;
}