#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5e4 + 5;
const int MAXK = 5;

int k, n;
int val[MAXK][MAXN];
int ord[MAXN];

// 用静态数组保存排序用的信息
pair<int, int> sortArr[MAXN];

void buildorder() {
    for (int i = 1; i <= n; i++) {
        ord[i] = i;
    }
}

// 按每一列内部极差从大到小排序
void buildsortorder() {
    for (int col = 1; col <= n; col++) {
        int mn = INT_MAX;
        int mx = INT_MIN;

        for (int row = 1; row <= k; row++) {
            mn = min(mn, val[row][col]);
            mx = max(mx, val[row][col]);
        }

        // 第一关键字取负数，sort 升序后就是极差从大到小
        sortArr[col] = {-(mx - mn), col};
    }

    sort(sortArr + 1, sortArr + n + 1);

    for (int i = 1; i <= n; i++) {
        ord[i] = sortArr[i].second;
    }
}

// 获取第 col 列旋转 r 次后，第 row 行的值
int getval(int col, int row, int r) {
    int oldRow = row - r;

    while (oldRow <= 0) {
        oldRow += k;
    }

    return val[oldRow][col];
}

// 给定当前 ord 顺序，按照这个顺序贪心计算答案
int calc() {
    int minn[MAXK], maxx[MAXK];

    for (int i = 1; i <= k; i++) {
        minn[i] = INT_MAX;
        maxx[i] = INT_MIN;
    }

    for (int idx = 1; idx <= n; idx++) {
        int col = ord[idx];

        int best = 0;
        int bestval = INT_MAX;

        // 枚举当前列转几次
        for (int r = 0; r < k; r++) {
            int curval = 0;

            for (int row = 1; row <= k; row++) {
                int v = getval(col, row, r);

                int newMin = min(minn[row], v);
                int newMax = max(maxx[row], v);

                curval = max(curval, newMax - newMin);
            }

            // 当前答案更小就更新；相等时用 r 的奇偶简单扰动
            if (curval < bestval || (curval == bestval && (r & 1))) {
                best = r;
                bestval = curval;
            }
        }

        // 应用当前列最优旋转
        for (int row = 1; row <= k; row++) {
            int v = getval(col, row, best);

            minn[row] = min(minn[row], v);
            maxx[row] = max(maxx[row], v);
        }
    }

    int ans = 0;

    for (int row = 1; row <= k; row++) {
        ans = max(ans, maxx[row] - minn[row]);
    }

    return ans;
}

int compute() {
    if (k == 1) {
        int mn = INT_MAX;
        int mx = INT_MIN;

        for (int i = 1; i <= n; i++) {
            mn = min(mn, val[1][i]);
            mx = max(mx, val[1][i]);
        }

        return mx - mn;
    }

    if (k == 2) {
        int ans = 0;

        int mn = INT_MAX;
        int mx = INT_MIN;

        for (int i = 1; i <= n; i++) {
            if (val[1][i] > val[2][i]) {
                swap(val[1][i], val[2][i]);
            }

            mn = min(mn, val[1][i]);
            mx = max(mx, val[1][i]);
        }

        ans = mx - mn;

        mn = INT_MAX;
        mx = INT_MIN;

        for (int i = 1; i <= n; i++) {
            mn = min(mn, val[2][i]);
            mx = max(mx, val[2][i]);
        }

        ans = max(ans, mx - mn);

        return ans;
    }

    mt19937 rng(
        chrono::steady_clock::now().time_since_epoch().count()
    );

    int ans = INT_MAX;

    // 原始顺序贪心
    buildorder();
    ans = min(ans, calc());

    // 极差排序顺序贪心
    buildsortorder();
    ans = min(ans, calc());

    // 随机顺序贪心
    buildorder();

    int times;

    if (k == 3) {
        if (n <= 50) {
            times = 1200;
        } else if (n <= 300) {
            times = 800;
        } else if (n <= 3000) {
            times = 500;
        } else {
            times = 280;
        }
    } else {
        if (n <= 50) {
            times = 2000;
        } else if (n <= 300) {
            times = 1200;
        } else if (n <= 2500) {
            times = 700;
        } else if (n <= 5000) {
            times = 500;
        } else {
            times = 350;
        }
    }

    for (int t = 1; t <= times; t++) {
        shuffle(ord + 1, ord + n + 1, rng);

        ans = min(ans, calc());

        if (ans == 0) {
            break;
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T >> k;

    while (T--) {
        cin >> n;

        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> val[i][j];
            }
        }

        cout << compute() << '\n';
    }

    return 0;
}