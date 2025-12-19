#include<bits/stdc++.h>
using namespace std;

queue<int>q;
bool ans[41];
int a[41][41],pre[41][41],num[41],dis[41],n;

void bfs(int s,int t){
	memset(num,0,sizeof num),memset(dis,63,sizeof dis);  //  忘了清数组会爆0
	dis[s]=0,q.push(s);
	while(!q.empty()){
		s=q.front(),q.pop();
		for(int i=1;i<=n;i++) if(a[s][i])
			if(dis[i]>dis[s]+1)
				dis[i]=dis[s]+1,pre[i][++num[i]]=s,q.push(i);
			else if(dis[i]==dis[s]+1) pre[i][++num[i]]=s;  //  分情况记录前驱
	}
	memset(ans,0,sizeof ans),q.push(t),ans[t]=1;
	while(!q.empty()){
		s=q.front(),q.pop();
		for(int i=num[s];i;i--) if(!ans[pre[s][i]])
			ans[pre[s][i]]=1,q.push(pre[s][i]);  //  倒着搜回去
	}
	for(int i=1;i<=n;i++) if(ans[i]) printf("%d ",i);
}
int main(){
	int m,q,x,y;
	scanf("%d%d",&n,&m);
	while(m--) scanf("%d%d",&x,&y),a[x][y]=1,a[y][x]=1;
	scanf("%d",&q);
	while(q--) scanf("%d%d",&x,&y),bfs(x,y),putchar('\n');
	return 0;
}
