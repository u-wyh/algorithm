// 用途：折半枚举两组子集和，计数总重量不超过上限的选取方案。
// 时间：O(n×2^(n/2))，包括排序。
// 空间：O(2^(n/2))。
// 注意：n≤40、重量非负；总和及方案数可能超过 32 位，统一用 long long。
// 例题：https://www.luogu.com.cn/problem/P4799
// 题意：给定若干物品，统计总重量不超过上限的子集数。
// 思路：物品分两半枚举子集和，排序后用双指针统计可配对数量。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 40;
const int MAXM = 1 << 20;

long long arr[MAXN];
long long lsum[MAXM];//左边展开的信息
long long rsum[MAXM];//右边展开的信息
int n;
long long w;

//暴力展开 从i开始到e结束  不要超过w  因为超过w没有任何意义
//目前已经有了j个答案  暂时总和是s
//递归函数  会一直递归到i==e
//返回值是自己可以得到的最终答案
int f(int i, int e, long long s, long long w, long long* ans, int j) {
    if (s > w) {
        return j;
    }
    // s <= w
    if (i == e) {
        //表示到了可以选择的最后一个物品了  记录可行答案的值  填入相应的答案记录数组中
        ans[j++] = s;
    } else {
        // 不要arr[i]位置的数
        j = f(i + 1, e, s, w, ans, j);
        // 要arr[i]位置的数
        j = f(i + 1, e, s + arr[i], w, ans, j);
    }
    return j;
}

long long compute(){
    int lsize = f(0, n >> 1, 0, w, lsum, 0);
    int rsize = f(n >> 1, n, 0, w, rsum, 0);
    sort(lsum, lsum+lsize);
    sort(rsum, rsum+rsize);
    long long ans = 0;
    //汇总左右两边信息 双指针
    for (int i = lsize - 1, j = 0; i >= 0; i--) {
        while (j < rsize && lsum[i] + rsum[j] <= w) {
            j++;
        }
        ans += j;
    }
    return ans;
}

int main()
{
    cin>>n>>w;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<compute();
    return 0;
}
