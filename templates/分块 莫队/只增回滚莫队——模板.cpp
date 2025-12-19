// 只增回滚莫队入门题，C++版
// 给定一个长度为n的数组arr，下面定义重要度的概念
// 如果一段范围上，数字x出现c次，那么这个数字的重要度为x * c
// 范围上的最大重要度，就是该范围上，每种数字的重要度，取最大值
// 一共有m条查询，格式 l r : 打印arr[l..r]范围上的最大重要度
// 1 <= n、m <= 10^5
// 1 <= arr[i] <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/AT_joisc2014_c
// 测试链接 : https://atcoder.jp/contests/joisc2014/tasks/joisc2014_c
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 我们还是按照普通莫队进行排序  我们是按照块进行操作的   对于左右边界都在同一块中的问题  直接暴力维护答案
// 对于右边不和左边在一块的  我们准备一个窗口  首先这些问题的右边界的都是有序的
// 对于每个问题 我们首先先将窗口更新到右边界  记录下此时窗口的状态
// 然后更行左边界  收集答案之后  减窗口信息复原到我们记录  然后重复这个操作
// 时间复杂度  左右边界在同一块的  无非每次左边界左右反复  每一次最多代价不过 根号n  总代价O(q*根号n)
// 左右边界不在同一块的  右边界的更新代价最多不过遍历一遍整个数组  最多会有根号n的块 也就是O(n*根号n)
// 对于左边界的话  其实和左右边界在同一块的代价一样 不过就是左右反复 总代价O(q*根号n)
// 只在窗口扩展的时候更新答案   这里不能使用奇偶优化性排序  任何一个块的右边界都必须是递增的
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXB = 401;

struct Query {
   int l, r, id;
};

int n, m;
int arr[MAXN];
Query query[MAXN];
int sorted[MAXN];
int cntv;

int blen, bnum;
int bi[MAXN];
int br[MAXB];

// 词频表
int cnt[MAXN];
// 当前窗口的最大重要度
long long curAns = 0;

// 收集所有答案
long long ans[MAXN];

// 只增回滚莫队经典排序
bool QueryCmp(Query &a, Query &b) {
    if (bi[a.l] != bi[b.l]) {
        return bi[a.l] < bi[b.l];
    }
    return a.r < b.r;
}

int kth(int num) {
    int left = 1, right = cntv, ret = 0;
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (sorted[mid] <= num) {
            ret = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ret;
}

// 暴力遍历arr[l..r]得到答案
// 如果左右边界都在一块中 那么直接暴力维护
long long force(int l, int r) {
    long long ret = 0;
    for (int i = l; i <= r; i++) {
        cnt[arr[i]]++;
    }
    for (int i = l; i <= r; i++) {
        ret = max(ret, 1LL * cnt[arr[i]] * sorted[arr[i]]);
    }
    for (int i = l; i <= r; i++) {
        cnt[arr[i]]--;
    }
    return ret;
}

// 窗口增加num，词频和答案都更新
void add(int num) {
    cnt[num]++;
    curAns = max(curAns, 1LL * cnt[num] * sorted[num]);
}

// 窗口减少num，词频更新、答案不更新
void del(int num) {
    cnt[num]--;
}

void compute() {
    for (int block = 1, qi = 1; block <= bnum && qi <= m; block++) {
        curAns = 0;
        fill(cnt + 1, cnt + cntv + 1, 0);
        int winl = br[block] + 1, winr = br[block];
        for (; qi <= m && bi[query[qi].l] == block; qi++) {
            int jobl = query[qi].l;
            int jobr = query[qi].r;
            int id = query[qi].id;
            if (jobr <= br[block]) {
                ans[id] = force(jobl, jobr);
            } else {
                while (winr < jobr) {
                    add(arr[++winr]);
                }
                // 记录一下此时的答案
                long long backup = curAns;
                while (winl > jobl) {
                    add(arr[--winl]);//必须要先恢复到jobl
                }
                ans[id] = curAns;
                curAns = backup;
                while (winl <= br[block]) {
                    del(arr[winl++]);
                }
            }
        }
    }
}

void prepare() {
    for (int i = 1; i <= n; i++) {
        sorted[i] = arr[i];
    }
    sort(sorted + 1, sorted + n + 1);
    cntv = 1;
    for (int i = 2; i <= n; i++) {
        if (sorted[cntv] != sorted[i]) {
            sorted[++cntv] = sorted[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        arr[i] = kth(arr[i]);
    }
    blen = (int)sqrt(n);
    bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= n; i++) {
        bi[i] = (i - 1) / blen + 1;
    }
    for (int i = 1; i <= bnum; i++) {
        br[i] = min(i * blen, n);
    }
    sort(query + 1, query + m + 1, QueryCmp);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> query[i].l >> query[i].r;
        query[i].id = i;
    }
    prepare();
    compute();
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}