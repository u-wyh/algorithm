// https://www.luogu.com.cn/problem/P2994
// 题意：输入奶牛数 N、座位数 M，N 头牛的初始坐标 (CX_i, CY_i)
// 和 M 个座位的坐标 (SX_j, SY_j)。
// 所有奶牛以相同速度直线奔向座位，先到先得；
// 若多头牛同时到达同一座位则输入序号更小的牛获胜，
// 若一头牛同时最快到达多个座位则选择输入序号更小的座位。
// 找出最终没有抢到座位的饥饿奶牛列表（注意距离平方可能超过 32 位整数）。
// 按编号递增顺序每行输出一个未分到座位的奶牛编号；若全部牛都有座位则输出 0。
// 数据范围：对于 100% 的数据，1 <= N <= 10^3，
// 1 <= M <= N
// -10^6 <= CX_i, CY_i, SX_j, SY_j <= 10^6。
// 算法标签：模拟、枚举
#include <stdio.h>
#include <stdlib.h>

#define maxn 1005

long long int a[maxn], b[maxn], c, d; // 奶牛位置和座位位置
int flag[maxn]; // 标记奶牛是否有座位
int pos; // 记录有座位的奶牛编号

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &a[i], &b[i]);
    }
    for (int j = 1; j <= m; j++) {
        scanf("%lld %lld", &c, &d);
        long long int dis = 0; // 计算当前奶牛到座位的距离
        long long int mindis = 1e15; // 记录当前最小奶牛距桌子距离
        for (int i = 1; i <= n; i++) {
            if (flag[i] == 1) continue; // 已有座位，直接跳过
            dis = (a[i] - c) * (a[i] - c) + (b[i] - d) * (b[i] - d); // 计算距离
            if (dis < mindis) { // 如果刷新了最小纪录
                mindis = dis;
                pos = i;
            }
        }
        flag[pos] = 1; // 标记，已有座位
    }
    if (n == m) { // 特判没有奶牛无座位
        printf("0\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) { // 其他情况输出
        if (flag[i]) continue;
        printf("%d\n", i);
    }
    return 0;
}
