// https://www.luogu.com.cn/problem/P2170
// 题意：从 n 名学生中选学霸，目标人数为 m，
// 有 k 对人所在连通块必须全选或全不选。
// 求最接近 m 的合法选出人数；若差值相等，选较小的一个。
// 输出选出的人数。
// 数据范围：1 <= n <= 2*10^4，0 <= m <= n，
// 0 <= k <= 2*10^4。
// 难度评分：1300（洛谷分级换算）
// 算法标签：并查集、0-1背包
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e4+5;

int fa[MAXN],sz[MAXN];
int n,m,k;
int cnt=1;
int ans[MAXN];
int dp[MAXN*2];

void build(){
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
}

int find(int i){
    if (i != fa[i]){
        fa[i] = find(fa[i]);
    }
    return fa[i];
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        sz[fx]+=sz[fy];
        fa[fy]=fx;
    }
}

int main()
{
    cin>>n>>m>>k;
    build();
    for(int i=1;i<=k;i++){
        int u,v;
        cin>>u>>v;
        un(u,v);
    }
    for(int i=1;i<=n;i++){
        if(find(i)==i){
            ans[cnt++]=sz[i];
        }
    }
    cnt--;
    for(int i=1;i<=cnt;i++) //背包问题
		for(int j=2*m;j>=ans[i];j--)
			dp[j]=max(dp[j],dp[j-ans[i]]+ans[i]);
    int ans=999999999,minn=999999999;
	for(int i=1;i<=2*m;i++)	//找到最接近m的
	{
		if(minn>abs(dp[i]-m)) minn=abs(dp[i]-m),ans=dp[i];
	}
	if(ans==999999999) printf("0");
	else	printf("%d",ans);
    return 0;
}
