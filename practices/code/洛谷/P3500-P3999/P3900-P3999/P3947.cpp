// https://www.luogu.com.cn/problem/P3947
// 题意：共有 n 首歌曲
// 每首歌耗时 T_i、奖励开放时间
// M_i（若在不超过 M_i 的时刻完成
// 则获得 M_i - 当前已用总时间 的分数，
// 否则得 0 分）。
// 必须在剩余时间 t 内打完所有 n 首歌且总分 >= m。
// 判断是否可行；
// 若可行，输出能获得的最大总分及字典序最小的完成歌曲顺序
// （输入歌名 S_i 已按字典序给出）。
// 数据范围：n <= 22，
// |S_i| <= 50，T_i <= M_i，m, t, M_i, T_i
// 及其相加结果都在 int 最大范围内。
// 算法标签：状态压缩动态规划
#include<bits/stdc++.h>
using namespace std;

int n,mn,T;
char name[25][50];
int t[25],m[25];
int dp[(1<<22)];
string s[(1<<22)];
int stime[(1<<22)];

int main()
{
	scanf("%d %d %d",&n,&mn,&T);
	int ts=0;
	for(int i=1;i<=n;i++){
		scanf("%s %d %d",name+i,t+i,m+i);
		ts+=t[i];
	}
	if(ts>T)
        printf("No Answer"),exit(0);
	int temp0=(1<<n);
	for(int S=1;S<temp0;S++){
		for(int i=1;i<=n;i++){
			if(S&(1<<(i-1))){
				int last=S^(1<<(i-1));
				if(!stime[S])
                    stime[S]=stime[last]+t[i];
				int sum=stime[last];
				int temp=dp[last]+max(0,m[i]-(sum+t[i]));
				if(temp>dp[S]){
					dp[S]=temp;
					s[S]=s[last]+(char)i;
				}
				else if(temp==dp[S]){
					s[S]=min(s[S],s[last]+(char)i);
				}
			}
		}
		//print(S);cout<<" "<<dp[S]<<" ";prints(S);cout<<endl;
	}
	int temp=(1<<n)-1;
	int ans=dp[temp];
	if(ans<mn)
        printf("No Answer"),exit(0);
	printf("%d\n",ans);
	int temp2=s[temp].length();
	for(int i=0;i<temp2;i++){
		printf("%s\n",name[s[temp][i]]);
	}
	return 0;
}
