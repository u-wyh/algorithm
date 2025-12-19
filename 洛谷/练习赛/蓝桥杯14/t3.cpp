#include<bits/stdc++.h>
using namespace std;
#define MAX_LEN 20010

char s1[MAX_LEN], s2[MAX_LEN], s3[MAX_LEN];
int a[MAX_LEN], b[MAX_LEN], c[MAX_LEN], sum[MAX_LEN], diff[MAX_LEN], res[MAX_LEN];

int max(int a, int b) {
    return a > b ? a : b;
}

bool compare(char *s1, char *s2) {
    int n1 = strlen(s1);
    int n2 = strlen(s2);
    if (n1 != n2)
        return n1 > n2;
    for (int i = 0; i < n1; i++) {
        if (s1[i] != s2[i])
            return s1[i] > s2[i];
    }
    return true;
}

void subtract(char *s1, char *s2, int *result) {
    int la = strlen(s1);
    int lb = strlen(s2);
    for (int i = 0; i < la; i++)
        a[la - i] = s1[i] - '0';
    for (int i = 0; i < lb; i++)
        b[lb - i] = s2[i] - '0';
    int lc = max(la, lb);
    for (int i = 1; i <= lc; i++) {
        if (a[i] < b[i]) {
            a[i + 1]--;
            a[i] += 10;
        }
        result[i] = a[i] - b[i];
    }
    while (result[lc] == 0 && lc > 1)
        lc--;
    for (int i = lc; i > 0; i--)
        result[i] = result[i];
    result[0] = lc;
}

void add(char *s1, char *s2, int *result) {
    int la = strlen(s1);
    int lb = strlen(s2);
    for (int i = 0; i < la; i++)
        a[la - i] = s1[i] - '0';
    for (int i = 0; i < lb; i++)
        b[lb - i] = s2[i] - '0';
    int lc = max(la, lb);
    int carry = 0;
    for (int i = 1; i <= lc; i++) {
        result[i] = a[i] + b[i] + carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }
    if (carry > 0) {
        lc++;
        result[lc] = carry;
    }
    result[0] = lc;
}

void multiply(int *num1, int *num2, int *result) {
    int l1 = num1[0];
    int l2 = num2[0];
    for (int i = 0; i <= l1 + l2; i++)
        result[i] = 0;
    for (int i = 1; i <= l1; i++) {
        for (int j = 1; j <= l2; j++) {
            result[i + j - 1] += num1[i] * num2[j];
            result[i + j] += result[i + j - 1] / 10;
            result[i + j - 1] %= 10;
        }
    }
    int lc = l1 + l2;
    while (result[lc] == 0 && lc > 1)
        lc--;
    result[0] = lc;
}

int main() {
    scanf("%s", s1);
    scanf("%s", s2);

    bool A_neg = (s1[0] == '-');
    bool B_neg = (s2[0] == '-');

    char *a = A_neg ? s1 + 1 : s1;
    char *b = B_neg ? s2 + 1 : s2;

    if (A_neg == B_neg) {
        add(a, b, sum);
        if (compare(a, b)) {
            subtract(a, b, diff);
        } else {
            subtract(b, a, diff);
            if (!A_neg)
                diff[0] = -diff[0];
        }
    } else {
        if (compare(a, b)) {
            subtract(a, b, sum);
            if (A_neg)
                sum[0] = -sum[0];
        } else {
            subtract(b, a, sum);
            if (B_neg)
                sum[0] = -sum[0];
        }
        add(a, b, diff);
        if (A_neg)
            diff[0] = -diff[0];
    }

    int sum_sign = sum[0] < 0 ? -1 : 1;
    int diff_sign = diff[0] < 0 ? -1 : 1;
    sum[0] = abs(sum[0]);
    diff[0] = abs(diff[0]);

    multiply(sum, diff, res);

    if (sum_sign * diff_sign == -1)
        printf("-");
    for (int i = res[0]; i > 0; i--)
        printf("%d", res[i]);
    printf("\n");

    return 0;
}