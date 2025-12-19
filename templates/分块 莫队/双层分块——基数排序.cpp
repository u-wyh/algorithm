// 魔法少女网站，C++版
// 给定一个长度为n的数组arr，一共有m条操作，每条操作类型如下
// 操作 1 x v   : arr[x]的值变成v
// 操作 2 x y v : arr[x..y]范围上，查询有多少连续子数组的最大值 <= v
// 1 <= n、m <= 3 * 10^5
// 1 <= arr[i] <= n
// 测试链接 : https://www.luogu.com.cn/problem/P6578
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 双层分块的难度属实是有点过于大了  有点建议放弃
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300002;
const int MAXB = 601;
const int POW = 9;//块的大小设置为512   这里用2进制表示  可以加速基数排序
const int OFFSET = (1 << POW) - 1;

namespace fastio {
    static const int SZ = 1 << 20;
    char ibuf[SZ], *is = ibuf, *ie = ibuf;
    inline int gc() {
        if (is == ie) {
            size_t len = fread(ibuf, 1, SZ, stdin);
            if (len == 0) return -1;
            is = ibuf;
            ie = ibuf + len;
        }
        return *is++;
    }
    template <typename T>
    inline bool readInt(T& x) {
        int c = gc(); if (c == -1) return false;
        bool neg = false;
        while (c != '-' && (c < '0' || c > '9')) { c = gc(); if (c == -1) return false; }
        if (c == '-') { neg = true; c = gc(); }
        x = 0;
        while (c >= '0' && c <= '9') { x = x * 10 + (c & 15); c = gc(); }
        if (neg) x = -x;
        return true;
    }
    char obuf[SZ]; char* op = obuf;
    inline void flush() {
        fwrite(obuf, 1, op - obuf, stdout);
        op = obuf;
    }
    template <typename T>
    inline void writeInt(T x, char end = '\n') {
        if (op > obuf + SZ - 256) flush();
        if (x == 0) { *op++ = '0'; *op++ = end; return; }
        if (x < 0) { *op++ = '-'; x = -x; }
        char s[24]; int n = 0;
        while (x) { s[n++] = char('0' + x % 10); x /= 10; }
        while (n) *op++ = s[--n];
        *op++ = end;
    }
}
using fastio::readInt;
using fastio::writeInt;
using fastio::flush;

int n, m;

int arr[MAXN];
int op[MAXN];
int x[MAXN];
int y[MAXN];
int v[MAXN];

// pos[1..cntp]是当前序列块的下标
// qid[1..cntq]是整包结算的查询编号
int pos[MAXN];
int qid[MAXN];
int cntp;
int cntq;

// 基数排序
int cntv[MAXB];
int help[MAXN];

// 双链表
int lst[MAXN];
int nxt[MAXN];

// 每条查询的答案信息
int pre[MAXN];
int suf[MAXN];
int len[MAXN];
long long ans[MAXN];

// 讲解028 - 基数排序，不会的话去看课
// idx[1..siz]都是编号，编号根据val[编号]的值排序
// val[编号]的高位 = val[编号] >> POW
// val[编号]的低位 = val[编号] & OFFSET
inline void radix(int* idx, int* val, int siz) {
    memset(cntv, 0, sizeof(int) * MAXB);
    for (int i = 1; i <= siz; i++) cntv[val[idx[i]] & OFFSET]++;
    for (int i = 1; i < MAXB; i++) cntv[i] += cntv[i - 1];
    for (int i = siz; i >= 1; i--) help[cntv[val[idx[i]] & OFFSET]--] = idx[i];
    memcpy(idx + 1, help + 1, siz * sizeof(int));
    memset(cntv, 0, sizeof(int) * MAXB);
    for (int i = 1; i <= siz; i++) cntv[val[idx[i]] >> POW]++;
    for (int i = 1; i < MAXB; i++) cntv[i] += cntv[i - 1];
    for (int i = siz; i >= 1; i--) help[cntv[val[idx[i]] >> POW]--] = idx[i];
    memcpy(idx + 1, help + 1, siz * sizeof(int));
}

// 查询的答案信息 pre[i]、suf[i]、len[i]、ans[i]
// 当前块答案信息 curPre、curSuf、curLen、curAns
// 查询的答案信息 合并 当前块答案信息
inline void merge(int i, int curPre, int curSuf, int curLen, int curAns) {
    ans[i] += 1L * suf[i] * curPre + curAns;
    pre[i] = pre[i] + (pre[i] == len[i] ? curPre : 0);
    suf[i] = curSuf + (curSuf == curLen ? suf[i] : 0);
    len[i] += curLen;
}

// 整包结算
// qid[1..cntq]是查询编号，每条查询整包[l..r]
// 根据序列块的数字状况，更新每个查询的答案信息
void calc(int l, int r) {
    for (int i = l; i <= r; i++) {
        pos[++cntp] = i;
        lst[i] = i - 1;
        nxt[i] = i + 1;
    }
    radix(pos, arr, cntp);
    radix(qid, v, cntq);
    int curPre = 0, curSuf = 0, curLen = r - l + 1, curAns = 0;
    for (int i = 1, j = 1, idx; i <= cntq; i++) {
        while (j <= cntp && arr[pos[j]] <= v[qid[i]]) {
            idx = pos[j];
            if (lst[idx] == l - 1) {
                curPre += nxt[idx] - idx;
            }
            if (nxt[idx] == r + 1) {
                curSuf += idx - lst[idx];
            }
            curAns += 1L * (idx - lst[idx]) * (nxt[idx] - idx);
            lst[nxt[idx]] = lst[idx];
            nxt[lst[idx]] = nxt[idx];
            j++;
        }
        merge(qid[i], curPre, curSuf, curLen, curAns);
    }
    cntp = cntq = 0;
}

// 序列块[l..r]，处理一遍所有的操作(单改 + 查询)
void compute(int l, int r) {
    for (int qi = 1; qi <= m; qi++) {
        if (op[qi] == 1) {
            //修改操作
            if (l <= x[qi] && x[qi] <= r) {
                calc(l, r);
                arr[x[qi]] = v[qi];
            }
        } else {
            if (x[qi] <= l && r <= y[qi]) {
                //区间全包
                qid[++cntq] = qi;
            } else {
                //散块暴力维护
                for (int i = max(x[qi], l); i <= min(y[qi], r); i++) {
                    //一个值单独作为一个块  将他的贡献和已有的结合
                    if (arr[i] <= v[qi]) {
                        merge(qi, 1, 1, 1, 1);
                    } else {
                        merge(qi, 0, 0, 1, 0);
                    }
                }
            }
        }
    }
    calc(l, r);
}

int main() {
    readInt(n);
    readInt(m);
    for (int i = 1; i <= n; i++) {
        readInt(arr[i]);
    }
    for (int i = 1; i <= m; i++) {
        readInt(op[i]);
        readInt(x[i]);
        if (op[i] == 1) {
            readInt(v[i]);
        } else {
            readInt(y[i]);
            readInt(v[i]);
        }
    }
    //其实这里一般就是prepare函数了
    int blen = 1 << POW;
    int bnum = (n + blen - 1) / blen;
    //枚举每一个块  计算对答案的贡献
    for (int i = 1, l, r; i <= bnum; i++) {
        l = (i - 1) * blen + 1;
        r = min(i * blen, n);
        compute(l, r);
    }
    for (int i = 1; i <= m; i++) {
        if (op[i] == 2) {
            writeInt(ans[i]);
        }
    }
    flush();
    return 0;
}