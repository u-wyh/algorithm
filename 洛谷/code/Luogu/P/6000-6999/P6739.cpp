// 如果a1不为1  即没有被改变 说明插入的字符一定在s1中 a2同理
// 那么如果a1 a2都是0  说明这一定是不可能的
// 如果a1 a2都是1  但是s1!=s2  说明这个不是唯一的
#include <bits/stdc++.h>
using namespace std;
int n, m, a1, a2;
string u, s1, s2;

int main()
{
	scanf("%d", &n);
	if (n % 2 == 0){
		printf("NOT POSSIBLE\n");
		return 0;
	}
	cin >> u;
	m = n / 2;

	s1 = u.substr(0, m); //匹配检查前M个字符
	int j = 0;
	for (int i = m; i < n && j < m; i++)
		if (u[i] == s1[j])
            j++;
	if (j == m)
        a1 = 1;

	s2 = u.substr(n - m, m); //匹配检查后M个字符
    // cout<<s1<<endl<<s2<<endl;
	j = 0;
	for (int i = 0; i < n - m && j < m; i++)
		if (u[i] == s2[j])
            j++;
	if (j == m)
        a2 = 1;

	if (!a1 && !a2) printf("NOT POSSIBLE\n");
	else if (a1 && a2 && s1 != s2) printf("NOT UNIQUE\n");
	else if (a1) cout << s1 << endl;
	else cout << s2 << endl;
	return 0;
}