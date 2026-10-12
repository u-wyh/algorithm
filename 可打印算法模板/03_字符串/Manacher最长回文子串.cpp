// 用途：线性求字符串最长回文子串长度。
// 时间：O(n)。
// 空间：O(n)。
// 注意：输入不含空白；半径定义见代码。
// 例题：https://www.luogu.com.cn/problem/P3805
// 题意：求字符串中最长连续回文子串的长度。
// 思路：插入分隔符统一奇偶长度，利用对称回文半径加速扩展。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 11000001;

char ss[MAXN << 1];//这个数组中间添加了#
char a[MAXN];//原始数组
// p[i] 是加入分隔符后以 i 为中心的回文半径。
int p[MAXN << 1];//半径数组
int n;

void manacherss() {
    n = strlen(a) * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : a[j++];
    }
}

int manacher() {
    manacherss();
    int maxans = 0;
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {
        len = r > i ? min(p[2 * c - i], r - i) : 1;
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]) {
            len++;
        }
        if (i + len > r) {
            r = i + len;
            c = i;//c表示的是如今的r是以那个点为中心的右边界
        }
        maxans = max(maxans, len);
        p[i] = len;
    }
    return maxans - 1;
}

int main()
{
    scanf("%s",a);
    cout<<manacher();
    return 0;
}
