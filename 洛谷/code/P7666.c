// https://www.luogu.com.cn/problem/P7666
// 题意：N 位客人依次在 [T_i, T_i+1] 来访（区间不重叠），期间炉子必须开启；
// 初始关闭，最多用 K 根火柴点亮 K 次（可随时关闭），求炉子最小总开启时间。
// 数据范围：1 <= N <= 10^5，1 <= K <= N，1 <= T_i <= 10^9，T_i < T_{i+1}。
#include<stdio.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
    return (*(int *)b - *(int *)a);
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    int T[n+1],t[n+1];
    t[1]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&T[i]);
        if(i>=2){
            t[i]=T[i]-T[i-1];
        }
    }
    qsort(t+1,n,sizeof(int),cmp);
    int sum=0;
    for(int i=1;i<=(m-1);i++){
        sum+=t[i];
    }
    printf("%d\n",T[n]+1-T[1]-sum+m-1);
    return 0;
}
