// https://www.luogu.com.cn/problem/P3522
// 题意：输入记录天数 n，以及每天温度的已知下界 x_i 和上界 y_i。
// 找一段最长的连续天数，
// 使得存在一组每天落在该日 [x_i, y_i] 内的实际温度序列，
// 满足温度单调不降。
// 输出这个最长的连续天数。
// 数据范围：1 <= n <= 10^6，
// -10^9 <= x_i <= y_i <= 10^9。
// 算法标签：单调队列、贪心
#include<bits/stdc++.h>
using namespace std;

struct node{
	int l,r,id;//id表示是第几天
};

int main()
{
	int n,ans=1;
	scanf("%d",&n);
	deque<node> q;
	for(int i=1;i<=n;i++){
		int l,r;
		scanf("%d%d",&l,&r);
		while(!q.empty()&&q.front().l>r){
			q.pop_front();
		}
		if(!q.empty()){
			ans=max(ans,i-q.front().id+1);
		}
		int tmp=i;
		while(!q.empty()&&q.back().l<l){
			tmp=q.back().id;//维护这一段的起始天
			q.pop_back();
		}
		q.push_back((node){l,r,tmp});
	}
	printf("%d",ans);
	return 0;
}
