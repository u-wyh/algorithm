// https://www.luogu.com.cn/problem/P7107
// 题意：n 个人每人抽取 m 个纸团（共 nm 个，其中 k 个有记号），判断是否存在一种分配方案使恰好 p 个人抽到的记号数达到全局最大值；
// 若存在需构造每人带记号与不带记号的纸团数 (x_i, y_i)。
// 数据范围：0 <= p <= n <= 10^5，n >= 1，1 <= m <= 10^9，0 <= k <= n*m。
// 算法标签：构造、数学
#include<stdio.h>

int main()
{
    int n,m,k,p;
    scanf("%d %d %d %d",&n,&m,&k,&p);
    if(n!=p){
        if(k/p<=m){
            if((k/p)>((k%p)/(n-p)+(k%p)%(n-p)>0?1:0)){
                printf("YES\n");
                for(int i=1;i<=p;i++){
                    printf("%d %d\n",k/p,m-k/p);
                }
                for(int i=p+1;i<=p+(k%p)%(n-p);i++){
                    printf("%d %d\n",(k%p)/(n-p),m-(k%p)/(n-p)-1);
                }
                for(int i=p+(k%p)%(n-p)+1;i<=n;i++){
                    printf("%d %d\n",(k%p)/(n-p),m-(k%p)/(n-p));
                }
            }else{
                printf("NO\n");
            }
        }else{
            if(m>((k-m*p)/(n-p)+(k-m*p)%(n-p)>0?1:0)){
                printf("YES\n");
                for(int i=1;i<=p;i++){
                printf("%d %d\n",m,0);
                }
                for(int i=p+1;i<=p+(k-m*p)%(n-p);i++){
                    printf("%d %d\n",(k-m*p)/(n-p)+1,m-(k-m*p)/(n-p)-1);
                }
                for(int i=p+(k-m*p)%(n-p)+1;i<=n;i++){
                    printf("%d %d\n",(k-m*p)/(n-p),m-(k-m*p)/(n-p));
                }
            }else{
                printf("NO\n");
            }
        }
    }else{
        if(k%p==0){
            printf("YES\n");
            for(int i=1;i<=n;i++){
                printf("%d %d\n",k/p,m-k/p);
            }
        }
        else{
            printf("NO\n");
        }
    }
    return 0;
}
