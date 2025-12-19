// Give Away，C++版
// 给定一个长度为n的数组arr，接下来有m条操作，每条操作是如下两种类型中的一种
// 操作 0 a b c : 打印arr[a..b]范围上>=c的数字个数
// 操作 1 a b   : 把arr[a]的值改成b
// 1 <= n <= 5 * 10^5
// 1 <= m <= 10^5
// 1 <= 数组中的值 <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/SP18185
// 测试链接 : https://www.spoj.com/problems/GIVEAWAY
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500001;
const int MAXB = 1001;

int n, m;
int arr[MAXN];//原始数组  所有的修改也会同步到arr中
int sortv[MAXN];//将数组拷贝过来  按照块分开  然后块内进行排序  变为有序的

int blen, bnum;//每一个块的长度  块的数量
int bi[MAXN];//每个位置属于哪一个块
int bl[MAXB];//这个编号的块的左边界
int br[MAXB];//这个编号的块的右边界

//初始化建立块的信息
void build() {
    blen = (int)sqrt(n);//块的长度
    bnum = (n + blen - 1) / blen;//块的个数（向上取整，即如果分块后最后存在小尾巴，那么自成一个块）
    for (int i = 1; i <= n; i++) {
        bi[i] = (i - 1) / blen + 1;
    }
    for (int i = 1; i <= bnum; i++) {
        bl[i] = (i - 1) * blen + 1;//左边界
        br[i] = min(i * blen, n);//右边界要小于n
    }
    //处理有序数组
    for (int i = 1; i <= n; i++) {
        sortv[i] = arr[i];
    }
    for (int i = 1; i <= bnum; i++) {
        sort(sortv + bl[i], sortv + br[i] + 1);
    }
}

//查询编号为i的块中 有多少数字大于等于v  二分查找
int getCnt(int i, int v) {
    int l = bl[i], r = br[i], m, ans = 0;
    while (l <= r) {
        m = (l + r) >> 1;
        if (sortv[m] >= v) {
            ans += r - m + 1;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

//查询从l~r中一共有多少个位置的值大于v
int query(int l, int r, int v) {
    int ans = 0;
    if (bi[l] == bi[r]) {
        //查询区间只涉及一个块  暴力的从原始数组中寻找
        for (int i = l; i <= r; i++) {
            if (arr[i] >= v) {
                ans++;
            }
        }
    } else {
        //涉及到的第一个和最后一个块使用枚举的方式进行统计
        for (int i = l; i <= br[bi[l]]; i++) {
            if (arr[i] >= v) {
                ans++;
            }
        }
        for (int i = bl[bi[r]]; i <= r; i++) {
            if (arr[i] >= v) {
                ans++;
            }
        }
        //统计中间的块中有多少值大于v的
        for (int i = bi[l] + 1; i <= bi[r] - 1; i++) {
            ans += getCnt(i, v);
        }
    }
    return ans;
}

//将位置i中的数字改成v
void update(int i, int v) {
    int l = bl[bi[i]];
    int r = br[bi[i]];
    arr[i] = v;
    for (int j = l; j <= r; j++) {
        sortv[j] = arr[j];
    }
    sort(sortv + l, sortv + r + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    build();
    cin >> m;
    int op, a, b, c;
    for (int i = 1; i <= m; i++) {
        cin >> op >> a >> b;
        if (op == 0) {
            cin >> c;
            cout << query(a, b, c) << '\n';
        } else {
            update(a, b);
        }
    }
    return 0;
}