#include <stdio.h>
#include <limits.h>

typedef struct {
    int a, b;
} Cow;

Cow cows[10];
int n, minn = INT_MAX;
int bj[10];
int fzsx[10];

void add() {
    int sum = 1;  // 第一头牛需要一个牛棚
    for (int i = 2; i <= n; i++) {
        sum += (cows[fzsx[i]].b > cows[fzsx[i - 1]].a) ? cows[fzsx[i]].b : cows[fzsx[i - 1]].a;
        sum += 1;  // 加上当前牛的牛棚
    }
    if (sum < minn) {
        minn = sum;
    }
}

void dfs(int x) {
    if (x - 1 == n) {
        add();
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!bj[i]) {
            bj[i] = 1;
            fzsx[x] = i;
            dfs(x + 1);
            bj[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &cows[i].a);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &cows[i].b);
    }
    dfs(1);
    printf("%d\n", minn);
    return 0;
}
