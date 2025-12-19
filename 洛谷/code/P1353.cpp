#include<iostream>
#include<cstdio>
using namespace std;

int f[10510][510], n, m, d[10010];

int main() {
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; ++i) {
        scanf("%d", &d[i]);
    }
    f[1][1]=d[1];
    for(int i=1; i<=n; ++i) {
        for(int j=0; j<=min(i, m); ++j) {
            if(j==0)
                f[i][0]=max(f[i-1][0], f[i][0]);
            else
                f[i+j][0]=max(f[i+j][0], f[i][j]);
            f[i+1][j+1]=max(f[i+1][j+1], f[i][j]+d[i+1]);
        }
    }
    printf("%d", f[n][0]);
    return 0;
}
