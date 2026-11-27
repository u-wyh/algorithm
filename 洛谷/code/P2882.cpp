// https://www.luogu.com.cn/problem/P2882
// 题意：输入奶牛数量 N，以及排成一排的每头奶牛初始朝向（F 表示朝前，B 表示朝后）。
// 选定一个固定长度 K（1 <= K <= N），每次操作可同时反转排中连续 K 头奶牛的朝向（不可跨出边界），目标是将所有牛变为朝前（F）。
// 求出能达成目标的最少操作次数 M，以及在达到最少操作次数的前提下 K 的最小值。
// 输出一行两个空格分隔的整数，依次为 K 和 M。
// 数据范围：对于 100% 的数据，1 <= N <= 5000。
#include<bits/stdc++.h>
// 算法标签：枚举、贪心、差分
using namespace std;
const int maxn = 10009;

int n;
bool A[maxn],B[maxn];

int main()
{
    cin>>n;
	char ch;
	for(int i=1;i<=n;++i){
		cin>>ch;
		A[i]=ch=='B'?0:1;
	}
	int mincnt=0x7fffffff,anslen;
	for(int len=1;len<=n;++len){
		memset(B,0,sizeof B);
		bool b=0,flag=1;
		int cnt=0;
		for(int i=1;i<=n;++i){
			b^=B[i];//数组B为记录差分的数组
			if(!(A[i]^b)){//若当前位置为0
				if(i+len-1>n){
                    flag=0;
                    break;
                }
				b^=1,B[i+len]^=1;
				++cnt;
			}
		}
		if(flag){
            if(cnt<mincnt)
                mincnt=cnt,anslen=len;
        }
	}
	cout<<anslen<<' '<<mincnt;
}
