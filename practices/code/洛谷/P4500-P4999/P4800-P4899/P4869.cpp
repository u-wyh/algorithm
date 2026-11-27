// https://www.luogu.com.cn/problem/P4869
// 题意：给定长为 n 的正整数序列 A，
// 将 A 的全部 2^n 个子集异或和从小到大排序成序列 B（下标从 1 开始）
// 求给定数 Q 在 B 中第一次出现时的下标模 10086。
// 数据范围：1 <= N <= 10^5，其余输入数均不超过 10^9，
// 保证 Q 在 B 中出现。
// 算法标签：线性基、高斯消元、位运算
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int BIT = 30;
const int MOD = 10086;

int n;
int len;
bool zero;
int arr[MAXN];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void compute() {
    len = 1;
    for (int i = BIT; i >= 0; i--) {
        for (int j = len; j <= n; j++) {
            if (arr[j] & (1LL << i)) {
                swap(arr[j], arr[len]);
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

signed main()
{
    n=read();
    for(int i=1;i<=n;i++){
        arr[i]=read();
    }
    compute();
    int p=1;
    for(int i=1;i<=n-len;i++){
        p=(p*2)%MOD;
    }

    int val=read();
    sort(arr+1,arr+len+1);
    int u=0;
    for(int i=1;i<=len;i++){
        while(arr[i]>=(1ll<<u)){
            u++;
        }
        arr[i]=u-1;
    }
    // int tmp=1;
    int k=0;
    for(int i=1;i<=len;i++){
        if(val&(1<<arr[i])){
            k=(k+(1<<(i-1)))%MOD;
        }
    }
    k+=zero;
    k-=1;
    int ans=0;
    ans=(k*p+1)%MOD;
    cout<<ans<<endl;
    return 0;
}