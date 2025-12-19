#include<bits/stdc++.h>
using namespace std;
int n,m,c[19],tot,ans=1e9,b[19];

//b数组用来记录第i个箱子的剩余容量
void dfs(int x,int cnt)
{
	if(x==n+1){
		ans=min(ans,cnt);
		return;
	}
	if(cnt>=ans)
        return;//剪枝1（这个不用解释）
	for(int i=1;i<=x-tot;i++)
    //枚举箱子，看看物品x能放入那一个箱子
    //由于不可能有体积大于容量的物品，所以第x个物品顶多会用到第x个箱子，假如说原本每个物品都独占一个箱子，
    //tot是用来记录有多少挤到已经有物品的箱子里的物品个数，因为有的物品和别的物品共用一个箱子，
    //这必然会腾出该物品原来占有的箱子，所以只需枚举到x-tot个箱子就可以了。
    //比如说2,3,4号物品共同占用2号箱子，那5号物品顶多会用到3号箱子，所以只需枚举到3.
	{
		if(b[i]<c[x])
            continue;
		if(b[i]==m)
            cnt++;
		else
            tot++;
		b[i]-=c[x];
		dfs(x+1,cnt);
		b[i]+=c[x];
		if(b[i]==m)
            cnt--;
		else
            tot--;
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>c[i],b[i]=m;
    //把箱子剩余容量初始化为m
    dfs(1,0);
	cout<<ans;
}
