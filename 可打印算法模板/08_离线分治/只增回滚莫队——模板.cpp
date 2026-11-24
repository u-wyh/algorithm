// 用途：离线查询区间内‘数值×出现次数’的最大值。
// 时间：约 O((n+q)√n)。
// 空间：O(n+q+V)。
// 注意：当前答案只增不减；缩回左端后须恢复备份答案。
// 例题：https://www.luogu.com.cn/problem/AT_joisc2014_c
// 题意：多次询问区间中数值乘其出现次数的最大值。
// 思路：按左端块分组，右端单向扩展，左端临时加入后回滚。
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
