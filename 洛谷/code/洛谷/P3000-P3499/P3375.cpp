// https://www.luogu.com.cn/problem/P3375
// 题意：给主串 s1 和模式串 s2，
// 按从小到大的顺序输出 s2 在 s1 中每次出现的起点。
// 最后一行输出 |s2| 个数。
// 对 s2 的每个非空前缀，求它最长的相同真前缀和真后缀的长度。
// 这里的真前缀、真后缀都必须比正在处理的那段字符串短。
// 数据范围：1 ≤ |s1|, |s2| ≤ 10^6，两个串都只含大写英文字母。
// 算法标签：KMP

#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1e6 + 10;

char s1[MAXN], s2[MAXN];
int n, m;
int nxt[MAXN];  // 1-based next数组

// 计算1-based next数组
void calcNext() {
    nxt[1] = 0;  // 第一个字符的next值固定为0
    
    // j表示当前匹配的前缀长度
    for (int i = 2, j = 0; i <= m; i++) {
        // 当不匹配时，通过next数组回溯
        while (j > 0 && s2[i] != s2[j + 1]) 
            j = nxt[j];
        
        // 如果当前字符匹配，j增加
        if (s2[i] == s2[j + 1]) 
            j++;
        
        // 设置当前位置的next值
        nxt[i] = j;
    }
}

// KMP匹配函数
void kmp() {
    // 计算主串和模式串长度
    n = strlen(s1 + 1);
    m = strlen(s2 + 1);
    
    calcNext();
    
    // 进行KMP匹配
    for (int i = 1, j = 0; i <= n; i++) {
        // 当不匹配时，通过next数组回溯
        while (j > 0 && s1[i] != s2[j + 1])
            j = nxt[j];
        
        // 如果当前字符匹配，j增加
        if (s1[i] == s2[j + 1]) 
            j++;
        
        // 完全匹配成功
        if (j == m) {
            // 输出匹配位置(1-based)
            cout << i - m + 1 << endl;
            // 继续寻找下一个匹配
            j = nxt[j];
        }
    }
}

int main() {
    // 从位置1开始读入字符串
    scanf("%s%s", s1 + 1, s2 + 1);
    
    kmp();
    
    // 输出1-based next数组
    for (int i = 1; i <= m; i++) {
        printf("%d ", nxt[i]);
    }
    puts("");
    
    return 0;
}