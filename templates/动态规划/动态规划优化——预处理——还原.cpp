// 还原数组的方法数(优化枚举)
// 原本有一个长度为n的数组arr，下标从1开始，数组中都是<=200的正数
// 并且任意i位置的数字都满足 : arr[i] <= max(arr[i-1], arr[i+1])
// 特别的，arr[1] <= arr[2]，arr[n] <= arr[n-1]
// 但是输入的arr中有些数字丢失了，丢失的数字用0表示
// 返回还原成不违规的arr有多少种方法，答案对 998244353 取模
// 3 <= n <= 10^4
// 测试链接 : https://www.nowcoder.com/practice/49c5284278974cbda474ec13d8bd86a9
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
//这种预处理方式是加速枚举过程  比如  如果要求连续多个上一层的状态 那么可以用前缀和  从而不用遍历的方式  实现加速
//这道题的dp[i][j][k]意思是 前i个数字需要还原(即处理的范围是1~i) 右侧已经全部确定  i+1位置的数字是j  
//k是0 则表示 s[i+1]>[i+2]  否则就是小于等于
//那么最终答案就是dp[n][0][1]  即要处理的是前n个位置  最后一个位置n肯定要比n+1大   那么将n+1设置为0
//我们将n+2>n+1  表示我们这里不需要使用前n个来满足第n+1位置的了
//如果上一个位置上的数字是v  那么这个位置不管上一个s是什么 一定可以是v+1~m   
//因为如果s是0  表示i+1>i+2  但是i+1<max(i+2,i)  所以v+1~m可以   如果s是1  那么说明i+1位置已经被满足了  那么这个位置可以随便填
//如果这个位置数字填v  也是同样的  但是我们要注意这个v不能是0  因为一开始我们调用的是dp[n][0][1]
//如果我们想尝试小于v的数字 那么s必须要是1  否则  i+1>i&&i+1>i+2
//那么dp[i][j][0/1] = dp[i-1][j+1~m][0]  意思是i-1这个位置上大于i的方案
//如果j!=0  dp[i][j][0/1] += dp[i-1][v][1]
//如果s是1  那么 +dp[i-1][1~j-1][1]
#include <iostream>
#include <vector>
#include <utility>
using namespace std;
const int MOD = 998244353;
const int MAXN = 10000;
const int M = 200;

int arr[MAXN + 1];
int n;
int memo[M + 1][2];
int dp[M + 1][2];
int suf0[M + 1];//0列后缀和
int pre1[M + 1];//1列前缀和

void prepare() {
    suf0[M] = memo[M][0];
    for (int v = M - 1; v >= 0; --v) {
        suf0[v] = (suf0[v + 1] + memo[v][0]) % MOD;
    }
    pre1[1] = memo[1][1];
    for (int v = 2; v <= M; ++v) {
        pre1[v] = (pre1[v - 1] + memo[v][1]) % MOD;
    }
}

int compute() {
    for (int v = 0; v <= M; ++v) {
        memo[v][0] = 0;
        memo[v][1] = 1;//滚动更新  状态压缩
    }
    for (int i = 1; i <= n; ++i) {
        prepare();
        for (int v = 0; v <= M; ++v) {
            for (int s = 0; s <= 1; ++s) {
                int ans = 0;
                if (arr[i] != 0) {
                    //如果这个值是固定值 那么没什么好说的  直接就是他
                    if (arr[i] >= v || s == 1) {
                        ans = memo[arr[i]][arr[i] > v ? 0 : 1];
                    }
                } else {
                    if (v + 1 <= M) {
                        ans = (ans + suf0[v + 1]) % MOD;
                    }
                    if (v != 0) {
                        ans = (ans + memo[v][1]) % MOD;
                    }
                    if (s == 1) {
                        if (v - 1 >= 0) {
                            ans = (ans + pre1[v - 1]) % MOD;
                        }
                    }
                }
                dp[v][s] = ans;
            }
        }
        for (int v = 0; v <= M; ++v) {
            for (int s = 0; s <= 1; ++s) {
                swap(memo[v][s], dp[v][s]);
            }
        }
    }
    return memo[0][1];
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    cout << compute() << endl;
    return 0;
}
