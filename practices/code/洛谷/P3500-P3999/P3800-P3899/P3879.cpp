// https://www.luogu.com.cn/problem/P3879
// 题意：给定 N 篇由小写字母和空格组成的英文短文
// （每篇先给出单词数 L，再给出 L 个单词），再给出 M 个生词询问。
// 对每个询问单词，按从小到大不重复地输出它出现过的短文序号（未出现则输出空行）。
// 数据范围：1 <= N <= 10^3，1 <= M <= 10^4，
// 每篇短文长度（含相邻单词间空格）<= 5 * 10^3 字符
// 每个单词长度 <= 20 字符。
// 难度评分：1000（洛谷分级换算）
// 算法标签：map、字符串
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;

int n, m, num, cnt[maxn];
string s;
map<string,vector<int> >a;

int main()
{
	cin>>n;
	for(int i = 1; i <= n; i++){
		cin>>num;
		for(int j = 1; j <= num; j++){
			cin>>s;
			a[s].push_back(i);
		}
	}
	cin>>m;
	for(int i = 1; i <= m; i++){
		cin>>s;
		memset(cnt,0,sizeof(cnt));
		for(int j = 0; j < a[s].size(); j++)
		if(cnt[a[s][j]] == 0){
			cout<<a[s][j]<<" ";
			cnt[a[s][j]]++;
		}
		cout<<endl;
	}
	return 0;
}
