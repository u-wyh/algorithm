// ST表查询最大公约数
// 给定一个长度为n的数组arr，一共有m次查询
// 每次查询arr[l~r]上所有数的最大公约数
// 测试链接 : https://www.luogu.com.cn/problem/P1890
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
const int LIMIT = 11;

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
        for(int j=1;j<=n;j++){
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