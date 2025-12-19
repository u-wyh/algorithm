#include<bits/stdc++.h>
using namespace std;
long long n, a, b;
long long f[100];
int main() {
	cin>>n;
	f[0] = 1;
	f[1] = 1;
	for(int i = 2; i <= 59; i++)
		f[i] = f[i - 1] + f[i - 2];
	for(int i = 1; i <= n; i++) {
		scanf("%lld %lld", &a, &b);
		while(a != b) {
			if(b < a) {
				long long k = a;
				a = b;
				b = k;
			}
			int l = 1, r = 59;
			while(l <= r) {
				int mid = (l + r) / 2;
				if(f[mid] < b)
				    l = mid + 1;
				else
				    r = mid - 1;
			}
			b -= f[l - 1];
		}
		printf("%lld\n", a);
	}
	return 0;
}
