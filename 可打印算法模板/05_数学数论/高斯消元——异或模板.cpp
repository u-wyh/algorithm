// 用途：异或高斯消元求 GF(2) 方程组。
// 时间：O(n³+n·2^f)，f 为消元后的自由元数。
// 空间：O(n²)。
// 例题：https://www.luogu.com.cn/problem/P2962
// 题意：开关影响自身及邻点，求让所有灯达到目标状态的最少操作数。
// 思路：建模为 GF(2) 方程组，高斯消元后枚举自由元求最少 1 的解。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 37;

int mat[MAXN][MAXN];
int op[MAXN];
int n,m,ans;

void prepare() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mat[i][j] = 0;
        }
        mat[i][i] = 1;
        mat[i][n + 1] = 1;
        op[i] = 0;
    }
}

// 高斯消元解决异或方程组模版
// 需要保证变量有n个，表达式也有n个
void gauss(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < i && mat[j][j] == 1) {
                continue;
            }
            if (mat[j][i] == 1) {
                swap(mat[i], mat[j]);
                break;
            }
        }
        if (mat[i][i] == 1) {
            for (int j = 1; j <= n; j++) {
                if (i != j && mat[j][i] == 1) {
                    for (int k = i; k <= n + 1; k++) {
                        mat[j][k] ^= mat[i][k];
                    }
                }
            }
        }
    }
}

//表示当前来到了第i号元  已经改了num次
void dfs(int i, int num) {
    if (num >= ans) { // 剪枝
        return;
    }
    if (i == 0) {
        ans = num;
    } else {
        if (mat[i][i] == 0) {
            // 当前是自由元
            // 自由元一定不依赖主元
            // 自由元也一定不依赖其他自由元
            // 所以当前自由元一定可以自行决定要不要操作
            op[i] = 0;
            dfs(i - 1, num);
            op[i] = 1;
            dfs(i - 1, num + 1);
        } else {
            // 当前是主元
            // 主元可能被其他自由元影响
            // 而且一定有，当前主元的编号 < 影响它的自由元编号
            // 所以会影响当前主元的自由元们，一定已经确定了要不要操作
            // 那么当前主元要不要操作，也就确定了
            //确定这个是主元之后  即使前面依旧存在自由元   但是绝不会影响这个主元的选择
            //能够影响当前主元的一定已经遍历过了
            int cur = mat[i][n + 1];
            for (int j = i + 1; j <= n; j++) {
                if (mat[i][j] == 1) {
                    cur ^= op[j];
                }
            }
            dfs(i - 1, num + cur);
        }
    }
}

int main()
{
    cin>>n>>m;
    prepare();
    for (int i = 1, u, v; i <= m; i++) {
        cin>>u>>v;
        mat[u][v] = 1;
        mat[v][u] = 1;
    }
    gauss(n);
    int sign = 1;
    for (int i = 1; i <= n; i++) {
        if (mat[i][i] == 0) {
            sign = 0;//表示存在自由元
            break;
        }
    }
    if (sign == 1) {
        // 唯一解  说明没有自由元
        // 那么需要调整的就只有值为1的点
        ans = 0;
        for (int i = 1; i <= n; i++) {
            if (mat[i][n + 1] == 1) {
                ans++;
            }
        }
    } else {
        // 多解
        //暴力dfs  寻找最小的答案
        ans = n;//最多只有n次
        dfs(n, 0);
    }
    cout<<ans<<endl;
    return 0;
}
