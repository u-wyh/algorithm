#include <iostream>
#include <cstdio>
using namespace std;

const int N = 27;

int n, m, ans(N * N), s;
int e[N], cnt1[(1 << (N / 2)) + 10];

int Count1(int x) {
	return cnt1[x >> (N/2)] + cnt1[x - ((x >> N/2) << N/2)];
}

void dfs(int pos, int k, int sum, int s1, int s2) {
    //k是第一个集合中的点的个数
    //sum是我们想要求的答案即有多少个顶点位于两个集合的线段
    //s1 s2分别表示两个集合的端点情况
    //pos表示现在到了第几个点  考虑是否要将它放到是s1中
	if(k == n / 2) {
		if(sum < ans)
            s = s1, ans = sum;
		return ;
	}
	for(int i=pos+1, ns2; i<=n; i++) {
		ns2 = s2 ^ (1 << i-1);
		dfs(i, k+1, sum - Count1(e[i] & s1) + Count1(e[i] & ns2), s1 | (1 << i-1), ns2);
		// sum - Count1(e[i] & s1) + Count1(e[i] & ns2):每次选一个点i加入S1时，减去原S1与i连的边数，加上i与新S2连的边数.
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i=0; i<1<<(N/2); i++)
		cnt1[i] = cnt1[i>>1] + (i & 1);
    //预处理出每一个数字的二进制有几个1
	for(int i=1, u, v; i<=m; i++) {
		scanf("%d%d", &u, &v);
		e[u] |= (1 << v-1);
		e[v] |= (1 << u-1);
		//以二进制的方式储存相连的边的信息
	}
	dfs(0, 0, 0, 0, (1<<n)-1);

	for(int i=1; i<=n; i++)
		if(s >> i-1 & 1)
            printf("%d ", i);
	printf("\n");
	return 0;
}
