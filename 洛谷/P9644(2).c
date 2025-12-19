#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int n, k;
char s[200005];

bool check(int x) {
    int p = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') {
            p = i; // 找到第一个'1'
            break;
        }
    }
    int cnt = 0; // 记录段数
    while (p <= n) {
        p += x;
        cnt++;
        if (p > n) break; // 控制边界
        while (s[p] == '0') p++; // 如果是'0'则无需覆盖
    }
    if (cnt <= k) return true; // 符合条件
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &k);
        scanf("%s", s + 1); // 从s[1]开始读入字符串，s[0]未使用
        int l = 1; // 左端点设为1
        int r = n / k + 1; // 假设每个段都尽可能短

        while (l < r) { // 二分答案
            int mid = (l + r) / 2;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }
        printf("%d\n", l);
    }
    return 0;
}
