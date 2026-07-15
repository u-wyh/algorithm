#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 500*500+100;

int temp[N];

ll msort(int l, int r, int *a) {
	if (l>=r) return 0;
	int mid = l+r>>1, k=0;
	ll res = msort(l, mid, a)+msort(mid+1, r, a);
	int i = l, j = mid+1;
	while (i<=mid && j<=r)
		if (a[i]<=a[j]) temp[k++] = a[i++];
		else temp[k++] = a[j++], res += (mid-i+1);
	while (i<=mid) temp[k++] = a[i++];
	while (j<=r) temp[k++] = a[j++];
	for (i=l, j=0; i<=r; i++, j++) a[i] = temp[j];
	return res;
}

int st[N], en[N];

int main()
{
	for (int n; cin >> n;) {
		n*=n;
		for(int i=1, x, f=0; i<=n&&cin>>x; i++, f|=(!x)) st[i-f] = x;
		for(int i=1, x, f=0; i<=n&&cin>>x; i++, f|=(!x)) en[i-f] = x;
		ll u = msort(1, n - 1, st);
		ll v = msort(1, n - 1, en);
		if((u&1)==(v&1)) cout << "TAK\n";
		else cout << "NIE\n";
	}
	return 0;
}
