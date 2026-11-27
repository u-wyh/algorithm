// https://www.luogu.com.cn/problem/P3239
// 题意：输入测试组数 T，每组输入卡牌数 n、总轮数 r，
// 以及每张卡牌的发动概率 p_i（至多 4 位小数）和发动伤害 d_i。
// 共进行 r 轮，每轮从第 1 张到第 n 张依次考虑：若该张在本局已发动过则跳过
// 否则以 p_i 概率发动、造成 d_i 伤害
// 并立刻结束当前轮（未发动或跳过到第 n 张也结束本轮）。
// 每组输出一行一局造成总伤害的期望值（相对误差 <= 10^-8）。
// 数据范围：1 <= T <= 444，1 <= n <= 220，
// 0 <= r <= 132，0 < p_i < 1，
// 0 <= d_i <= 1000。
// 算法标签：概率动态规划
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

const int MAXN = 225;
const int MAXR = 135;

double f[MAXN][MAXR]; // f[i][j]: 前i张卡牌中有j张发动过技能的概率
double p[MAXN]; // 每张卡牌的发动概率
int d[MAXN]; // 每张卡牌的伤害
double pow_p[MAXN][MAXR]; // 预计算(1-p_i)^k

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int n, r;
        scanf("%d%d", &n, &r);
        
        for (int i = 1; i <= n; i++) {
            scanf("%lf%d", &p[i], &d[i]);
        }
        
        // 预计算幂次
        for (int i = 1; i <= n; i++) {
            pow_p[i][0] = 1.0;
            for (int j = 1; j <= r; j++) {
                pow_p[i][j] = pow_p[i][j-1] * (1 - p[i]);
            }
        }
        
        // 初始化
        memset(f, 0, sizeof(f));
        f[0][0] = 1.0;
        double ans = 0.0;
        
        // 动态规划
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= min(i, r); j++) {
                // 第i张卡牌没有被发动
                if (j <= i - 1) {
                    f[i][j] += f[i-1][j] * pow_p[i][r - j];
                }
                
                // 第i张卡牌被发动
                if (j > 0) {
                    double prob = 1.0 - pow_p[i][r - (j - 1)];
                    f[i][j] += f[i-1][j-1] * prob;
                }
            }
        }
        
        // 计算每张卡牌被发动的概率
        for (int i = 1; i <= n; i++) {
            double prob_i = 0.0;
            for (int j = 0; j <= min(i - 1, r); j++) {
                if (f[i-1][j] > 1e-10) {
                    double prob = 1.0 - pow_p[i][r - j];
                    prob_i += f[i-1][j] * prob;
                }
            }
            ans += prob_i * d[i];
        }
        
        printf("%.10lf\n", ans);
    }
    
    return 0;
}