#include<stdio.h>
#include<string.h>
#include<limits.h>  // 为了使用INT_MIN

#define max(x,y) ((x)>(y)?(x):(y))
#define MAX(x,y,z) (max(max((x),(y)),(z)))

char s1[3001], s2[3001];
int P[5][5];
int f[3001][3001][4];

// f[i][0]表示s1,s2串都以字母结尾的最优解
// f[i][1]表示s1以空格结尾,s2以字母结尾的最优解
// f[i][2]表示s1以字母结尾,s2以空格结尾的最优解

int n, m, A, B;

int work(char ch)
{
    switch(ch)
    {
        case 'A': return 1;
        case 'T': return 2;
        case 'G': return 3;
        case 'C': return 4;
    }
    return 0;  // 默认返回0，虽然这个分支实际上不会被执行（假设输入总是合法的）
}

int main()
{
    freopen("dnaseq.in", "r", stdin);
    freopen("dnaseq.out", "w", stdout);

    scanf("%s", s1 + 1);
    n = strlen(s1 + 1);
    scanf("%s", s2 + 1);
    m = strlen(s2 + 1);

    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            scanf("%d", &P[i][j]);

    scanf("%d %d", &A, &B);

    // 初始化f数组为一个较小的值（注意：这里用INT_MIN的绝对值，因为memset是按字节设置的）
    memset(f, 0x80, sizeof(f));  // 0x80是-128，足够小但不等于INT_MIN

    f[0][0][0] = 0;

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
        {
            if (i + j == 0) continue;

            int t1 = work(s1[i]), t2 = work(s2[j]);

            if (i != 0 && j != 0)
                f[i][j][0] = P[t1][t2] + MAX(f[i-1][j-1][0], f[i-1][j-1][1], f[i-1][j-1][2]);

            if (j != 0)
                f[i][j][1] = MAX(f[i][j-1][0] - A, f[i][j-1][1] - B, f[i][j-1][2] - A);

            if (i != 0)
                f[i][j][2] = MAX(f[i-1][j][0] - A, f[i-1][j][1] - A, f[i-1][j][2] - B);
        }

    printf("%d\n", MAX(f[n][m][0], f[n][m][1], f[n][m][2]));

    return 0;
}
