// https://www.luogu.com.cn/problem/P2064
// 题意：从第 1 天行驶任意正整数距离 a 出发，
// 每天路程须为前一天的 2~9 的整数倍。
// 要求至少行驶 2 天，且总路程恰好等于给定的正整数 S。
// 输出最少行驶天数；若无解输出 -1。
// 数据范围：
// 9 < S <= 10^8（总里程）
// 算法标签：深度优先搜索、剪枝、数论
#include<bits/stdc++.h>
using namespace std;

int ans=INT_MAX,n;

void dfs(int dep,int num){
    if(dep>ans){
        return ;
    }
    if(num==0){
        ans=min(ans,dep);
        return ;
    }
    num--;
    for(int i=2;i<=9;i++){
        if(num%i==0){
            dfs(dep+1,num/i);
        }
    }
}

int main()
{
	cin>>n;
	for(int i=1;i<=sqrt(n);i++){
        if(n%i==0){
            if(i!=1)
                dfs(0,i);
            dfs(0,n/i);
        }
	}
	if(ans!=INT_MAX)
        cout<<ans<<endl;
	else
        cout<<-1<<endl;
	return 0;
}
