// 用途：康托展开求排列的字典序排名。
// 时间：O(n log n)。
// 空间：O(n)。
// 例题：https://www.luogu.com.cn/problem/P5367
// 题意：求给定排列在所有排列中字典序排第几。
// 思路：逐位统计未使用且更小的数，乘剩余位置阶乘求贡献。
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1000001;
const int MOD = 998244353;

int arr[MAXN];
// 阶乘余数表
int fac[MAXN];
// 树状数组
int tree[MAXN];
int n;

//以下部分是树状数组用于求和
int lowbit(int x){
    return x & -x;
}

void add(int i,int v){
    while(i<=n){
        tree[i]+=v;
        i+=lowbit(i);
        //每一次都加上自己最右侧的1
        //相当于把所有包含该状态的数字都增加
    }
}

//这个函数求的是从1到i所有数字的和
int sum(int i){
    int ans=0;
    while(i>0){
        ans+=tree[i];
        i-=lowbit(i);
        //每一次都减去自己最右侧的1
        //相当于将整个区间拆分开为几个小区间加速  和乘法快速幂相似
    }
    return ans;
}

int query(int l,int r){
    return sum(r)-sum(l-1);
}

signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }

    //建立阶乘表
    fac[0]=1;
    for(int i=1;i<n;i++){
        fac[i]=(fac[i-1]*i)%MOD;
    }

    for(int i=1;i<=n;i++){
        add(i,1);
    }
    //将树状数组初始化
    long long ans=0;
    for(int i=1;i<=n;i++){
        ans=(ans+(fac[n-i]*sum(arr[i]-1))%MOD)%MOD;
        add(arr[i],-1);//将这一位的信息去除
    }
    ans=(ans+1)%MOD;
    cout<<ans<<endl;
    return 0;
}
