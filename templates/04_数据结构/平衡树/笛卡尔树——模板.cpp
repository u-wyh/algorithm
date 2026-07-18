// 笛卡尔树模版(C++版)
// 给定一个长度为n的数组arr，下标从1开始
// 构建一棵二叉树，下标按照搜索二叉树组织，值按照小根堆组织
// 建树的过程要求时间复杂度O(n)
// 建树之后，为了验证
// 打印，i * (left[i] + 1)，所有信息异或起来的值
// 打印，i * (right[i] + 1)，所有信息异或起来的值
// 1 <= n <= 10^7
// 测试链接 : https://www.luogu.com.cn/problem/P5854
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 笛卡尔树建立的时候需要单调栈  栈里面比较的东西是按照堆组织的
// 里面存储的是按照二叉排序组织的值  这样建图是O(n)
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10000001;

int arr[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];
int n;

//如果没有变小的数字  那么建树就是一直往右边节点建立
//也不会有节点从栈中弹出  单调队列比较的是按堆组织的  大压小是小跟堆
//利用单调栈建立笛卡尔树
void build() {
    int top = 0;
    for (int i = 1; i <= n; i++) {
        int pos = top;

        while (pos > 0 && arr[sta[pos]] > arr[i]) {
            //单调栈  弹出不符合的元素
            pos--;
        }

        // 插入一个元素 它是连接在哪个节点的右孩子上的   哪些节点连接到它的左孩子
        if (pos > 0) {
            //那么就是没有弹干净   那么当前节点就会成为栈顶节点的右孩子
            rs[sta[pos]] = i;
        }

        if (pos < top) {
            //表示有元素弹出 那么一定是当前节点的左孩子节点
            ls[i] = sta[pos + 1];
        }

        sta[++pos] = i;//加入栈中
        top = pos;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    build();
    long long ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; i++) {
        ans1 ^= 1LL * i * (ls[i] + 1);
        ans2 ^= 1LL * i * (rs[i] + 1);
    }
    cout << ans1 << " " << ans2 << endl;
    return 0;
}