// https://www.luogu.com.cn/problem/P2161
// 题意：维护数轴上线段集合 S，共 n 次操作。
// A l r：删去 S 中所有与 [l,r] 相交的线段，加入 [l,r]，并输出删除个数。
// B：输出 S 中的线段数量。
// 数据范围：1 <= n <= 2*10^5，1 <= l <= r <= 10^5。
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<set>
// 算法标签：平衡树、区间维护
using namespace std;
struct Plan{
	int l,r;
	bool operator <(const Plan &rhs)const{
		return r<rhs.l;
	}
};
int T;
set<Plan> s;
int main(){
	cin>>T;
	while(T--){
		char c; scanf(" %c",&c); //空格可以防止读入无效字符
		if(c=='A'){
			int l,r,cnt=0; scanf("%d %d",&l,&r);
			Plan tmp=(Plan){l,r};
            //删掉与该预约冲突的预约，并统计个数
			set<Plan>::iterator it=s.find(tmp);
			while(it!=s.end()){
				++cnt; s.erase(it);
				it=s.find(tmp);
			}
			s.insert(tmp);
			printf("%d\n",cnt);
		}
		else{
			printf("%d\n",s.size());
		}
	}
	return 0;
}
