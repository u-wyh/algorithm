// 用途：计算模式串 Z 数组和文本扩展匹配数组。
// 时间：O(n+m)。
// 空间：O(n+m)。
// 注意：输入文本、模式串；按原题输出两组加权异或值。
// 例题：https://www.luogu.com.cn/problem/P5410
// 题意：求模式串每个后缀与自身、文本后缀与模式串的最长公共前缀。
// 思路：维护当前最右匹配区间，复用区间内已有的 Z 值。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 20000001;

int n,m;
char a[MAXN];
char b[MAXN];
// z[i] 是模式串与其第 i 位后缀的最长公共前缀。
int z[MAXN];
// e[i] 是文本第 i 位后缀与模式串的最长公共前缀。
int e[MAXN];

void zArray(char* s, int n) {
    z[0] = n;
    for (int i = 1, c = 1, r = 1, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && s[i + len] == s[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        z[i] = len;
    }
}

void eArray(char* a, char* b, int n, int m) {
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {
        len = r > i ? min(r - i, z[i - c]) : 0;
        while (i + len < n && len < m && a[i + len] == b[len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        e[i] = len;
    }
}

long long eor(int* arr, int n) {
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans ^= 1LL * (i + 1) * (arr[i] + 1);
    }
    return ans;
}

int main()
{
    scanf("%s",a);
    n=strlen(a);
    scanf("%s",b);
    m=strlen(b);
    zArray(b,m);
    eArray(a,b,n,m);
    cout<<eor(z,m)<<endl;
    cout<<eor(e,n)<<endl;
    return 0;
}
