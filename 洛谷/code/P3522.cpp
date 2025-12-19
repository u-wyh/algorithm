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
