// https://www.luogu.com.cn/problem/P8893
// 题意：输入题目数 N、目标题号 K、第 0 天初始推荐数 p 及这 p 道题号
// 再输入 R 条规则
// （每条给出目标题 v_i、前提题数 s_i 及 s_i 个前提题号 p_i）；
// 天数从 0 开始，每天可做任意道以前或当天已推荐且未做过的题；
// 若集合 s_i 中所有题均已做完且至少有一道是在第 d 天做的，
// 则第 d+1 天会推荐
// v_i（无前提时按规则若已在第 0 天推荐则第 0 天可做）；
// 输出做完第 K 题的最早天数，无法完成输出 -1。
// 数据范围：
// 1 <= K, s_i, p_i, v_i <= N <= 5*10^3，
// 0 <= R <= 5*10^3
// 所有 |s_i| 互不相同（原文写作 |s_i| 互不相同）
// 且同一规则内 p_i 互不相同、各规则的 v_i
// 互不相同（未单独标注 p 上界）。
// 难度评分：1300（洛谷分级换算）
// 算法标签：广度优先搜索、拓扑排序
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int n,k,r,day,vis[N],t[N];
//vis 记录某题是否已做，t 记录做某题所需要做的题数
int w,nw,ok[N],nok[N];
//分别记录今天推荐题目，明天推荐题目
vector <int> relat[N];
//relat 记录某题在哪些题的题目集合里
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>k>>nw;
	for(int i=1;i<=nw;i++) cin>>nok[i];
	cin>>r;
	for(int i=1,x,y;i<=r;i++){
		cin>>x>>t[x];
		for(int j=1;j<=t[x];j++){
			cin>>y;
			relat[y].push_back(x);
		}
	}
	while(1){
		//明天推荐题目复制到今天推荐题目里
		w=nw;nw=0;
		for(int i=1;i<=w;i++)
			ok[i]=nok[i];
		//如果当天没有任何推荐题目，无解
		if(!w){
			cout<<"-1\n";
			return 0;
		}
		for(int i=1;i<=w;i++){
			//记录已做
			vis[ok[i]]=1;
			//遍历包含本题的题目集合
			for(int j=0,l=relat[ok[i]].size();j<l;j++){
				t[relat[ok[i]][j]]--;
				//如果需做题数为零，则明天能做这道题
				if(!t[relat[ok[i]][j]]){
					nok[++nw]=relat[ok[i]][j];
				}
			}
		}
		//做完了第k道题，退出循环
		if(vis[k]) break;
		day++;
 	}
	cout<<day<<'\n';
	return 0;
}
