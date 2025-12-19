#include<bits/stdc++.h>
#define int long long //记得开long long
using namespace std;
const int N=5e6+10;

int head[N],cnt,vis[N],tot,a[N],dis[N];
int n,l,r,minn=0x3f3f3f3f3f3f3f3f;
queue<int>q;

inline void spfa(){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	q.push(0);
	vis[0]=1;
	dis[0]=0;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=1;i<=n;i++){
			if(a[i]==minn)
                continue;
			int y=(x+a[i])%minn;
			if(dis[y]>dis[x]+a[i]){
				dis[y]=dis[x]+a[i];
				if(!vis[y]){
					q.push(y);
					vis[y]=1;
				}
			}
		}
	}
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		minn=min(minn,a[i]);
	}
	spfa();
	int k;
	scanf("%lld",&k);
	while(k--){
		int c;
		scanf("%lld",&c);
		printf("%s\n",dis[c%minn]<=c ?"TAK":"NIE");//不要把输出打错，不然会像我一样调试半天（orz）
	}
	return 0;
}
