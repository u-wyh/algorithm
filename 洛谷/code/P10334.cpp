// https://www.luogu.com.cn/problem/P10334
// 题意：果汁机每分钟可做一杯任意体积的果汁。
// 第 i 人在 t[i] 分钟拿走库存中最大的一杯，对体积的最低要求为 a[i]，同一时刻按输入顺序取。
// 求满足所有人需要的最小总体积，无解输出 -1。
// 数据范围：1 ≤ n ≤ 10^5，1 ≤ t[1] ≤ … ≤ t[n] ≤ 10^9，1 ≤ a[i] ≤ 10^9。

#include <bits/stdc++.h>
using namespace std;

stack <int> st;
int t[300005],m[300005];
long long ans;

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t[i];
		if(t[i]<i){
			cout<<-1;
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		cin>>m[i];
	}
	int dw=n;
	for(int i=t[n];i>=1;i--){
		if(t[dw]<i){
        //当下一个人还没来取果汁时，就可以先制作后面的
			if(st.size()){
				ans+=st.top();
				st.pop();
			}
		}else if(t[dw]==i){
        //当下一个人已经来取果汁时，就立刻制作他的
			if(st.size())
                st.push(max(st.top(),m[dw]));
			else
                st.push(m[dw]);
			dw--,i++;
		}else if(t[dw]>i)
            dw--,i++;
      //当下一个人和上一个人同时取果汁时就要存到栈里提前制作。
	}

	while(st.size()){
		ans+=st.top();
		st.pop();
	}
	cout<<ans;
	return 0;
}
