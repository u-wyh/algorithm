#include<stdio.h>
#include<stdbool.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int x[m+1],y[m+1];
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&x[i],&y[i]);
    }
    int ans=0;
    for (int i = 0; i < (1 << n); i++) {
        bool bj = false; // C语言中，布尔类型用false和true表示
        for (int j = 1; j <= m; j++) {
            if ((i & (1 << (x[j] - 1))) && (i & (1 << (y[j] - 1)))) {
                bj = true;
                break;
            }
        }
        if (!bj) ans++;
    }
    printf("%d\n",ans);
    return 0;
}
