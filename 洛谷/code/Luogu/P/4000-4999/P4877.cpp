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
