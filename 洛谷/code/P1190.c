#include <stdio.h>

int s[11000];
int ans = 0;  // 初始化ans为0

int main() {
    int n, m;
    scanf("%d %d", &n, &m);  // 读取学生数量n和水龙头数量m

    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);  // 读取每个学生的接水量
    }

    int t = m + 1;  // t用来记录下一个学生的编号

    while (t <= n + m) {
        for (int i = 1; i <= m; i++) {  // 枚举m个水龙头
            s[i]--;
            if (s[i] == 0) {
                // 如果这个学生的水接完了，模拟换下一个学生来这个水龙头
                if (t <= n) {  // 确保t没有超出学生数量
                    s[i] = s[t];
                    t++;
                }
            }
        }
        ans++;  // 模拟的1秒钟的接水时间，ans加一
    }

    printf("%d\n", ans);  // 输出结果

    return 0;
}
