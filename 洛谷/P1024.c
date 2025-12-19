#include<stdio.h>

double a, b, c, d;

double fc(double x) {
    return a * x * x * x + b * x * x + c * x + d;
}

int main() {
    double l, r, m, x1, x2;
    int s = 0, i;

    // 输入
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
