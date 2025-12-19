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