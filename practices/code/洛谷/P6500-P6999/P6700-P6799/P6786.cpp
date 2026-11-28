// https://www.luogu.com.cn/problem/P6786
// 题意：从长为 n 的序列 a 中选出若干个元素组成序列 b_1..b_k，
// 使得每个 b_i 要么是 b 的最大值
// 要么存在 b_j > b_i
// 满足 b_i + b_j + gcd(b_i, b_j)
// = lcm(b_i, b_j)，求选出元素之和的最大值。
// 数据范围：1 <= n <= 3*10^5，1 <= a_i <= 10^9。
// 难度评分：1500（洛谷分级换算）
// 算法标签：排序、贪心、映射
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=3e5+5;

map <int,int> mp;
int n,a[N];
ll ans;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
        cin>>a[i],mp[a[i]]++;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		ll tmp=a[i],cnt=0;
		while(mp[tmp]){
			cnt+=tmp*mp[tmp],mp[tmp]=0;
			if(tmp%2==0)
                tmp=tmp/2*3;
			else
                break;
		}
		ans=max(ans,cnt);
	}
	cout<<ans<<endl;
	return 0;
}
