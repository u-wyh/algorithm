// 蒲公英，C++版
// 给定一个长度为n的数组arr，接下来有m条操作，每条操作格式如下
// 操作 l r : 打印arr[l..r]范围上的众数，如果有多个众数，打印值最小的
// 1 <= n <= 4 * 10^4
// 1 <= m <= 5 * 10^4
// 1 <= 数组中的值 <= 10^9
// 题目要求强制在线，具体规则可以打开测试链接查看
// 测试链接 : https://www.luogu.com.cn/problem/P4168
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题的分块做法有点类似于动态规划
//最大的变化是它不再按照每个位置的下标组织数组
//是按照块号来组织的  以块为单位
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 40001;
const int MAXB = 201;

int n, m, s;
int arr[MAXN];
int sortv[MAXN];

int blen, bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int freq[MAXB][MAXN];//表示前i块中  数字j出现的次数
int mode[MAXB][MAXB];//用于收集从第i块到第j块中出现次数最多且值最小的数字
int numCnt[MAXN];//这个是辅助数组  用于统计散块的词频

int lower(int num) {
    int l = 1, r = s, m, ans = 0;
    while (l <= r) {
        m = (l + r) >> 1;
        if (sortv[m] >= num) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

//统计第l~r块中  数字v出现的次数
int getCnt(int l, int r, int v) {
    return freq[r][v] - freq[l - 1][v];
}

void prepare() {
    blen = (int)sqrt(n);
    bnum = (n + blen - 1) / blen;
    for (int i = 1; i <= n; i++) {
        bi[i] = (i - 1) / blen + 1;
    }
    for (int i = 1; i <= bnum; i++) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(i * blen, n);
    }
    //离散化
    for (int i = 1; i <= n; i++) {
        sortv[i] = arr[i];
    }
    sort(sortv + 1, sortv + n + 1);
    s = 1;
    for (int i = 2; i <= n; i++) {
        if (sortv[s] != sortv[i]) {
            sortv[++s] = sortv[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        arr[i] = lower(arr[i]);
    }
    //准备freq、mode数组
    for (int i = 1; i <= bnum; i++) {
        //统计每一块中各个元素出现次数
        for (int j = bl[i]; j <= br[i]; j++) {
            freq[i][arr[j]]++;
        }
        //继承以前的块  实现从1~i块
        for (int j = 1; j <= s; j++) {
            freq[i][j] += freq[i - 1][j];
        }
    }
    for (int i = 1; i <= bnum; i++) {
        for (int j = i; j <= bnum; j++) {
            //most是从i~j-1中的众数  mostcnt是他在i~j块出现的次数
            int most = mode[i][j - 1];
            int mostCnt = getCnt(i, j, most);
            //枚举第j块中的元素   看看有没有出现次数更多的
            for (int k = bl[j]; k <= br[j]; k++) {
                int cur = arr[k];
                int curCnt = getCnt(i, j, cur);
                if (curCnt > mostCnt || (curCnt == mostCnt && cur < most)) {
                    most = cur;
                    mostCnt = curCnt;
                }
            }
            mode[i][j] = most;
        }
    }
}

//查询从l~r这个区间上的众数
int query(int l, int r) {
    int most = 0;
    if (bi[l] == bi[r]) {
        //如果只是一个块
        for (int i = l; i <= r; i++) {
            numCnt[arr[i]]++;
        }
        for (int i = l; i <= r; i++) {
            if (numCnt[arr[i]] > numCnt[most] || (numCnt[arr[i]] == numCnt[most] && arr[i] < most)) {
                most = arr[i];
            }
        }
        //全部归零 方便下一次使用
        for (int i = l; i <= r; i++) {
            numCnt[arr[i]] = 0;
        }
    } else {
        //先收集左右两个散块的词频
        for (int i = l; i <= br[bi[l]]; i++) {
            numCnt[arr[i]]++;
        }
        for (int i = bl[bi[r]]; i <= r; i++) {
            numCnt[arr[i]]++;
        }
        //此时的most是中间的块的众数  如果中间没有块 那么就是0
        most = mode[bi[l] + 1][bi[r] - 1];
        int mostCnt = getCnt(bi[l] + 1, bi[r] - 1, most) + numCnt[most];
        //枚举左散块
        for (int i = l; i <= br[bi[l]]; i++) {
            int cur = arr[i];
            int curCnt = getCnt(bi[l] + 1, bi[r] - 1, cur) + numCnt[cur];
            if (curCnt > mostCnt || (curCnt == mostCnt && cur < most)) {
                most = cur;
                mostCnt = curCnt;
            }
        }
        //枚举右散块
        for (int i = bl[bi[r]]; i <= r; i++) {
            int cur = arr[i];
            int curCnt = getCnt(bi[l] + 1, bi[r] - 1, cur) + numCnt[cur];
            if (curCnt > mostCnt || (curCnt == mostCnt && cur < most)) {
                most = cur;
                mostCnt = curCnt;
            }
        }
        for (int i = l; i <= br[bi[l]]; i++) {
            numCnt[arr[i]] = 0;
        }
        for (int i = bl[bi[r]]; i <= r; i++) {
            numCnt[arr[i]] = 0;
        }
    }
    return sortv[most];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    prepare();
    int lastAns = 0, a, b, l, r;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b;
        a = (a + lastAns - 1) % n + 1;
        b = (b + lastAns - 1) % n + 1;
        l = min(a, b);
        r = max(a, b);
        lastAns = query(l, r);
        cout << lastAns << '\n';
    }
    return 0;
}