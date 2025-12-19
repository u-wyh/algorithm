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
