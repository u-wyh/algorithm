// https://www.luogu.com.cn/problem/P4301
// 题意：有 k 堆火柴，每堆 a_i 根；
// 第一回合先手和后手各可以直接拿走若干整堆（可以不拿但不能全拿光），从第二回合开始按普通 Nim 游戏轮流从某一堆拿走任意正数根（拿最后一根胜）
// 求先手第一回合至少要拿走多少根火柴才能保证必胜，不能必胜输出 -1。
// 数据范围：1 <= k <= 100，1 <= a_i <= 1e9。
#include<bits/stdc++.h>
// 算法标签：线性基、贪心
using namespace std;
const int BIT = 40;

int n;
long arr[105];
long basis[BIT];

bool insert(long num) {
	for (int i = BIT; i >= 0; i--) {
		if (num >> i == 1) {
			if (basis[i] == 0) {
				basis[i] = num;
				return true;
			}
			num ^= basis[i];
		}
	}
	return false;
}

bool cmp(long a,long b){
    return a>b;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }
    sort(arr+1,arr+n+1,cmp);
    long ans=0;
    for(int i=1;i<=n;i++){
        if(!insert(arr[i])){
            ans+=arr[i];
        }
    }
    if(ans==0){
        ans=-1;
    }
    cout<<ans;
    return 0;
}
