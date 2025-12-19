// 炮兵阵地
// 给定一个n * m的二维数组grid，其中的1代表可以摆放炮兵，0代表不可以摆放
// 任何炮兵攻击范围是一个"十字型"的区域，具体是上下左右两个格子的区域
// 你的目的是在gird里摆尽量多的炮兵，但要保证任何两个炮兵之间无法互相攻击
// 返回最多能摆几个炮兵
// 1 <= n <= 100
// 1 <= m <= 10
// 0 <= grid[i][j] <= 1
// 测试链接 : https://www.luogu.com.cn/problem/P2704
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
//这种预处理方式是减少不必要的情况枚举 只枚举可能对答案有贡献的状态
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100;
const int MAXM = 10;
const int MAXS = 60;

int grid[MAXN][MAXM];
int dp[MAXN][MAXS][MAXS];//dp[i][j][k]表示的是第i行（从0开始）的状态是sta[j] 上一行的状态是sta[k]的情况下填的最多可以是多少
int sta[MAXS];//sta数组存储的是对于一行而言 所有的有效状态
int n, m, k;

void prepare(int j, int s) {
    if (j >= m) {
        sta[k++] = s;
    } else {
        prepare(j + 1, s);//表示这个位置不放  去下一个位置继续
        prepare(j + 3, s | (1 << j));//表示这个位置放 去第三个位置继续
    }
}

// 第i行士兵状态为s，结合grid第i号的状况
// 返回摆放士兵的数量
int onecnt(int i, int s) {
	int ans = 0;
	for (int j = 0; j < m; j++) {
		if (((s >> j) & 1) == 1 && grid[i][j] == 1) {
			ans++;
		}
	}
	return ans;
}

int main()
{
    cin>>n>>m;
    k=0;//记录的是对于一行而言 有效状态的总数
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin>>c;
            grid[i][j] = c == 'H' ? 0 : 1;
        }
    }
    prepare(0,0);
    for (int a = 0, cnt; a < k; a++) {
        cnt = onecnt(0, sta[a]);
        dp[0][a][0] = cnt;
    }
    for (int i = 1; i < n; i++) {
        for (int a = 0, cnt; a < k; a++) {
            cnt = onecnt(i, sta[a]);//表示这一行如果状态是sta[a]  实际可以放多少个
            for (int b = 0; b < k; b++) {
                if ((sta[a] & sta[b]) == 0) {
                    //这里要求和上一行不能冲突  虽然可能实际上是不冲突的  但是不冲突的情况也可以被其他的状态计算  那么我就没有必要挽留了
                    for (int c = 0; c < k; c++) {
                        if ((sta[b] & sta[c]) == 0 && (sta[a] & sta[c]) == 0) {
                            dp[i][a][b] = max(dp[i][a][b], dp[i - 1][b][c] + cnt);
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int a = 0; a < k; a++) {
        for (int b = 0; b < k; b++) {
            ans = max(ans, dp[n - 1][a][b]);
        }
    }
    cout<<ans;
    return 0;
}
