#include<stdio.h>

int n, m, w[10001], s[101], maxx; // 定义全局变量

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]); // 输入每个人打水需要的时间
    }

    // 初始化s数组为0（虽然全局变量默认初始化为0，但明确写出更清晰）
    for (int i = 0; i < m; i++) {
        s[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        maxx = 1; // 假设第一个水龙头是最小的
        for (int j = 2; j <= m; j++) {
            if (s[maxx] > s[j]) {
                maxx = j; // 找到当前最小的水龙头
            }
        }
        s[maxx] += w[i]; // 将当前人的打水时间加到找到的最小的水龙头上
    }

    // 遍历s数组找到最大值
    maxx = 0; // 初始化为0，因为s数组中的值都是非负的
    for (int i = 1; i <= m; i++) {
        if (s[i] > maxx) {
            maxx = s[i];
        }
    }

    printf("%d\n", maxx); // 输出最大值，并添加换行符以符合常规输出格式
    return 0; // 显式返回0表示程序正常结束
}
