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
