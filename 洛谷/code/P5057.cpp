#include <bits/stdc++.h>
using namespace std;

int N, M, B[100001];

inline void A(int i) {
    for (; i <= N; i += i & -i)
        B[i] ^= 1;
}

inline int Q(int i) {
    int A = 0;
    for (; i; i -= i & -i)
        A ^= B[i];
    return A;
}

int main() {
	cin>>N>>M;
	while (M--) {
		int opt, l, r;
		cin>>opt>>l;
		if (opt == 1) A(l), scanf("%d", &r), A(r + 1);
		else printf("%d\n", Q(l));
	}
	return 0;
}
