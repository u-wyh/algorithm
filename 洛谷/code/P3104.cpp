// https://www.luogu.com.cn/problem/P3104
// 题意：输入奶牛数 N，以及一个长度为 N+1 的整数列表。
// 列表本来记录了 N 头牛各自的朋友数量（朋友关系是双向的，不能自己和自己做朋友，一对牛最多当一次朋友），但被误添了 1 个多余数字。
// 找出所有可能的错误位置编号（1 到 N+1），使得删掉该位置的数后，剩下 N 个数能对应一组合法的朋友关系。
// 第一行输出可行位置个数 K，接下来 K 行按从小到大输出可行位置编号（K=0 时只输出 0）。
// 数据范围：2 <= N <= 500。
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n, a[502], b[500],c[500],sum=0;
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; i++)
	{
		scanf("%d", &a[i]);
		sum += a[i];
	}
	int num = 0, res[501];
	for (int i = 1; i <= n + 1; i++){
		if (sum % 2 != a[i] % 2)
			continue;
		int index = 0;
		for (int j = 1; j <= n + 1; j++)
			if (j != i)
				b[index++] = a[j];
		sort(b, b + n, [](const int x, const int y) {
			return x > y;
        });
		bool flag = 1;
		for (int j = 1; j <= n; j++){
			if (b[0] == 0)
				break;
			int in = 1;
			while (b[0] > 0 && b[in] > 0){
				b[0]--;
				b[in++]--;
			}
			if (b[0] > 0){
				flag = 0;
				break;
			}
			int p = 1, q = in, cnt = 0;
			while (p < in && q < n)
				if (b[p] > b[q])
					c[cnt++] = b[p++];
				else
					c[cnt++] = b[q++];
			while (p < in)
				c[cnt++] = b[p++];
			while (q < n)
				c[cnt++] = b[q++];
			for (int k = 0; k < n - 1; k++)
				b[k] = c[k];
			b[n - 1] = 0;
		}
		if (flag)
			res[num++] = i;
	}
	printf("%d\n", num);
	for (int i = 0; i < num; i++)
		printf("%d\n", res[i]);
	return 0;
}
