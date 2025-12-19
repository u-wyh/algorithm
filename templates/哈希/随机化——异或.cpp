// https://www.luogu.com.cn/problem/P3587
// 4065是一道弱化版的题目
// 通过将同一个种类的所有哈希值异或的结果设置为0  来保证正确性
// 第一问查询方案数  我们可以将划分方案分为两种  第一种是跨过1和n中间线的方案  第二种是没有跨过的
// 但其实没有跨过的和跨过的是互补的  算一种就好的  但是为了第二问  我们只好全算 然后答案要除以二
// 第二问的答案 我们肯定是想让划分的尽量接近n/2 所以对于破环为链的后一半而言  只有两个位置是可以用于选择的
// 第一个是最后一个距离它大于n/2的  第二个是第一个距离他小于n/2的
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXM = MAXN << 1; // 扩展为两倍大小

int n, k;
int nums[MAXN];
int lastpos[MAXN];
long long val[MAXM]; // 注意：val需要两倍空间
long long eorval[MAXN];
long long sum[MAXM]; // 前缀和数组
long long arr[MAXM]; // 离散化数组

vector<int> vec[MAXN]; // 使用MAXM大小
int pos[MAXN]; // 第一问指针
int nxtpos[MAXN]; // 第二问指针

mt19937_64 rng(time(0)); // 64位随机数生成器

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int find(long long val, int m) {
    int l = 1, r = m, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (arr[mid] >= val) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int calc(int cut, int r) {
    return abs(2 * (r - cut) - n); // 简化距离计算公式
}

int main() {
    n = read(), k = read();
    int dis = (n + 1) / 2; // 循环移位中点到右端点的距离
    for (int i = 1; i <= n; i++) {
        nums[i] = read();
        lastpos[nums[i]] = i;
    }

    // 生成随机权值并计算前缀和
    for (int i = 1; i <= n; i++) {
        if (lastpos[nums[i]] == i) {
            val[i] = eorval[nums[i]];
        } else {
            val[i] = rng();
            eorval[nums[i]] ^= val[i];
        }
    }
    for (int i = n + 1; i <= 2 * n; i++) {
        val[i] = val[i - n]; // 复制一份
    }
    for (int i = 1; i <= 2 * n; i++) {
        sum[i] = sum[i - 1] ^ val[i];
        arr[i] = sum[i]; // 复制到离散化数组
    }

    // 离散化
    sort(arr + 1, arr + 2 * n + 1);
    int m = unique(arr + 1, arr + 2 * n + 1) - arr - 1;
    for (int i = 1; i <= 2 * n; i++) {
        sum[i] = find(sum[i], m); // 获取离散化后的值
    }

    // 初始化vec：存储1~n的位置
    for (int i = 1; i <= n; i++) {
        vec[sum[i]].push_back(i);
    }

    long long ans = 0;
    int minans = n;
    for (int i = n + 1; i <= 2 * n; i++) {
        int w = sum[i];
        // 更新第一问指针：跳过超出[i-n, i]区间的位置
        while (pos[w] < (int)vec[w].size() && vec[w][pos[w]] <= i - n) {
            pos[w]++;
        }
        ans += vec[w].size() - pos[w]; // 统计合法对数

        // 更新第二问指针：确保在有效范围内
        nxtpos[w] = max(nxtpos[w], pos[w]);
        while (nxtpos[w] < (int)vec[w].size() - 1 && 
               vec[w][nxtpos[w] + 1] <= i - dis) {
            nxtpos[w]++;
        }

        // 用最近的两个位置更新最小距离
        minans = min(minans, calc(vec[w][nxtpos[w]], i));
        if (nxtpos[w] + 1 < (int)vec[w].size()) {
            minans = min(minans, calc(vec[w][nxtpos[w] + 1], i));
        }

        // 将当前位置加入vec
        vec[w].push_back(i);
    }

    printf("%lld %d\n", ans / 2, minans);
    return 0;
}