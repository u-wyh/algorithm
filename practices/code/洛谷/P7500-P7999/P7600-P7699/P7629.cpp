// https://www.luogu.com.cn/problem/P7629
// 题意：给定 1~N 的排列，每轮将其划分为最少个极长递减子串（slope），
// 将所有长度 > 1 的 slope 反转，直至整体递增；
// 已知首轮划分每个 slope 长度均为偶数，求总共调用反转操作的次数。
// 数据范围：2 <= N <= 10^5。
// 算法标签：树状数组、逆序对、模拟
#include<bits/stdc++.h>
using namespace std;
const int N=100005;

int n,a[N],c[N];
long long ans;

void swap(int& x,int& y){
    x^=y;y^=x;x^=y;
}//交换两个元素

void reverse(int l,int r){//翻转区间[l,r]内的元素
	for(int i=l;i<=r&&(i<<1)<l+r;++i)
        swap(a[i],a[r+l-i]);
	++ans;//顺便统计答案
}

int lowbit(int x){
    return x&-x;
}//下面三行是经典的树状数组

void update(int i,int v){
    for(;i<=n;i+=lowbit(i))
        c[i]+=v;
}

int getsum(int i){
    int ans=0;
    for(;i;i-=lowbit(i))
        ans+=c[i];
    return ans;
}

int main()
{
	scanf("%d",&n);
	int las=1;scanf("%d",&a[1]);//先将序列按要求翻转一次
	for(int i=2;i<=n;++i){
		scanf("%d",&a[i]);
		if(a[i]>a[i-1]){
			reverse(las,i-1);
			las=i;
		}
	}
	reverse(las,n);
	for(int i=n;i>=1;--i){//然后直接树状数组求逆序对正确性就可以保证了
		ans+=getsum(a[i]);
		update(a[i],1);
	}
	printf("%lld\n",ans);
	return 0;
}
