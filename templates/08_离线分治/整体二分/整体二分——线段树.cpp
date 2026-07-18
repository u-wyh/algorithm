// 混合果汁，C++版
// 一共有n种果汁，每种果汁给定，美味度d、每升价格p、添加上限l
// 制作混合果汁时每种果汁不能超过添加上限，其中美味度最低的果汁，决定混合果汁的美味度
// 一共有m个小朋友，给每位制作混合果汁时，钱数不超过money[i]，体积不少于least[i]
// 打印每个小朋友能得到的混合果汁最大美味度，如果无法满足，打印-1
// 1 <= n、m、d、p、l <= 10^5
// 1 <= money[i]、least[i] <= 10^18
// 测试链接 : https://www.luogu.com.cn/problem/P4602
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//如果对于每个人都做一次二分的话  单个人的时间复杂度是 n*log(n)  那么总代价就是n*q*log(n)
//这道题建立的是单价线段树  即叶子结点上的信息是各种饮料的单价
//每个节点有cost suml信息分别表示这个节点所有饮料全买下来花多少钱 一共有多少体积
// P9175也是结合了线段树算法  不过难度更大
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;

int n, m;

// 果汁有三个参数，美味度d、每升价格p、添加上限l
struct Juice {
    int d, p, l;
};

bool JuiceCmp(Juice x, Juice y) {
    return x.d > y.d;
}

Juice juice[MAXN];
// 记录所有小朋友的编号
int qid[MAXN];
// 小朋友能花的钱数
long long money[MAXN];
// 小朋友至少的果汁量
long long least[MAXN];

// 果汁单价作为下标的线段树
// maxp为最大的果汁单价
int maxp = 0;
// suml[i] : 线段树某单价区间上，允许添加的总量
long long suml[MAXN << 2];
// cost[i] : 线段树某单价区间上，如果允许添加的总量全要，花费多少钱
long long cost[MAXN << 2];
// 多少种果汁加入了线段树  这是第二种整体二分的写法
int used = 0;

// 整体二分的过程需要
int lset[MAXN];
int rset[MAXN];

// 每个小朋友的答案，是第几号果汁的美味度
int ans[MAXN];

void up(int i) {
   suml[i] = suml[i << 1] + suml[i << 1 | 1];
   cost[i] = cost[i << 1] + cost[i << 1 | 1];
}

// 单价为jobi，现在允许添加的量增加了jobv
void add(int jobi, int jobv, int l, int r, int i) {
    if (l == r) {
        suml[i] += jobv;
        cost[i] = suml[i] * l;
    } else {
        int mid = (l + r) >> 1;
        if (jobi <= mid) {
            add(jobi, jobv, l, mid, i << 1);
        } else {
            add(jobi, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

// 总体积一共volume，已知总体积一定能耗尽
// 返回总体积耗尽的情况下，能花的最少钱数
long long query(long long volume, int l, int r, int i) {
    if (l == r) {
        return volume * l;
    }
    int mid = (l + r) >> 1;
    if (suml[i << 1] >= volume) {
        return query(volume, l, mid, i << 1);
    } else {
        return cost[i << 1] + query(volume - suml[i << 1], mid + 1, r, i << 1 | 1);
    }
}

void compute(int ql, int qr, int vl, int vr) {
    if (ql > qr) {
        return;
    }
    if (vl == vr) {
        //到了叶节点开始统计答案
        for (int i = ql; i <= qr; i++) {
            ans[qid[i]] = vl;
        }
    } else {
        int mid = (vl + vr) >> 1;
        // 线段树包含果汁的种类少就添加
        while (used < mid) {
            used++;
            add(juice[used].p, juice[used].l, 1, maxp, 1);
        }
        // 线段树包含果汁的种类多就撤销
        while (used > mid) {
            add(juice[used].p, -juice[used].l, 1, maxp, 1);
            used--;
        }
        int lsiz = 0, rsiz = 0;
        for (int i = ql, id; i <= qr; i++) {
            id = qid[i];
            if (suml[1] >= least[id] && query(least[id], 1, maxp, 1) <= money[id]) {
                //目前添加的种类  已经使得总数可以满足并且价格也满足 那么不需要使用美味度更低的了
                lset[++lsiz] = id;
            } else {
                rset[++rsiz] = id;
            }
        }
        for (int i = 1; i <= lsiz; i++) {
            qid[ql + i - 1] = lset[i];
        }
        for (int i = 1; i <= rsiz; i++) {
            qid[ql + lsiz + i - 1] = rset[i];
        }
        compute(ql, ql + lsiz - 1, vl, mid);
        compute(ql + lsiz, qr, mid + 1, vr);
    }
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> juice[i].d >> juice[i].p >> juice[i].l;
        maxp = max(maxp, juice[i].p);
    }
    for (int i = 1; i <= m; i++) {
        qid[i] = i;
        cin >> money[i] >> least[i];
    }
    // 所有果汁按照美味度排序，美味度大的在前，美味度小的在后
    sort(juice + 1, juice + n + 1, JuiceCmp);
    // 答案范围就是美味度范围，从最美味的第1名，到最难喝的第n名
	// 如果小朋友答案为n+1，说明无法满足这个小朋友
    compute(1, m, 1, n + 1);
    for (int i = 1; i <= m; i++) {
        if (ans[i] == n + 1) {
            cout << -1 << '\n';
        } else {
            cout << juice[ans[i]].d << '\n';
        }
    }
    return 0;
}