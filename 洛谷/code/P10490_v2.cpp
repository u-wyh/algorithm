#include<bits/stdc++.h>
using namespace std;

const int MAXN=55;
int n,ans;
int a[MAXN];
vector<int> up,down;//数组里面存的是一个系统的最新值

void dfs(int now){
	int upsize=up.size();
	int downsize=down.size();

	if(upsize+downsize>=ans)
        return;
	if(now>n){
		ans=min(ans,upsize+downsize);
		return;
	}

	for(int i=0;i<upsize;i++){
		if(up[i]<a[now]){
			int t=up[i];
			up[i]=a[now];
			dfs(now+1);
			up[i]=t;
			break;
		}
	}

	if(upsize==0||up[upsize-1]>=a[now])
	{
		up.push_back(a[now]);
		dfs(now+1);
		up.pop_back();
	}

	for(int i=0;i<downsize;i++){
		if(down[i]>a[now]){
			int t=down[i];
			down[i]=a[now];
			dfs(now+1);
			down[i]=t;
			break;
		}
	}
	if(downsize==0||down[downsize-1]<=a[now]){
		down.push_back(a[now]);
		dfs(now+1);
		down.pop_back();
	}
	return;
}

int main(){
	while (true)
	{
		scanf("%d",&n);
		if(n==0) break;
		up.clear();
		down.clear();
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		ans=n;
		dfs(1);
		printf("%d\n",ans);
	}
	return 0;
}
