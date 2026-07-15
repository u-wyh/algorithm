#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000 + 5;
const int MAXV = 1000000 + 5;

// n 为整数序列长度，k 为循环符号序列长度，maxValue 为 a_i 的最大值
int n, k, maxValue;

// a[i] 保存原整数序列的第 i 个元素
int a[MAXN];

// signSeq[i] 保存循环符号序列的第 i 个符号
char signSeq[MAXN];

// f[i] 表示以位置 i 结尾的合法子序列的最大长度
int f[MAXN];

// pre[i] 保存状态 i 的最优前驱位置，用于还原答案
int pre[MAXN];

// lessTree 维护下一步需要满足“<”的状态，节点中保存最优状态的结尾位置
int lessTree[MAXV];

// greaterTree 使用反向值域维护下一步需要满足“>”的状态
int greaterTree[MAXV];

// equalBest[x] 保存末尾值为 x 且下一步需要满足“=”的最优状态位置
int equalBest[MAXV];

// answerPath 保存答案子序列中每个元素在原序列里的位置
int answerPath[MAXN];

// answerLength 为最长合法子序列长度，answerEnd 为该子序列的结尾位置
int answerLength, answerEnd;

// 比较两个状态位置，返回 f 值更大的状态位置
int betterPosition(int x, int y) {
    return f[x] >= f[y] ? x : y;
}

// 在树状数组 tree 中，用状态位置 pos 更新值域位置 x
void updateFenwick(int tree[], int x, int pos) {
    for (int i = x; i <= maxValue; i += i & -i) {
        tree[i] = betterPosition(tree[i], pos);
    }
}

// 查询树状数组 tree 的前缀 [1, x] 中 f 值最大的状态位置
int queryFenwick(int tree[], int x) {
    int res = 0;

    for (int i = x; i > 0; i -= i & -i) {
        res = betterPosition(res, tree[i]);
    }

    return res;
}

// 读入整数序列和循环符号序列
void readInput() {
    cin >> n >> k;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        maxValue = max(maxValue, a[i]);
    }

    for (int i = 1; i <= k; ++i) {
        cin >> signSeq[i];
    }
}

// 使用动态规划和树状数组计算最长合法子序列，并记录前驱
void solve() {
    for (int i = 1; i <= n; ++i) {
        // bestPre 保存能够接到 a[i] 前面的最优状态位置
        int bestPre = equalBest[a[i]];

        // 查询末尾值小于 a[i] 且下一步需要“<”的最优状态
        bestPre = betterPosition(
            bestPre,
            queryFenwick(lessTree, a[i] - 1)
        );

        // 查询末尾值大于 a[i] 且下一步需要“>”的最优状态
        bestPre = betterPosition(
            bestPre,
            queryFenwick(greaterTree, maxValue - a[i])
        );

        f[i] = f[bestPre] + 1;
        pre[i] = bestPre;

        // nextSignPos 表示当前状态下一次需要使用的符号位置
        int nextSignPos = (f[i] - 1) % k + 1;

        if (signSeq[nextSignPos] == '<') {
            updateFenwick(lessTree, a[i], i);
        } else if (signSeq[nextSignPos] == '>') {
            // 将值 x 映射到 maxValue - x + 1，使大值出现在树状数组前方
            updateFenwick(
                greaterTree,
                maxValue - a[i] + 1,
                i
            );
        } else {
            equalBest[a[i]] = betterPosition(equalBest[a[i]], i);
        }

        if (f[i] > answerLength) {
            answerLength = f[i];
            answerEnd = i;
        }
    }
}

// 根据 pre 数组还原并输出一个最长合法子序列
void outputAnswer() {
    cout << answerLength << '\n';

    // cur 表示当前正在还原的状态位置
    int cur = answerEnd;

    for (int i = answerLength; i >= 1; --i) {
        answerPath[i] = cur;
        cur = pre[cur];
    }

    for (int i = 1; i <= answerLength; ++i) {
        if (i > 1) {
            cout << ' ';
        }

        cout << a[answerPath[i]];
    }

    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    readInput();
    solve();
    outputAnswer();

    return 0;
}