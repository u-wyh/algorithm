// 未来日记，C++版
// 给定一个长度为n的数组arr，一共有m条操作，每条操作类型如下
// 操作 1 l r x y : arr[l..r]范围上，所有值x变成值y
// 操作 2 l r k   : arr[l..r]范围上，查询第k小的值
// 1 <= n、m、arr[i] <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P4119
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题和我妻由乃打扑克是一样的  只不过时间限制更加紧张  如果使用那一道题的时间复杂度  在这里会超时
// 所以这里使用的是双层分块 既按照位置分块 也按照值域分块
// 在查询的时候 这道题的大思路是首先找到答案所在的值域块 然后仔细遍历每一个块中的数字 从而得到答案
// 修改操作的重点是维持我们需要的信息的正确性
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXB = 401;

int n, m;
int arr[MAXN];

// blen既表示序列块长，也表示值域块长
// bnum只表示序列块的数量
// bi[i]可以查询下标i来自哪个序列块
// bi[v]也可查询数字v来自哪个值域块
// bl[i]表示下标第i块的左边界
// br[i]表示下标第i块的右边界
int blen, bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

// idxset[i]表示下标i，在归属的块中，来自哪个集合
// valset[b][v]表示序列块b中的数值v，来自哪个集合
// setval[b][s]表示序列块b中的集合s，对应的数值
int idxset[MAXN];
int valset[MAXB][MAXN];
int setval[MAXB][MAXB];

// sum1[k][b]表示前k个序列块中，第b块个值域块的数字有几个
// sum2[k][v]表示前k个序列块中，数字v有几个
// cnt1[b]表示遍历散块之后，第b块个值域块的数字有几个
// cnt2[v]表示遍历散块之后，数字v有几个
int sum1[MAXB][MAXB];
int sum2[MAXB][MAXN];
int cnt1[MAXB];
int cnt2[MAXN];

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

// 序列第b块中，根据当前arr中的值，重建集合
//要解决的是valset  setval  idxset
void build(int b) {
    // 根据arr中的值重建集合，需要放弃之前的信息
	// 可是数值范围很大，不能枚举数值去清空 valset
	// 注意到，一个块里集合的数量 <= 块长
	// 所以根据 setval[b][s]，可以得到每个集合之前的对应值v
	// 然后 valset[b][v] = 0，让块内之前的每个值，不再挂靠任何集合
	// 这样可以避免数值的枚举，做到快速清空 valset
    for (int i = 1; i <= blen; i++) {
        valset[b][setval[b][i]] = 0;
    }
    for (int i = bl[b], s = 0; i <= br[b]; i++) {
        if (valset[b][arr[i]] == 0) {
            s++;
            valset[b][arr[i]] = s;
            setval[b][s] = arr[i];
        }
        idxset[i] = valset[b][arr[i]];
    }
}

// 命中了整块修改，有x无y的情况，序列第b块中所有x改成y
void lazy(int b, int x, int y) {
    valset[b][y] = valset[b][x];
    setval[b][valset[b][x]] = y;
    valset[b][x] = 0;
}

// 之前命中了整块修改，有x无y的情况，导致序列第b块中有些值改动了，把改动写入arr
void down(int b) {
    for (int i = bl[b]; i <= br[b]; i++) {
        arr[i] = setval[b][idxset[i]];
    }
}

// 序列[l..r]范围上，有x有y，把所有x改成y
void innerUpdate(int l, int r, int x, int y) {
    down(bi[l]);
    for (int i = l; i <= r; i++) {
        if (arr[i] == x) {
            sum1[bi[i]][bi[x]]--;
            sum1[bi[i]][bi[y]]++;
            sum2[bi[i]][x]--;
            sum2[bi[i]][y]++;
            arr[i] = y;
        }
    }
    build(bi[l]);
}

void update(int l, int r, int x, int y) {
    // 必要的剪枝
    if (x == y || (sum2[bi[r]][x] - sum2[bi[l] - 1][x] == 0)) {
        return;
    }
    // 前缀统计变成当前块统计
    for (int b = bi[n]; b >= bi[l]; b--) {
        sum1[b][bi[x]] -= sum1[b - 1][bi[x]];
        sum1[b][bi[y]] -= sum1[b - 1][bi[y]];
        sum2[b][x] -= sum2[b - 1][x];
        sum2[b][y] -= sum2[b - 1][y];
    }
    //维护更新后的信息
    if (bi[l] == bi[r]) {
        innerUpdate(l, r, x, y);//散块直接暴力维护
    } else {
        //散块直接暴力维护
        innerUpdate(l, br[bi[l]], x, y);
        innerUpdate(bl[bi[r]], r, x, y);
        //对于中间的整块而言  如果是y没有出现  那么我们可以很巧妙的维护
        //否则  也是暴力维护
        for (int b = bi[l] + 1; b <= bi[r] - 1; b++) {
            if (sum2[b][x] != 0) {
                if (sum2[b][y] != 0) {
                    // 整块更新时，调用innerUpdate的次数 <= 块长
                    //这里扩充一下  如果说在已经完成了全部的情况下  即整个块基本上是一样的  但是后来散块修改了一下 也同样不会增加复杂度
                    //因为修改的是边界位置上的值  如果要修正回来  还是通过目前这个分支修正的话  那么说明就是将原来散块修改的在改回来
                    //那我可以认为这是散块暴力修改的工作 只不过是有整块代替完成  
                    innerUpdate(bl[b], br[b], x, y);
                } else {
                    sum1[b][bi[y]] += sum2[b][x];
                    sum1[b][bi[x]] -= sum2[b][x];
                    sum2[b][y] = sum2[b][x];
                    sum2[b][x] = 0;
                    lazy(b, x, y);
                }
            }
        }
    }
    // 当前块统计变回前缀统计
    for (int b = bi[l]; b <= bi[n]; b++) {
        sum1[b][bi[x]] += sum1[b - 1][bi[x]];
        sum1[b][bi[y]] += sum1[b - 1][bi[y]];
        sum2[b][x] += sum2[b - 1][x];
        sum2[b][y] += sum2[b - 1][y];
    }
}

//收集散块的词频
void addCnt(int l, int r) {
    for (int i = l; i <= r; i++) {
        cnt1[bi[arr[i]]]++;
        cnt2[arr[i]]++;
    }
}

//将收集到的散块词频清空   为了方便下一次收集
void clearCnt(int l, int r) {
    for (int i = l; i <= r; i++) {
        cnt1[bi[arr[i]]] = cnt2[arr[i]] = 0;
    }
}

//其实整个程序还是很好理解的  就是为了如何更好的解决查询问题来合理的设置更新操作
int query(int l, int r, int k) {
    int ans = 0;
    bool inner = bi[l] == bi[r];
    // 建立散块的词频统计
    if (inner) {
        down(bi[l]);
        addCnt(l, r);
    } else {
        down(bi[l]);
        down(bi[r]);
        addCnt(l, br[bi[l]]);
        addCnt(bl[bi[r]], r);
    }
    int sumCnt = 0;
    int vblock = 0;
    // 定位第k小的数字，来自哪个值域块
    for (int b = 1; b <= bi[MAXN - 1]; b++) {
        // 如果不存在中间的整块，词频 = 散块词频，否则 词频 = 散块词频 + 整块词频
        //这里判断inner其实是因为如果是一样的  那么bi[r]-1<bi[l]
        int cnt = cnt1[b] + (inner ? 0 : sum1[bi[r] - 1][b] - sum1[bi[l]][b]);
        if (sumCnt + cnt >= k) {
            vblock = b;
            break;
        } else {
            sumCnt += cnt;
        }
    }
    // 定位第k小的数字，来自值域块的具体数字
    for (int v = (vblock - 1) * blen + 1; v <= vblock * blen; v++) {
        //枚举这个值域块中的所有数字
        // 如果不存在中间的整块，词频 = 散块词频，否则 词频 = 散块词频 + 整块词频
        //这里判断inner其实是因为如果是一样的  那么bi[r]-1<bi[l]
        int cnt = cnt2[v] + (inner ? 0 : sum2[bi[r] - 1][v] - sum2[bi[l]][v]);
        if (sumCnt + cnt >= k) {
            ans = v;
            break;
        } else {
            sumCnt += cnt;
        }
    }
    // 清空散块的词频统计
    if (inner) {
        clearCnt(l, r);
    } else {
        clearCnt(l, br[bi[l]]);
        clearCnt(bl[bi[r]], r);
    }
    return ans;
}

void prepare() {
    blen = 300;
    bnum = (n + blen - 1) / blen;
    // i一定要枚举[1, MAXN)
	// 因为不仅序列要分块，值域也要分块
    for (int i = 1; i < MAXN; i++) {
        bi[i] = (i - 1) / blen + 1;
    }
    // bl、br 仅用于序列分块
    //不适用于值域分块
    for (int i = 1; i <= bnum; i++) {
        bl[i] = (i - 1) * blen + 1;
        br[i] = min(i * blen, n);
        build(i);
    }
    // 初始建立sum1、sum2，都表示前缀信息
    for (int i = 1; i <= bnum; i++) {
        for (int j = 1; j < MAXB; j++) {
            sum1[i][j] = sum1[i - 1][j];
        }
        for (int j = 1; j < MAXN; j++) {
            sum2[i][j] = sum2[i - 1][j];
        }
        for (int j = bl[i]; j <= br[i]; j++) {
            sum1[i][bi[arr[j]]]++;
            sum2[i][arr[j]]++;
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
    for (int i = 1, op, l, r, x, y, k; i <= m; i++) {
        op = read();
        l = read();
        r = read();
        if (op == 1) {
            x = read();
            y = read();
            update(l, r, x, y);
        } else {
            k = read();
            printf("%d\n", query(l, r, k));
        }
    }
    return 0;
}