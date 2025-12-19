#include <bits/stdc++.h>
using namespace std;
const int MAXN = 800010;

int n, q;
char s[MAXN];
int fa[MAXN];
int t[MAXN];

int main() {
    scanf("%d %d %s", &n, &q, s + 1);
    
    fa[1] = 0;
    for (int i = 2; i <= n; i++) {
        int j = fa[i - 1];
        while (j && s[i] != s[j + 1]) {
            j = fa[j];
        }
        if (s[i] == s[j + 1]) {
            j++;
        }
        fa[i] = j;
    }

    for (int i = 1; i <= n; i++) {
        t[i] = 1;
    }
    for (int i = n; i >= 1; i--) {
        if (fa[i]) {
            t[fa[i]] += t[i];
        }
    }

    while (q--) {
        int op, v;
        scanf("%d", &op);
        if (op == 1) {
            n++;
            char c[2];
            scanf("%s", c);
            s[n] = c[0];
            
            int j = fa[n - 1];
            while (j && s[n] != s[j + 1]) {
                j = fa[j];
            }
            if (s[n] == s[j + 1]) {
                j++;
            }
            fa[n] = j;
            
            t[n] = 1; 
            int f = fa[n];
            while (f) {
                t[f]++;
                f = fa[f];
            }
        } else {
            scanf("%d", &v);
            int ans = -1;
            int f = fa[n];
            while (f) {
                if (t[f] >= v) {
                    ans = f;
                    break;
                }
                f = fa[f];
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}