#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 200005;
int n;
int dfs0[MAXN], bfs0[MAXN];
int rank_bfn[MAXN];
int d[MAXN], pos[MAXN];
int flag[MAXN];
int diff[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &dfs0[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &bfs0[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        rank_bfn[bfs0[i]] = i;
    }
    
    for (int i = 1; i <= n; i++) {
        d[i] = rank_bfn[dfs0[i]];
    }
    
    for (int i = 1; i <= n; i++) {
        pos[d[i]] = i;
    }

    for(int i=1;i<=n;i++){
        cout<<d[i]<<' ';
    }
    cout<<endl;
    
    flag[1] = 1;
    for (int i = 2; i < n; i++) {
        if (pos[i] > pos[i+1]) {
            flag[i] = 1;
        }
    }
    
    for (int k = 1; k < n; k++) {
        if (d[k] + 1 < d[k+1]) {
            int l = d[k];
            int r = d[k+1] - 1;
            diff[l]++;
            diff[r+1]--;
        }
    }
    
    int s = 0;
    for (int i = 1; i <= n; i++) {
        s += diff[i];
        if (flag[i] != 1 && s > 0) {
            flag[i] = -1;
        }
    }
    
    double ans = 1.0;
    for (int i = 1; i < n; i++) {
        if (flag[i] == 1) {
            ans += 1.0;
        } else if (flag[i] == 0) {
            ans += 0.5;
        }
    }
    
    printf("%.3lf\n", ans);
    
    return 0;
}