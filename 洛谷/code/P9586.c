#include<stdio.h>

int main()
{
    int t;
    scanf("%d",&t);
    int c1,c2,c3,d1,d2,d3;
    for(int i=1;i<=t;i++){
        scanf("%d %d %d %d %d %d",&c1,&c2,&c3,&d1,&d2,&d3);
        if(c1>d2||c3>d1)
            printf("C\n");
        else if(d3>c1||d1-c3>c2)
            printf("D\n");
        else
            printf("E\n");
    }
    return 0;
}
