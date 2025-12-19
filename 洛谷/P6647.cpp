#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n, m, a[MAXN];
long long f[MAXN], g[MAXN];  // f[i]: 到i位置的最大评分和; g[i]: 后缀最大值
int x[MAXN];          // x[i]: 当前块从块首到i的最大值
int pos[MAXN], L[MAXN], R[MAXN], numb;  // 分块信息

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    
    // 分块处理
    numb = n / m;  // 基本块数
    for(int i = 1; i <= numb; i++) {
        L[i] = R[i-1] + 1;
        R[i] = i * m;
    }
    // 处理剩余部分
    if(R[numb] <= n) {
        numb++;
        L[numb] = R[numb-1] + 1;
        R[numb] = n;
    }
    
    // 预处理每块的前缀最大值
    for(int i = 1; i <= numb; i++) {
        for(int j = L[i]; j <= R[i]; j++) {
            if(j == L[i]) x[j] = a[j];
            else x[j] = max(x[j-1], a[j]);
        }	
    }
    
    // 初始化第一块
    for(int i = L[1]; i <= R[1]; i++) f[i] = x[i];
    for(int i = R[1]; i >= L[1]; i--) 
        g[i] = max(g[i+1], f[i]);
    
    // 处理后续块
    for(int k = 2; k <= numb; k++) {
        long long mx = 0;
        int j = R[k-1], mx2 = 0;
        
        // 预处理：从上一块右端点向左扫描
        while(j > R[k] - m) {
            mx = max(mx, f[j] + mx2);
            mx2 = max(mx2, a[j]);
            j--;
        }
        
        // 处理当前块（从右向左）
        for(int i = R[k]; i >= L[k]; i--) {
            mx = max(mx, f[j] + mx2);
            f[i] = max(mx, g[j] + x[i]);
            mx2 = max(mx2, a[j]);
            g[i] = max(g[i+1], f[i]);
            j--;
        }
    }
    
    cout << f[n] << endl;
    return 0;
}