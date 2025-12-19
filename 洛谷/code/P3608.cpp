#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
struct sCow
{
	int iH, iBh;
}Cow[N];
bool cmp(sCow x, sCow y){return x.iH > y.iH;}
int iSum[N], n;
int lowbit(int x) {return x & -x;}
void Add(int x, int k){for(; x <= n; x += lowbit(x)) iSum[x] += k;}
int Query(int x){int ans = 0;for(; x; x -= lowbit(x)) ans += iSum[x];return ans;}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &Cow[i].iH), Cow[i].iBh = i;
	sort(Cow + 1, Cow + 1 + n, cmp);
	int iAns = 0;
	for(int i = 1; i <= n; i++)
	{
		Add(Cow[i].iBh, 1);
		int l = Query(Cow[i].iBh - 1);
		int r = i - l - 1;
		if(max(l, r) > 2 * min(l, r)) iAns++;
	}
	cout<<iAns;
}
