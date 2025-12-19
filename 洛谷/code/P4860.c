#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++){
        int n;
        scanf("%d",&n);
        if(n%4==0){
            printf("Roy wins!\n");
        }else{
            printf("October wins!\n");
        }
    }
    return 0;
}
