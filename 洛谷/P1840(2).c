#include <stdio.h>

int st[200005];

int getfa(int x) {
    return x == st[x] ? x : (st[x] = getfa(st[x]));
}

void unio(int a, int b) {
    st[getfa(b)] = getfa(a);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    int blkn = n;
    for (int i = 1; i <= n + 1; ++i) {
        st[i] = i;
    }
    for (int i = 1; i <= m; ++i) {
        int li, ri;
        scanf("%d%d", &li, &ri);

        int t = getfa(li);
        while (t <= ri) {
            unio(t + 1, t);
            t = getfa(t);
            --blkn;
        }

        printf("%d\n", blkn);
    }

    return 0;
}
