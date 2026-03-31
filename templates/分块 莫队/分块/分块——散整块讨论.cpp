// 区间逆序对，C++版
// 给定一个长度为n的排列，接下来有m条操作，每条操作格式如下
// 操作 l r : 打印arr[l..r]范围上的逆序对数量
// 1 <= n、m <= 10^5
// 题目要求强制在线，具体规则可以打开测试链接查看
// 测试链接 : https://www.luogu.com.cn/problem/P5046
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题比较卡常，C++实现也需要优化常数，比如快读
// 正式比赛不卡常
// 这道题主要是散整块之间的关系讨论  主要是分析很难  以及准备预处理信息
// 查询从l到r之间的逆序对   
// 1、l~r都是一个组   并且l是左边界  那么直接就是pre[r]
// 2、l~r是一个组  但是l不是左边界  那么答案就是pre[r]-pre[l-1]-f(l[i],l-1,l,r)
// 3、不是一个组  这是普遍情况 答案是（左散块[l..]内部逆序对 + 右散块[..r]内部逆序对 + 左散块 结合 右散块 的逆序对）+左散块对中间的+右散块对中间的+中间的逆序对个数
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXB = 701;

char buf[1000000], *p1 = buf, *p2 = buf;

inline char getChar() {
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read() {
    int s = 0;
    char c = getChar();
    while (!isdigit(c)) {
        c = getChar();
    }
    while (isdigit(c)) {
        s = s * 10 + c - '0';
        c = getChar();
    }
    return s;
}

// (数值、位置)
struct Node {
    int v, i;
};

bool NodeCmp(Node &a, Node &b) {
    return a.v != b.v ? a.v < b.v : a.i < b.i;
}

int n, m;
int arr[MAXN];
Node sortv[MAXN];

int blen, bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

// 树状数组，为了快速生成pre数组和suf数组
int tree[MAXN];

// pre[i] : 从所在块最左位置到i位置，有多少逆序对
int pre[MAXN];
// suf[i] : 从i位置到所在块最右位置，有多少逆序对
int suf[MAXN];
// cnt[i][j] : 前i块里<=j的数字个数
int cnt[MAXB][MAXN];
// dp[i][j] : 从第i块到第j块有多少逆序对
long long dp[MAXB][MAXB];

inline int lowbit(int i) {
    return i & -i;
}

inline void add(int i, int v) {
    while (i <= n) {
        tree[i] += v;
        i += lowbit(i);
    }
}

inline int sum(int i) {
    int ret = 0;
    while (i > 0) {
        ret += tree[i];
        i -= lowbit(i);
    }
    return ret;
}

// 更靠左的第x块，从xl到xr范围上，选第一个数
// 更靠右的第y块，从yl到yr范围上，选第二个数
// x和y可以相等，但是xl..xr需要在yl..yr的左侧
// 返回逆序对数量
//时间复杂度是根号n
inline int f(int x, int xl, int xr, int y, int yl, int yr) {
    int ans = 0;
    for (int p1 = bl[x], p2 = bl[y] - 1, cnt = 0; p1 <= br[x]; p1++) {
        if (xl <= sortv[p1].i && sortv[p1].i <= xr) {
            while (p2 + 1 <= br[y] && sortv[p1].v > sortv[p2 + 1].v) {
                p2++;
                if (yl <= sortv[p2].i && sortv[p2].i <= yr) {
                    cnt++;
                }
            }
            ans += cnt;
        }
    }
    return ans;
}

long long query(int l, int r) {
    long long ans = 0;
    int lb = bi[l], rb = bi[r];
    if (lb == rb) {
        if (l == bl[lb]) {
            ans = pre[r];
        } else {
            ans = pre[r] - pre[l - 1] - f(lb, bl[lb], l - 1, lb, l, r);
        }
    } else {
        // 左散块[l..]内部逆序对 + 右散块[..r]内部逆序对 + 左散块 结合 右散块 的逆序对
        ans = suf[l] + pre[r] + f(lb, l, br[lb], rb, bl[rb], r);
        // 左散块中的arr[i]，作为第一个数
		// 中间整块中的某个数字，作为第二个数
		// 计算这样的逆序对数量
		// 注意因为题目给定的是排列！所以如下这么写没问题
        for (int i = l; i <= br[lb]; i++) {
            //查询中间的块中小于自己的
            ans += cnt[rb - 1][arr[i]] - cnt[lb][arr[i]];
        }
        // 中间整块中的某个数字，作为第一个数
		// 右散块中的arr[i]，作为第二个数
		// 计算这样的逆序对数量
        for (int i = bl[rb]; i <= r; i++) {
            //查询中间块中大于自己的
            ans += br[rb - 1] - bl[lb + 1] + 1 - (cnt[rb - 1][arr[i]] - cnt[lb][arr[i]]);
        }
        // 中间整块的逆序对
        ans += dp[lb + 1][rb - 1];
    }
    return ans;
}

// 注意调整块长
void prepare() {
    blen = (int)sqrt(n / 4);
    bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= n; i++) bi[i] = (i - 1) / blen + 1;
    for (int i = 1; i <= bnum; i++) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(i * blen, n);
    }
    for (int i = 1; i <= n; i++) {
        sortv[i].v = arr[i];
        sortv[i].i = i;
    }
    for (int i = 1; i <= bnum; i++) {
        sort(sortv + bl[i], sortv + br[i] + 1, NodeCmp);
    }
    //预处理各种信息
    for (int i = 1; i <= bnum; i++) {
        for (int j = bl[i]; j <= br[i]; j++) {
            cnt[i][arr[j]]++;
            if (j != bl[i]) {
                pre[j] = pre[j - 1] + sum(n) - sum(arr[j]);//前面大于自己的数字个数
            }
            add(arr[j], 1);
        }
        //注意清空树状数组
        for (int j = bl[i]; j <= br[i]; j++) {
            add(arr[j], -1);
        }

        for (int j = br[i]; j >= bl[i]; j--) {
            if (j != br[i]) {
                suf[j] = suf[j + 1] + sum(arr[j]);//后面小于自己的数字的个数
            }
            add(arr[j], 1);
        }
        //注意清空树状数组
        for (int j = bl[i]; j <= br[i]; j++) {
            add(arr[j], -1);
        }

        int tmp = 0;
        for (int j = 1; j <= n; j++) {
            tmp += cnt[i][j];
            cnt[i][j] = tmp + cnt[i - 1][j];
        }
    }
    //利用容斥进行计算
    //dp[l][r]=dp[l+1][r]+dp[l][r-1]-dp[l+1][r-1]+(l这个块和r这个块产生的逆序对)
    for (int l = bnum; l >= 1; l--) {
        dp[l][l] = pre[br[l]];
        for (int r = l + 1; r <= bnum; r++) {
            dp[l][r] = dp[l + 1][r] + dp[l][r - 1] - dp[l + 1][r - 1] + f(l, bl[l], br[l], r, bl[r], br[r]);
        }
    }
}

int main() {
    n = read();
    m = read();
    for (int i = 1; i <= n; i++) {
        arr[i] = read();
    }
    prepare();
    long long lastAns = 0;
    for (int i = 1, l, r; i <= m; i++) {
        l = read() ^ lastAns;
        r = read() ^ lastAns;
        lastAns = query(l, r);
        printf("%lld\n", lastAns);
    }
    return 0;
}