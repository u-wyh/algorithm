#include <bits/stdc++.h>
using namespace std;
#define int long long
int f[305] ;
int n, m ;
string s ;
string d[605] ;
signed main() {
	cin >> n >> m ;
	cin >> s ;
	for(int i = 1 ; i <= n ; i++) cin >> d[i] ;
	memset(f, 0x3f, sizeof(f)) ; //要求最小值，初始化成INF
	f[0] = 0 ; //边界 f[0] = 0
	for(int i = 1 ; i <= m ; i++) {
		f[i] = f[i - 1] + 1 ;
		for(int j = 1 ; j <= n ; j++) {
			int r1 = i, r2 = d[j].size() ;//指针的思想
			int flag = 1 ;//记录是否可以匹配成功
			while(r1 && r2) {
				if(d[j][r2 - 1] == s[r1 - 1]) r1--, r2-- ; //若匹配成功，各向前移一位
				else r1-- ; // 不然 把母串指针前移一位
				if(!r2) flag = 0 ; //匹配成功
			}
			if(!flag) f[i] = min(f[r1] + i - r1 - (int)d[j].size(), f[i]) ; // 若匹配成功，转移
		}
	}
	cout << f[m] ;
	return 0 ;
}
