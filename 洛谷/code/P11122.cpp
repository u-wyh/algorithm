#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 20;

int n, m;
LL s;
int a[N][N];
LL l[N];

int main() {
    scanf("%d%d", &n, &m);

    LL sum = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            sum += a[i][j];
        }
    }
    scanf("%lld", &s);

    if(sum == s) {
        puts("YES");
        printf("0");
        return 0;
    }
    
    const int totalRows = n;
    const int totalCols = m;
    const int halfCols = totalCols / 2;
    const int secHalfCols = totalCols - halfCols;
    
    int t1 = 0, t2 = 0, t3 = 0;
    bool found = false;
    
    for(int i = 0; i < (1 << totalRows); i++) {
        // 计算每列在保留行下的和（行优先顺序）
        for(int j = 1; j <= totalCols; j++) l[j] = 0;
        for(int k = 1; k <= totalRows; k++) {
            if(i >> (k-1) & 1) {
                for(int j = 1; j <= totalCols; j++) {
                    l[j] += a[k][j];
                }
            }
        }
        
        unordered_map<LL, int> Map;
        Map.reserve(1 << halfCols);  // 预分配空间
        
        // 前半部分列
        for(int j = 0; j < (1 << halfCols); j++) {
            LL t = 0;
            for(int k = 0; k < halfCols; k++) {
                t += ((j >> k) & 1) * l[k+1];
            }
            Map[t] = j;
        }
        
        // 后半部分列
        for(int j = 0; j < (1 << secHalfCols); j++) {
            LL t = 0;
            for(int k = 0; k < secHalfCols; k++) {
                t += ((j >> k) & 1) * l[halfCols + k + 1];
            }
            
            if(Map.find(s - t) != Map.end()) {
                t1 = Map[s - t];
                t2 = j;
                t3 = i;
                found = true;
                goto end;
            }
        }
    }

    puts("NO");
    return 0;
    
end:
    if (!found) {
        puts("NO");
        return 0;
    }
    
    puts("YES");
    int cnt = 0;
    for(int i = 1; i <= totalRows; i++) {
        if(!((t3 >> (i-1)) & 1)) cnt++;
    }
    for(int i = 0; i < halfCols; i++) {
        if(!((t1 >> i) & 1)) cnt++;
    }
    for(int i = 0; i < secHalfCols; i++) {
        if(!((t2 >> i) & 1)) cnt++;
    }
    
    printf("%d\n", cnt);
    for(int i = 1; i <= totalRows; i++) {
        if(!((t3 >> (i-1)) & 1)) {
            printf("1 %d\n", i);
        }
    }
    for(int i = 0; i < halfCols; i++) {
        if(!((t1 >> i) & 1)) {
            printf("2 %d\n", i+1);
        }
    }
    for(int i = 0; i < secHalfCols; i++) {
        if(!((t2 >> i) & 1)) {
            printf("2 %d\n", halfCols + i + 1);
        }
    }
    
    return 0;
}