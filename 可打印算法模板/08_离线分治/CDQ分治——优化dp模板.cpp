// 用途：CDQ 优化二维偏序 DP，求最长拦截长度与各点入选概率。
// 时间：O(n log² n)。
// 空间：O(n)。
// 例题：https://www.luogu.com.cn/problem/P2487
// 题意：按发射顺序选高度、速度均不上升的导弹，求最长长度及每枚导弹出现在随机最优方案中的概率。
// 思路：CDQ 分别求以每枚导弹为终点、起点的最长长度和方案数；两侧方案数相乘后除以总方案数。
#include <bits/stdc++.h>   
using namespace std;
const int MAXN = 50001;
const long double NO_WAYS = -1e100L;

// 方案数可能达到 2^25000，改存其对数；相加时用 log-sum-exp。
long double addWays(long double a, long double b) {
    if (a == NO_WAYS) return b;
    if (b == NO_WAYS) return a;
    if (a < b) swap(a, b);
    if (a - b > 50) return a;
    return a + log1pl(expl(b - a));
}

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
// 次数均存 log(方案数)，防止大量最长方案造成浮点溢出。
int treeVal[MAXN];
long double treeCnt[MAXN];

// i位置结尾的情况下，最长不上升子序列的长度 及其 子序列个数
int len1[MAXN];
long double cnt1[MAXN];

// i位置开头的情况下，最长不上升子序列的长度 及其 子序列个数
int len2[MAXN];
long double cnt2[MAXN];

bool Cmp1(Node a, Node b) {
    return a.h > b.h;
}

bool Cmp2(Node a, Node b) {
    return a.h < b.h;
}

int lowbit(int i) {
    return i & -i;
}

void more(int i, int val, long double cnt) {
    // 树状数组维护最大长度；长度相同的前驱方案数相加。
    while (i <= s) {
        if (val > treeVal[i]) {
            treeVal[i] = val;
            treeCnt[i] = cnt;
        } else if (val == treeVal[i]) {
            treeCnt[i] = addWays(treeCnt[i], cnt);
        }
        i += lowbit(i);
    }
}

int queryVal;
long double queryCnt;

void query(int i) {
    queryVal = 0;
    queryCnt = NO_WAYS;
    while (i > 0) {
        if (treeVal[i] == 0) {
            i -= lowbit(i);
            continue;
        }
        if (treeVal[i] > queryVal) {
            queryVal = treeVal[i];
            queryCnt = treeCnt[i];
        } else if (treeVal[i] == queryVal) {
            queryCnt = addWays(queryCnt, treeCnt[i]);
        }
        i -= lowbit(i);
    }
}

void clear(int i) {
    while (i <= s) {
        treeVal[i] = 0;
        treeCnt[i] = NO_WAYS;
        i += lowbit(i);
    }
}

void merge1(int l, int m, int r) {
    // 左半时间早于右半；按高度扫描，速度反向离散化后做前缀查询。
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
            cnt1[arr[p2].i] = addWays(cnt1[arr[p2].i], queryCnt);
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
    // 原序列倒过来后，求从当前导弹出发的最长合法后缀。
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
            cnt2[arr[p2].i] = addWays(cnt2[arr[p2].i], queryCnt);
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
        cnt1[i] = cnt2[i] = 0.0L; // log(1)=0，每个单点都是一个方案。
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
    long double cnt = NO_WAYS;
    for (int i = 1; i <= n; i++) {
        len = max(len, len1[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (len1[i] == len) {
            cnt = addWays(cnt, cnt1[i]); // 所有最长方案数的对数。
        }
    }
    printf("%d\n", len);
    for (int i = 1; i <= n; i++) {
        if (len1[i] + len2[i] - 1 < len) {
            //无法被拦截
            printf("0 ");
        } else {
            // log(包含 i 的方案数/总方案数) 后取指数。
            printf("%.5Lf ", expl(cnt1[i] + cnt2[i] - cnt));
        }
    }
    printf("\n");
    return 0;
}
