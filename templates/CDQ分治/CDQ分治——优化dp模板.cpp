// 拦截导弹，C++版
// 一共有n个导弹，编号1~n，表示导弹从早到晚依次到达，每个导弹给定，高度h、速度v
// 你有导弹拦截系统，第1次可以拦截任意参数的导弹
// 但是之后拦截的导弹，高度和速度都不能比前一次拦截的导弹大
// 你的目的是尽可能多的拦截导弹，如果有多个最优方案，会随机选一个执行
// 打印最多能拦截几个导弹，并且打印每个导弹被拦截的概率
// 1 <= n <= 5 * 10^4
// 1 <= h、v <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P2487
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题的树状数组维持的是最大值以及出现的次数  可以更新（添加）、查询  但是不可以修改和删除
//这道题的难点是求每个导弹被拦截的概率  我们首先可以求出最多的可以被拦截的导弹有多少个
//并且要求出有多少种方案可以实现这种方法  也就是求出max(以i为结尾的最长不上升子序列长度) 和sum(相应的个数)
//并且要求出:1、i位置结尾的情况下，最长不上升子序列的长度 及其 子序列个数
//          2、i位置开头的情况下，最长不上升子序列的长度 及其 子序列个数
//这样我们就可以求出包含这个导弹的最长不上升子序列长度  以及 个数
//如果长度就是最长的  那么概率就是  符合条件的个数/总数
//这道题的第一维实际上是按照下标排序
// cdq分治优化动态规划的时候  在merge过程中都需要拷贝到另外一个数组中  因为右侧部分还没有开始cdq
#include <bits/stdc++.h>   
using namespace std;
const int MAXN = 50001;

int n, s;
int h[MAXN];
int v[MAXN];
int sortv[MAXN];//我们要在速度上进行树状数组  所以要离散化

// 位置i、高度h、速度v
struct Node {
    int i, h, v;
};

Node arr[MAXN];

// 树状数组维护前缀最大值、最大值出现的次数
//因为最后要计算概率  所以将次数设置为double类型
int treeVal[MAXN];
double treeCnt[MAXN];

// i位置结尾的情况下，最长不上升子序列的长度 及其 子序列个数
int len1[MAXN];
double cnt1[MAXN];

// i位置开头的情况下，最长不上升子序列的长度 及其 子序列个数
int len2[MAXN];
double cnt2[MAXN];

bool Cmp1(Node a, Node b) {
    return a.h > b.h;
}

bool Cmp2(Node a, Node b) {
    return a.h < b.h;
}

int lowbit(int i) {
    return i & -i;
}

void more(int i, int val, double cnt) {
    while (i <= s) {
        if (val > treeVal[i]) {
            treeVal[i] = val;
            treeCnt[i] = cnt;
        } else if (val == treeVal[i]) {
            treeCnt[i] += cnt;
        }
        i += lowbit(i);
    }
}

int queryVal;
double queryCnt;

void query(int i) {
    queryVal = 0;
    queryCnt = 0;
    while (i > 0) {
        if (treeVal[i] > queryVal) {
            queryVal = treeVal[i];
            queryCnt = treeCnt[i];
        } else if (treeVal[i] == queryVal) {
            queryCnt += treeCnt[i];
        }
        i -= lowbit(i);
    }
}

void clear(int i) {
    while (i <= s) {
        treeVal[i] = 0;
        treeCnt[i] = 0;
        i += lowbit(i);
    }
}

void merge1(int l, int m, int r) {
    //先拷贝一份  不在原数组上操作 防止破坏顺序
    for (int i = l; i <= r; i++) {
        arr[i].i = i;
        arr[i].h = h[i];
        arr[i].v = v[i];
    }
    sort(arr + l, arr + m + 1, Cmp1);
    sort(arr + m + 1, arr + r + 1, Cmp1);
    int p1, p2;
    // 为了防止出现0下标，(s - v + 1)是树状数组的下标
    //这样是为了方便求前缀  因为符合条件的v一定要大于当前值  小于的不能用于更新
    //所以使用(s-v+1)  s是离散化后v的最大值
    for (p1 = l - 1, p2 = m + 1; p2 <= r; p2++) {
        while (p1 + 1 <= m && arr[p1 + 1].h >= arr[p2].h) {
            p1++;
            more(s - arr[p1].v + 1, len1[arr[p1].i], cnt1[arr[p1].i]);
        }
        query(s - arr[p2].v + 1);
        if (queryVal + 1 > len1[arr[p2].i]) {
            len1[arr[p2].i] = queryVal + 1;
            cnt1[arr[p2].i] = queryCnt;
        } else if (queryVal + 1 == len1[arr[p2].i]) {
            cnt1[arr[p2].i] += queryCnt;
        }
    }
    //复原操作
    for (int i = l; i <= p1; i++) {
        clear(s - arr[i].v + 1);
    }
}

// 最长不上升子序列的长度 及其 个数
void cdq1(int l, int r) {
    if (l == r) {
        return;
    }
    int m = (l + r) / 2;
    cdq1(l, m);
    merge1(l, m, r);
    cdq1(m + 1, r);
}

// 最长不下降子序列的长度 及其 个数
void merge2(int l, int m, int r) {
    for (int i = l; i <= r; i++) {
        arr[i].i = i;
        arr[i].h = h[i];
        arr[i].v = v[i];
    }
    sort(arr + l, arr + m + 1, Cmp2);
    sort(arr + m + 1, arr + r + 1, Cmp2);
    int p1, p2;
    //这里求得是最长不下降  那么就是v必须要小于当前值才能用  所以这里不需要用(s-v+1)
    for (p1 = l - 1, p2 = m + 1; p2 <= r; p2++) {
        while (p1 + 1 <= m && arr[p1 + 1].h <= arr[p2].h) {
            p1++;
            more(arr[p1].v, len2[arr[p1].i], cnt2[arr[p1].i]);
        }
        query(arr[p2].v);
        if (queryVal + 1 > len2[arr[p2].i]) {
            len2[arr[p2].i] = queryVal + 1;
            cnt2[arr[p2].i] = queryCnt;
        } else if (queryVal + 1 == len2[arr[p2].i]) {
            cnt2[arr[p2].i] += queryCnt;
        }
    }
    for (int i = l; i <= p1; i++) {
        clear(arr[i].v);
    }
}

void cdq2(int l, int r) {
    if (l == r) {
        return;
    }
    int m = (l + r) / 2;
    cdq2(l, m);
    merge2(l, m, r);
    cdq2(m + 1, r);
}

int lower(int num) {
    int l = 1, r = s, ans = 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (sortv[mid] >= num) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

void prepare() {
    //速度离散化
    for (int i = 1; i <= n; i++) {
        sortv[i] = v[i];
    }
    sort(sortv + 1, sortv + n + 1);
    s = 1;
    for (int i = 2; i <= n; i++) {
        if (sortv[s] != sortv[i]) {
            sortv[++s] = sortv[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        v[i] = lower(v[i]);
    }
    //初始化长度以及个数
    for (int i = 1; i <= n; i++) {
        len1[i] = len2[i] = 1;
        cnt1[i] = cnt2[i] = 1.0;
    }
}

void compute() {
    //求出以每个节点为尾的最长不上升子序列长度以及个数
    cdq1(1, n);

    //求出以每个节点为头的最长不上升子序列长度以及个数  相当于求出全部逆序后的 最长不下降子序列的长度 及其 个数
    for (int l = 1, r = n; l < r; l++, r--) {
        swap(h[l], h[r]);
        swap(v[l], v[r]);
    }
    cdq2(1, n);
    //复原位置
    for (int l = 1, r = n; l < r; l++, r--) {
        swap(len2[l], len2[r]);
        swap(cnt2[l], cnt2[r]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &h[i], &v[i]);
    }
    prepare();
    compute();
    int len = 0;
    double cnt = 0.0;
    for (int i = 1; i <= n; i++) {
        len = max(len, len1[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (len1[i] == len) {
            cnt += cnt1[i];//求出总方案数
        }
    }
    printf("%d\n", len);
    for (int i = 1; i <= n; i++) {
        if (len1[i] + len2[i] - 1 < len) {
            //无法被拦截
            printf("0 ");
        } else {
            printf("%.5f ", cnt1[i] * cnt2[i] / cnt);
        }
    }
    printf("\n");
    return 0;
}