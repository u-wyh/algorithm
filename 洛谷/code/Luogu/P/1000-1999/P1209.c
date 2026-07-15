#include<stdio.h>
#include<stdlib.h>
#define MAXN 205

// 比较函数，用于qsort
int cmp(const void *x, const void *y) {
    return (*(int *)y - *(int *)x);
}

int main() {
    int m, s, c, ans;
    int a[MAXN], C[MAXN],b[MAXN],min=s,max=0;
    scanf("%d %d %d", &m, &s, &c);
    for(int i=1;i<=s;i++)
    {
        a[i]=0;
        C[i]=0;
        b[i]=0;
    }
    int k;
    for (int i = 1; i <= c; i++) {
        min=min<k?min:k;
        max=min>k?max:k;
        scanf("%d",&k);
        a[k]=1;
    }
    ans=s;

    if (m >= c) { // 如果木板数大于牛数，每只牛可以有一块木板
        printf("%d\n", c);
        return 0;
    }
    C[0]=0;
    for(int i=min;i<=max;i++)
    {
        if(a[i]==1)
        {
            C[i]=0;
            b[i-1]=C[i-1];
        }
        else
            C[i]=1+C[i-1];
    }

    qsort(b + 1, s, sizeof(int), cmp); // 对距离进行排序

    // 减去差最大的木板间隔，直到满足m块木板
    for (int i = 1; i <= m -1; i++) {
        ans  -= b[i];
    }

    printf("%d\n", ans);

    return 0;
}
