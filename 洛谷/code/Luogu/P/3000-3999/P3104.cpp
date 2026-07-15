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
