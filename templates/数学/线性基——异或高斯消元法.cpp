// 第k小的异或和
// 给定一个长度为n的数组arr，arr中都是long类型的非负数，可能有重复值
// 在这些数中选取任意个，至少要选一个数字
// 可以得到很多异或和，假设异或和的结果去重
// 返回第k小的异或和
// 1 <= n <= 10^5
// 0 <= arr[i] <= 2^50
// 1 <= k <= 2^50
// 测试链接 : https://loj.ac/p/114
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
//通过这种方法得到的线性基是唯一的  可以求出第k小的异或和
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int BIT = 50;

long arr[MAXN];
int len;
bool zero;
int n;

void swap(int a, int b) {
    long long tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

//这个是高斯消元法  得到的是标准线性基
void compute() {
    len = 1;
    for (int i = BIT; i >= 0; i--) {
        for (int j = len; j <= n; j++) {
            if (arr[j] & (1LL << i)) {
                swap(j, len);//这里是对的 改成swap(arr[j], arr[len]);也可以通过
                break;
            }
        }
        if (arr[len] & (1LL << i)) {
            //表示找到了这一位上是1的数字
            for (int j = 1; j <= n; j++) {
                //将所有这一位置上是1的数字全部异或掉
                if (j != len && (arr[j] & (1LL << i))) {
                    arr[j] ^= arr[len];
                }
            }
            len++;
        }
    }
    len--;//表示有len位可以确定
    zero = len != n;
}

// 返回第k小的异或和
long query(long k) {
	if (zero && k == 1) {
        //如果有0  并且查询第一小的数字
        //那么直接返回0就好了
		return 0;
	}
	if (zero) {
	    //如果有0  那么k就要减1
	    //因为我们统计的是异或后不产生0的线性基
		k--;
	}
	if (k >= 1L << len) {
        //超出范围
		return -1;
	}
	long ans = 0;
	for (int i = len, j = 0; i >= 1; i--, j++) {
		if ((k & (1L << j)) != 0) {
			ans ^= arr[i];
		}
	}
	return ans;
}

int main()
{
    cin>>n;
    for (int i = 1; i <= n; i++) {
        cin>>arr[i] ;
    }
    compute();
    int q ;
    cin>>q;
    for (int i = 1; i <= q; i++) {
        long k ;
        cin>>k;
        cout<<query(k)<<endl;
    }
    return 0;
}