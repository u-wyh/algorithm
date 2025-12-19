#include <bits/stdc++.h>
using namespace std;

int n, m, d[25], a[25][1005];
int cnt[1<<20], f[1 << 20];

int main()
{
    cin>>n>>m;
    for (int i = 0; i < n; i++){
        cin>>d[i]>>a[i][0];
        for (int j = 1; j <= a[i][0]; j++)
            cin>>a[i][j];
    }

    cnt[0]=0;
    for(int i=1;i<(1<<n);i++){
        int k=i&-i;
        cnt[i]=cnt[i^k]+1;
    }

    int ans = 1e9;
    memset(f,-1,sizeof(f));
    f[0] = 0;
    for (int i = 0; i < (1<<n); i++){
        for (int j = 0; j < n; j++){
            if (i & (1 << j))
                continue;
            int p = upper_bound(a[j] + 1, a[j] + a[j][0] + 1, f[i]) - a[j];
            if (p > 1)
                f[i | (1 << j)] = max(f[i | (1 << j)], a[j][p - 1] + d[j]);
            else
                f[i | (1 << j)] = f[i];
        }
        if (f[i] >= m)
            ans = min(ans, cnt[i]);
    }
    if (ans == 1e9)
        printf("-1");
    else
        printf("%d", ans);
    return 0;
}
