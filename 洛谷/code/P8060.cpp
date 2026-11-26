// https://www.luogu.com.cn/problem/P8060
// 题意：给定长为 n 的严格递增正整数集合 A = {a_1, ..., a_n}。
// 定义 A' 为所有可表示为 A 中若干元素（可重复，0 个元素之和为 0）之和的非负整数集合。
// 给出 k 个询问 b_1..b_k，判断每个 b_i 是否属于 A'。
// 输入 n 及 n 行 a_i，再输入 k 及 k 行 b_i。
// 输出 k 行，属于输出 TAK，否则输出 NIE。
// 数据范围：1 <= n <= 5*10^3，1 <= k <= 10^4，1 <= a_1 < a_2 < ... < a_n <= 5*10^4
// 0 <= b_i <= 10^9。
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
