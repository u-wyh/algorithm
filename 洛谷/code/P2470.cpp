#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 110;
int f[N][N][2];  // f[i][j][0]: 区间[i,j]没有M的最小长度, f[i][j][1]: 区间[i,j]有M的最小长度
char s[N];

// 检查区间[l, r]是否可以分成两个相同的部分
bool check(int l, int r) {
    int len = r - l + 1;
    if (len % 2 != 0) return false;
    
    int mid = (l + r) / 2;
    for (int i = 0; i <= mid - l; i++) {
        if (s[l + i] != s[mid + 1 + i]) {
            return false;
        }
    }
    return true;
}

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    
    // 初始化：单个字符的长度为1
    for (int i = 1; i <= n; i++) {
        f[i][i][0] = 1;
        f[i][i][1] = 1;
    }
    
    // 区间DP：从小区间到大区间
    for (int len = 2; len <= n; len++) {        // 区间长度
        for (int i = 1; i + len - 1 <= n; i++) { // 区间起点
            int j = i + len - 1;                 // 区间终点
            
            // 初始化为区间原始长度
            f[i][j][0] = f[i][j][1] = len;
            
            // 状态1：区间内有M
            // 枚举M的位置k，将区间分成[i,k]和[k+1,j]
            for (int k = i; k < j; k++) {
                f[i][j][1] = min(f[i][j][1], 
                                min(f[i][k][0], f[i][k][1]) + 1 +  // 前半部分 + M
                                min(f[k+1][j][0], f[k+1][j][1]));  // 后半部分
            }
            
            // 状态0：区间内没有M
            // 直接分割区间，不使用M
            for (int k = i; k < j; k++) {
                f[i][j][0] = min(f[i][j][0], f[i][k][0] + j - k);
            }
            
            // 如果区间可以压缩（分成两个相同的部分）
            if (check(i, j)) {
                int mid = (i + j) / 2;
                f[i][j][0] = min(f[i][j][0], f[i][mid][0] + 1);
            }
        }
    }
    
    printf("%d\n", min(f[1][n][0], f[1][n][1]));
    return 0;
}