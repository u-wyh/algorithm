// https://www.luogu.com.cn/problem/P11012
// 题意：给 n 幅画的颜料编号，选一个连续区间。
// 每对不同颜料贡献两者在区间里出现次数的较小值。
// 要求所有颜料对的贡献和至少为 k，输出最短区间长度，无解输出 -1。
// 数据范围：1 ≤ n,a[i] ≤ 2 × 10^6，
// 1 ≤ k ≤ 10^15。
// 算法标签：滑动窗口、计数统计

#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e6+10;

ll read(){
    ll X = 0 ,r = 1;
    char ch = getchar();
    while(!isdigit(ch) && ch != '-') ch = getchar();
    if(ch == '-') r = -1,ch = getchar();
    while(isdigit(ch)) X = X*10+ch-'0',ch = getchar();
    return X*r;
}

int n,a[N],m;
int cnt[N],sz[N];
ll k;

int main()
{
	n = read();
	k = read();
	for(int i=1;i<=n;i++)
        a[i] = read();
	int ans = n+1;
	ll res = 0;
	for(int l=1,r=0;l<=n;l++){
		while(r < n && res < k){
			r++;
            sz[a[r]]++;
			cnt[sz[a[r]]]++;
			res += cnt[sz[a[r]]]-1;
		}
		if(res >= k)
            ans = min(ans,r-l+1);
		res -= cnt[sz[a[l]]]-1;
		cnt[sz[a[l]]]--;
		sz[a[l]]--;
	}
	printf("%d",ans == n+1 ? -1 : ans);
    return 0;
}
