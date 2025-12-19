#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int x, y;
} node;

node b[405];
int n, m, a[405], ans;

int main() {
    scanf("%d %d", &n, &m);
    int x, y;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &b[i].x, &b[i].y);
    }

    for (int i = 0; i < (1 << n); i++) {
        bool bj = false; // C语言中，布尔类型用false和true表示
        for (int j = 1; j <= m; j++) {
            if ((i & (1 << (b[j].x - 1))) && (i & (1 << (b[j].y - 1)))) {
                bj = true;
                break;
            }
        }
        if (!bj) ans++;
    }

    printf("%d\n", ans);
    return 0;
}
