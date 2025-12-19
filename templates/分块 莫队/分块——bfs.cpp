// 磁力块，C++版
// 磁块有五个属性值，x、y、m、p、range，磁块在(x, y)位置、质量为m、磁力为p、吸引半径range
// 磁块A可以把磁块B吸到磁块A的位置，需要满足如下的条件
// A与B的距离不大于A的吸引半径，并且B的质量不大于A的磁力
// 你有一个初始磁块，给定初始磁块的4个属性值(不给质量，因为没用)，你永远在初始磁块的位置
// 接下来给定n个磁块各自的5个属性值，你可以用初始磁块，吸过来其中的磁块
// 吸过来的磁块可以被你随意使用，返回你最多能吸过来多少磁块
// 1 <= n <= 3 * 10^5    -10^9 <= x、y <= +10^9    1 <= m、p、range <= 10^9
// 测试链接 : https://www.luogu.com.cn/problem/P10590
// 测试链接 : https://codeforces.com/problemset/problem/198/E
// 如下实现是C++的版本，C++版本和java版本逻辑完全一样
// 提交如下代码，可以通过所有测试用例
// 这道题的大流程是bfs  每个磁力块遍历所有的磁力块  看看能不能吸引进入队列
// 但是如果这样的话 时间复杂度是O(n*n)  我们必须剪枝  并且降低时间复杂度
// 这道题的思路是首先按照质量大小排序  然后进行分组    并记录这个组的最大质量 
// 在分组之后 按照距离组内重排 （哈哈哈 竟然有点类似于cdq）
// 为了避免精度问题 这里全部使用平方
// 这道题的优化包括  如果当前访问的块的最大质量超出了能力  那么下面的块也不用访问了
// 如果当前的块中有的元素已经访问了  那么左边界可以右移
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300001;
const int MAXB = 601;

struct Node {
    int x, y, m, p;
    long long range;
    long long dist;
};

//按照质量排序
bool cmp1(Node &a, Node &b) {
    return a.m < b.m;
}

//按照距离排序
bool cmp2(Node &a, Node &b) {
    return a.dist < b.dist;
}

int n;
Node arr[MAXN];

int blen, bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];
int maxm[MAXB];

int que[MAXN];
bool vis[MAXN];

int bfs() {
    int ans = 0;
    vis[0] = true;
    int l = 1, r = 1;
    que[r++] = 0;
    while (l < r) {
        int cur = que[l++];
        //再加入队列之前  必须要检查之前是否已经进入过l队列  因为有的时候是可能已经进入过队列
        //比如说这个组的最大值过大   导致需要遍历这个组   此时符合要求的就已经进入过了
        for (int b = 1; b <= bnum; b++) {
            //判断这个组的最大质量是否可以被当前的磁块所吸引
            if (maxm[b] <= arr[cur].p) {
                while (bl[b] <= br[b] && arr[bl[b]].dist <= arr[cur].range) {
                    int i = bl[b];
                    if (!vis[i]) {
                        vis[i] = true;
                        que[r++] = i;
                        ans++;
                    }
                    bl[b]++;//这个组的左边界右移  不回退  一个优化
                }
            } else {
                //如果这个组的最大质量不满足  那么之后的组也一定不满足 遍历完这个组之后  直接退出
                for (int i = bl[b]; i <= br[b]; i++) {
                    if (arr[i].dist <= arr[cur].range && arr[i].m <= arr[cur].p && !vis[i]) {
                        //符合条件  进入队列
                        vis[i] = true;
                        que[r++] = i;
                        ans++;
                    }
                }
                break;
            }
        }
    }
    return ans;
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
    sort(arr + 1, arr + n + 1, cmp1);
    for (int i = 1; i <= bnum; i++) {
        maxm[i] = arr[br[i]].m;//记录这个块内的最大质量
        sort(arr + bl[i], arr + br[i] + 1, cmp2);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, y, m, p, range;
    cin >> x >> y >> p >> range >> n;
    arr[0] = {x, y, 0, p, range, 0};
    for (int i = 1; i <= n; i++) {
        cin >> x >> y >> m >> p >> range;
        arr[i] = {x, y, m, p, range, 0};
    }
    long long xd, yd;
    for (int i = 0; i <= n; i++) {
        arr[i].range = arr[i].range * arr[i].range;//磁力值（平方）
        xd = arr[0].x - arr[i].x;
        yd = arr[0].y - arr[i].y;
        arr[i].dist = xd * xd + yd * yd;//到0磁块的距离 （平方）
    }
    prepare();
    cout << bfs() << '\n';
    return 0;
}