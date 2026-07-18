// 牛牛的背包问题 & 世界冰球锦标赛
// 牛牛准备参加学校组织的春游, 出发前牛牛准备往背包里装入一些零食, 牛牛的背包容量为w。
// 牛牛家里一共有n袋零食, 第i袋零食体积为v[i]。
// 牛牛想知道在总体积不超过背包容量的情况下,他一共有多少种零食放法(总体积为0也算一种放法)。
// 输入描述：
// 输入包括两行
// 第一行为两个正整数n和w(1 <= n <= 30, 1 <= w <= 2 * 10^9),表示零食的数量和背包的容量
// 第二行n个正整数v[i](0 <= v[i] <= 10^9),表示每袋零食的体积
// 输出描述：
// 输出一个正整数, 表示牛牛一共有多少种零食放法。
// 测试链接 : https://www.luogu.com.cn/problem/P4799
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过
//这种才是双向广搜的本体用法
//即必须要全部展开 但是时间复杂度不允许  eg:2^40(10^12)
//所以我们将左右两边分别展开  最后将左右两边信息合并起来  得到汇总信息
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 40;
const int MAXM = 1 << 20;

long arr[MAXN];
long lsum[MAXM];//左边展开的信息
long rsum[MAXM];//右边展开的信息
int n;
long w;

//暴力展开 从i开始到e结束  不要超过w  因为超过w没有任何意义
//目前已经有了j个答案  暂时总和是s
//递归函数  会一直递归到i==e
//返回值是自己可以得到的最终答案
int f(int i, int e, long s, long w, long* ans, int j) {
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

long compute(){
    int lsize = f(0, n >> 1, 0, w, lsum, 0);
    int rsize = f(n >> 1, n, 0, w, rsum, 0);
    sort(lsum, lsum+lsize);
    sort(rsum, rsum+rsize);
    long ans = 0;
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