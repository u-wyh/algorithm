#include <bits/stdc++.h>
using namespace std;
#define maxn 1000005

int t;
int ed[maxn], cnt[maxn];
int tr[maxn][27], tot = 1;

void add(char *s, int len) {
    int p = 1;
    ++cnt[p];
    for (int i = 1; i <= len; ++i) {
        int u = s[i] - 'a' + 1;
        if (!tr[p][u]) {
            tr[p][u] = ++tot;
            memset(tr[tot], 0, sizeof tr[tot]); // 插入时顺便清空 trie
        }
        p = tr[p][u];
        ++cnt[p]; // 记录经过当前位置的字符串个数
    }
    ++ed[p]; // 记录从当前位置结束的字符串个数
    return;
}

char s[maxn];

void sol() {
    // 多测记得清空
    tot = 1;
    for (int i = 1; i <= 26; ++i)
        tr[1][i] = 0; // 清空首层
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        add(s, len);
    }
    int p = 1;
    // 题解大部分写的是 dfs，这里用简单循环实现
    while (1) {
        int sum = ed[p];
        for (int i = 1; i <= 26; ++i)
            if (cnt[tr[p][i]])
                ++sum; // 下一位每个字符串最多选一个
        if (sum >= k) {
            // 判定答案合法
            for (int i = 1; i <= tot; ++i) {
                ed[i] = 0;
                cnt[i] = 0;
            }
            if (p == 1) // 在首层，即答案为空字符串
                printf("EMPTY");
            putchar('\n');
            // 已经找到最优合法答案，结束程序即可
            return;
        }
        for (int i = 1; i <= 26; ++i) {
            if (!cnt[tr[p][i]])
                continue;
            sum += cnt[tr[p][i]] - 1;
            // 之所以减一，因为上面已经每个算了一个
            if (sum >= k) {
                // 确定下一位字母
                k -= (sum - cnt[tr[p][i]]);
                // 把当前可选所有字符串数从 k 中减掉
                putchar((char)('a' + i - 1));
                // 已确定，直接输出即可
                p = tr[p][i];
                break; // 进入下一位的枚举
            }
        }
    }
    return;
}

int main() {
    scanf("%d", &t);
    while (t--)
        sol();
    return 0;
}
