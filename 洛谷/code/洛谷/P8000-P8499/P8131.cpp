// https://www.luogu.com.cn/problem/P8131
// 题意：给定仅由字符 A, C, G, T 组成的字符串 s。
// 每次可在某两个相邻字符间选一个折叠点
// （要求从该点向左右两侧延伸直到先碰到某一端点的长度内，两侧字符序列互为回文对称）
// ，沿该点折叠并合并重合的相同字符。
// 求经过零次或多次折叠操作后字符串的最小可能长度。
// 输入一行字符串 s。
// 输出一行一个整数。
// 数据范围：1 <= |s| <= 4*10^6，仅含 A, C, G, T。
// 算法标签：Manacher、贪心
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e6+5;

char ss[MAXN << 1];//这个数组中间添加了#
char s[MAXN];//原始数组
int p[MAXN << 1];//半径数组
int n;

void manacherss() {
    n = strlen(s) * 2 + 1;
    for (int i = 0, j = 0; i < n; i++) {
        ss[i] = (i & 1) == 0 ? '#' : s[j++];
    }
}

void manacher() {
    manacherss();
    for (int i = 0, c = 0, r = 0, len; i < n; i++) {
        len = r > i ? min(p[2 * c - i], r - i) : 1;
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len]) {
            len++;
            //如果被包住了  根本就进不来
        }
        //此时已经求出了以i为中心的回文半径大小
        if (i + len > r) {
            r = i + len;
            c = i;
        }
        p[i] = len;
    }
}

int main()
{
    scanf("%s",s);
    manacher();
    // for(int i=0;i<n;i++){
    //     cout<<p[i]<<' ';
    // }
    // cout<<endl;
    int l=0,r=n-1;
    for(int i=0;i<n;i+=2){
        if(i-p[i]+1<=l){
            l=i;
        }
    }
    for(int i=n-1;i>l;i-=2){
        if(i+p[i]-1>=r){
            r=i;
        }
    }
    cout<<(r-l)/2<<endl;
    return 0;
}