// https://www.luogu.com.cn/problem/P1024
// 题意：输入三次方程 ax^3+bx^2+cx+d=0 的四个实数系数，
// 按从小到大的顺序输出三个实根，每个保留两位小数。
// 数据范围：三个实根均在 [-100, 100]，任意两个的距离至少为 1。

    // 输入
// 难度评分：900（洛谷分级换算）
// 算法标签：枚举、二分查找
#include<stdio.h>

double a, b, c, d;

double fc(double x) {
    return a * x * x * x + b * x * x + c * x + d;
}

int main() {
    double l, r, m, x1, x2;
    int s = 0, i;

    scanf("%lf%lf%lf%lf", &a, &b, &c, &d);

    for (i = -100; i < 100; i++) {
        l = i;
        r = i + 1;
        x1 = fc(l);
        x2 = fc(r);

        // 判断左端点，是零点直接输出
        if (x1 == 0.0) {
            printf("%.2lf ", l);
            s++;
        }

        // 区间内有根
        if (x1 * x2 < 0.0) {
            while (r - l >= 0.001) {
                m = (l + r) / 2;
                if (fc(m) * fc(r) <= 0.0) {
                    l = m;
                } else {
                    r = m;
                }
            }
            // 注意：这里应该输出更精确的根的位置，即l或(l+r)/2
            printf("%.2lf ", l); // 或者使用 (l + r) / 2 来获取更精确的值
            s++;
        }

        // 找到三个就退出
        if (s == 3) {
            break;
        }
    }

    return 0;
}
