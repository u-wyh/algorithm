#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
int i[20], v[20], x[20], l[20], c[20], d[20], m[20], A[20];
int ansi, ansv, ansx, ansl, ansc, ansd, ansm;

void mem() {
    A[1] = 1; i[1] = 1;
    A[2] = 4; i[2] = 1; v[2] = 1;
    A[3] = 5; v[3] = 1;
    A[4] = 9; i[4] = 1; x[4] = 1;
    A[5] = 10; x[5] = 1;
    A[6] = 40; x[6] = 1; l[6] = 1;
    A[7] = 50; l[7] = 1;
    A[8] = 90; x[8] = 1; c[8] = 1;
    A[9] = 100; c[9] = 1;
    A[10] = 400; c[10] = 1; d[10] = 1;
    A[11] = 500; d[11] = 1;
    A[12] = 900; c[12] = 1; m[12] = 1;
    A[13] = 1000; m[13] = 1;
}

void add(int b, int num) {
    ansi += i[b] * num;
    ansv += v[b] * num;
    ansx += x[b] * num;
    ansl += l[b] * num;
    ansc += c[b] * num;
    ansd += d[b] * num;
    ansm += m[b] * num;
}

int main() {
    scanf("%d", &n);
    mem();
    for (int j = 1; j <= n; j++) {
        int temp = j, now = 13;
        while (temp) {
            while (temp < A[now]) now--;
            add(now, temp / A[now]);
            temp %= A[now];
        }
    }
    if (ansi != 0) printf("I %d\n", ansi);
    if (ansv != 0) printf("V %d\n", ansv);
    if (ansx != 0) printf("X %d\n", ansx);
    if (ansl != 0) printf("L %d\n", ansl);
    if (ansc != 0) printf("C %d\n", ansc);
    if (ansd != 0) printf("D %d\n", ansd);
    if (ansm != 0) printf("M %d\n", ansm);
    return 0;
}
