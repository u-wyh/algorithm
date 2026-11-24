// 最小异或查询，C++版
// 一共有q条操作，每种操作是如下三种类型中的一种
// 操作 1 x : 黑板上写上一个数字x，同一种数字可以出现多次
// 操作 2 x : 将一个x从黑板上擦掉，操作时保证至少有一个x在黑板上
// 操作 3   : 打印黑板上任意两数的最小异或值，操作时保证黑板上至少有两个数
// 1 <= q <= 3 * 10^5
// 0 <= x <= 2^30
// 测试链接 : https://www.luogu.com.cn/problem/AT_abc308_g
// 测试链接 : https://atcoder.jp/contests/abc308/tasks/abc308_g
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
//这道题没有使用线段树分治  因为时间复杂度非常紧张
//这里有点类似于树形dp了
//这个反面教材的意思是我们不能学会了线段树分治 就只会线段树分治 不能跳出思维
//在建立的前缀树进行树形dp  对每个节点进行以这个节点为首的子树进行动态规划
//对叶节点特别处理  only的值是原本值
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10000001;
const int BIT = 29;
const int INF = 1 << 30;

int fa[MAXN];
int tree[MAXN][2];
int pass[MAXN];
int cnt = 1;

// 整棵树上最小异或值
int mineor[MAXN];
// 整棵树上如果只有一个数x，才有记录，否则记录是0
int only[MAXN];

int change(int x, int changeCnt) {
    int cur = 1;
    pass[cur] += changeCnt;
    for (int b = BIT, path; b >= 0; b--) {
        path = (x >> b) & 1;
        if (tree[cur][path] == 0) {
            tree[cur][path] = ++cnt;
            fa[tree[cur][path]] = cur;
        }
        cur = tree[cur][path];
        pass[cur] += changeCnt;
    }
    return cur;
}

void compute(int x, int changeCnt) {
    int bottom = change(x, changeCnt);//返回的是最底层的编号  
    //设置好底层节点
    mineor[bottom] = pass[bottom] >= 2 ? 0 : INF;
    only[bottom] = pass[bottom] == 1 ? x : 0;
    //不断向上调整
    for (int i = fa[bottom], l, r; i > 0; i = fa[i]) {
        l = tree[i][0];
        r = tree[i][1];
        if (pass[i] < 2) {
            //表示这个节点中出现的数字不足两个  那么一定不可以有异或的结果
            mineor[i] = INF;
        } else if (pass[l] == 1 && pass[r] == 1) {
            //如果左右两边各有一个数字  那么没办法 只能左右异或一下
            mineor[i] = only[l] ^ only[r];
        } else if (pass[l] == 0 ^ pass[r] == 0) {
            //如果有一侧是空  那么就是非空的那一边的答案
            //这里需要注意 不能和下面的情况合并在一起  因为即使pass等于0  但是mineor可能不是INF  
            //比如根本没有这个孩子节点  即这个孩子节点始终是0  没有被赋值
            mineor[i] = pass[l] == 0 ? mineor[r] : mineor[l];
        } else {
            //否则  一定是左右两边至少有一边不止1个  那么一定就是两侧中较小的那一个
            //因为如果是左右两边一起产生效果得到的答案  那么一定比一边的答案要大  
            mineor[i] = min(mineor[l], mineor[r]);
        }
        if (pass[l] + pass[r] == 1) {
            only[i] = pass[l] == 1 ? only[l] : only[r];
        } else {
            only[i] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    for (int i = 1, op, x; i <= q; i++) {
        cin >> op;
        if (op == 3) {
            cout << mineor[1] << '\n';
        } else {
            cin >> x;
            if (op == 1) {
                compute(x, 1);
            } else {
                compute(x, -1);
            }
        }
    }
    return 0;
}