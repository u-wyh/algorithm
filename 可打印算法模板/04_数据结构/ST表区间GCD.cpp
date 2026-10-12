// 用途：静态数组区间最大公约数查询。
// 时间：预处理 O(n log n)，单次查询 O(1)。
// 空间：O(n log n)。
// 注意：只支持查询；n<=5000，预处理 O(n log n)。
// 例题：https://www.luogu.com.cn/problem/P1890
// 题意：静态数组多次查询区间最大公约数。
// 思路：预处理 2 的幂长区间 GCD，询问时拼接两个覆盖块。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int LIMIT = 13;

// st[i][k] 保存从 i 开始长度 2^k 区间的 GCD。
int st[MAXN][LIMIT];
int arr[MAXN];
int Log2[MAXN];
int n,m;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void build(int n){
    Log2[0]=-1;
    for(int i=1;i<=n;i++){
        Log2[i]=Log2[i>>1]+1;
        st[i][0]=arr[i];
    }
    for(int i=1;i<=Log2[n];i++){
        for(int j=1;j+(1<<i)-1<=n;j++){
            st[j][i]=gcd(st[j][i-1],st[j+(1<<(i-1))][i-1]);
        }
    }
}

int query(int l,int r){
    int p=Log2[r-l+1];
    return gcd(st[l][p],st[r-(1<<p)+1][p]);
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>arr[i];
    build(n);
    while(m--){
        int l,r;
        cin>>l>>r;
        cout<<query(l,r)<<endl;
    }
    return 0;
}
