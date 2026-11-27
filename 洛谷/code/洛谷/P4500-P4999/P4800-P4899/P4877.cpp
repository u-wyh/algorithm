// https://www.luogu.com.cn/problem/P4877
// 题意：N 头奶牛一一对应参加按顺序进行的 N 项比赛，
// 第 i 头牛参加第 j 项得 S_{i,j} 分；
// 另有 B 个奖励，
// 第 K_i 项比赛结束时若当前总分 >= P_i 则额外得 A_i
// 分（同刻奖励可任意顺序结算），求最大总分。
// 数据范围：1 <= N, B <= 20，1 <= K_i <= N，
// 1 <= P_i <= 4 * 10^4，1 <= A_i <= 10^3
// 1 <= S_{i,j} <= 10^3。
// 算法标签：状态压缩动态规划、排序
#include<bits/stdc++.h>
using namespace std;

struct node{
	int P,A;
};
vector<node> vec[21];
int dp[1<<21],val[21][21],n,m;

bool cmp(node a,node b) {
    return a.P < b.P;
}

int main()
{
    cin>>n>>m;
	for(int i = 1;i <= m;i++) {
		int a,b,c;
		cin>>a>>b>>c;
		vec[a].push_back({b,c});
	}
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n;j++) {
			cin>>val[j][i];//注意这里
		}
	}
	for(int i = 1;i <= n;i++)
        sort(vec[i].begin(),vec[i].end(),cmp);
	for(int s = 1;s < (1<<n);s++){
		int S = 0;
		for(int j = 1;j <= n;j++)
            S += ((s>>(j-1))&1);
        //这里的S表示奶牛的状态，选了几头奶牛 就意味着按照顺序有几个任务已经完成
        //接下来要选的就是那头奶牛为下一个任务服务
		for(int j = 1;j <= n;j++) {
			if((s&(1<<j-1))) {
				dp[s] = max(dp[s],val[S][j]+dp[s^(1<<j-1)]);
				//dp[s^(1<<j-1)]表示最后一个任务是由这头奶牛j完成的
			}
		}
		for(int j = 0;j < vec[S].size();j++){
			if(dp[s] >= vec[S][j].P){
                dp[s] += vec[S][j].A;
			}
		}
		//cout<<s<<' '<<dp[s]<<endl;
	}
	cout<<dp[(1<<n)-1];
	return 0;
}
