// 空间少求众数的次数，C++版
// 给定一个长度为n的数组arr，接下来有m条操作，每条操作格式如下
// 操作 l r : 打印arr[l..r]范围上，众数到底出现了几次
// 1 <= 所有数值 <= 5 * 10^5
// 内存空间只有64MB，题目要求强制在线，具体规则可以打开测试链接查看
// 测试链接 : https://www.luogu.com.cn/problem/P5048
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题和上一个众数的区别是空间少  不能使用频率统计数组
//但是我们维护另外一种结构，使之可以实现：查询一个值的前面或者后面的第任意个相同的值所在位置
//这样在区间查询的时候  我们可以通过判断这个值后面或者前面第len个是不是在范围内  能不能起到更新答案的作用
//我们将原始数组上的位置信息和值信息看成是这个点的全部信息
//按照值大小进行排序  然后再使用一个数组记录原来的i位置上的节点信息现在在排序后的位置
//那么这样我们在查询某个位置之后的第k个相同值的位置就可以找到了
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500001;
const int MAXB = 801;

struct Node {
    int v, i;
};

int n, m;
int arr[MAXN];

int blen, bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

// (值、下标)，用来收集同一种数的下标列表
Node sortList[MAXN];
// listIdx[i] = j，表示arr[i]这个元素在sortList里的j位置
int listIdx[MAXN];
// modeCnt[i][j]表示从i块到j块中众数的出现次数
int modeCnt[MAXB][MAXB];
// 数字词频统计
int numCnt[MAXN];

bool NodeCmp(Node a, Node b) {
    if (a.v != b.v) {
        return a.v < b.v;
    }
    return a.i < b.i;
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
    //收集信息、准备排序
    for (int i = 1; i <= n; i++) {
        sortList[i].v = arr[i];
        sortList[i].i = i;
    }
    sort(sortList + 1, sortList + n + 1, NodeCmp);
    for (int i = 1; i <= n; i++) {
        listIdx[sortList[i].i] = i;
    }
    //统计连续的块中的众数频率
    for (int i = 1; i <= bnum; i++) {
        for (int j = i; j <= bnum; j++) {
            int cnt = modeCnt[i][j - 1];
            //枚举右边半散列 统计信息
            for (int k = bl[j]; k <= br[j]; k++) {
                cnt = max(cnt, ++numCnt[arr[k]]);
            }
            modeCnt[i][j] = cnt;
        }
        for (int j = 1; j <= n; j++) {
            numCnt[j] = 0;
        }
    }
}

//查询从l~r区间出现次数最多的频率
int query(int l, int r) {
    int ans = 0;
    if (bi[l] == bi[r]) {
        for (int i = l; i <= r; i++) {
            ans = max(ans, ++numCnt[arr[i]]);
        }
        for (int i = l; i <= r; i++) {
            numCnt[arr[i]] = 0;
        }
    } else {
        ans = modeCnt[bi[l] + 1][bi[r] - 1];//中间连续块的众数频率
        //枚举左右两个半块 看看是否可以更新答案
        for (int i = l, idx; i <= br[bi[l]]; i++) {
            idx = listIdx[i];//找到在排序列表中的位置
            while (idx + ans <= n && sortList[idx + ans].v == arr[i] && sortList[idx + ans].i <= r) {
                ans++;//只要这个位置可以更新答案  那么这个位置就持续更新
            }
        }
        for (int i = bl[bi[r]], idx; i <= r; i++) {
            idx = listIdx[i];
            while (idx - ans >= 1 && sortList[idx - ans].v == arr[i] && sortList[idx - ans].i >= l) {
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    prepare();
    for (int i = 1, l, r, lastAns = 0; i <= m; i++) {
        cin >> l >> r;
        l ^= lastAns;
        r ^= lastAns;
        lastAns = query(l, r);
        cout << lastAns << '\n';
    }
    return 0;
}