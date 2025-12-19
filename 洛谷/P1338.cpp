#include <bits/stdc++.h>
using namespace std;
long long n,m;    //某测试点要开long long才能过
void solve_ (int x,int y) {    //表示调整最后x位，并将第y大的数填入第x位，无需递归
	for (int i=n;i>x;i--) {
		cout << (n-i+1) << ' ';    //第x位前无需调整，升序输出
	}
	cout << (n-y) << ' ';    //第x位输出剩余x个数中第y大的数
	for (int i=n;i>=(n-x+1);i--) {
		if (i!=(n-y)) {
			cout << i << ' ';    //最后x-1个数降序输出，注意判一下是否在前面输出过
		}
	}
	return;
}
int main () {
	cin >> n >> m;
	if (m==0) {    //0的特判
		for (int i=1;i<=n;i++) {
			cout << i << ' ';
		}
		return 0;
	}
	for (long long i=2;i<=n;i++) {
		if ((i*(i-1))/2>=m&&((i-1)*(i-2))/2<m) {
			solve_(i,(i*(i-1))/2-m);
			break;
		}
	}
	return 0;
}
